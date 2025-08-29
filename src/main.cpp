#include <WiFi.h>
#include "esp_wifi.h"
// ===== CONFIG =====
const int AP_CHANNEL = 1;
const int MIN_OFF_MS = 350;
const int MAX_OFF_MS = 600;
const int JITTER_MS = 60;
const int MAX_TOGGLES_PER_MIN = 40;
const unsigned long COOLDOWN_WINDOW_MS = 60UL * 1000UL;

// Meme quotes list (rotate each toggle)
const char* memeQuotes[] = {
    "Attack me - TPLink",
    "Why u still use Windows for it, lil bro? - TPLink",
    "You deserve a kick - TPLink",
    "Dumb, you touched Darwin's Award of Deauther - TPLink",
    "Nice try, kid - TPLink"
};
const int memeCount = sizeof(memeQuotes) / sizeof(memeQuotes[0]);

// ===== STATE =====
volatile bool deauthSeen = false;
unsigned long lastToggleTime = 0;
int togglesInWindow = 0;
unsigned long windowStart = 0;
bool apRunning = false;
int memeIndex = 0;

// ===== FORWARD DECL =====
void startBaitAP(const char* ssid);
void stopBaitAP();
void randomizeAPmac();
void snifferCallback(void* buf, wifi_promiscuous_pkt_type_t type);
void handleToggleIfNeeded();

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n[Info] Booting...");
    playMelody(melody, duration, len);

    // Start sniffer mode
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&snifferCallback);

    // Start initial AP
    startBaitAP(memeQuotes[memeIndex]);

    // Init window
    windowStart = millis();
}

void loop() {
    if (deauthSeen) {
        deauthSeen = false;
        Serial.println("[Warn] Deauth detected - Processing toggle...");
        handleToggleIfNeeded();
    }
    delay(10);
}

void snifferCallback(void* buf, wifi_promiscuous_pkt_type_t type) {
    const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t*)buf;
    const uint8_t *payload = ppkt->payload;

    uint8_t fc = payload[0];
    uint8_t subtype = (fc & 0xF0) >> 4;
    uint8_t type_val = (fc & 0x0C) >> 2;

    if (type_val == 0 && subtype == 12) {
        deauthSeen = true;
    }
}

void startBaitAP(const char* ssid) {
    if (apRunning) return;

    WiFi.mode(WIFI_AP);
    randomizeAPmac();

    wifi_config_t conf;
    memset(&conf, 0, sizeof(conf));
    strncpy((char*)conf.ap.ssid, ssid, sizeof(conf.ap.ssid)-1);
    conf.ap.ssid_len = strlen(ssid);
    strncpy((char*)conf.ap.password, "memepass", sizeof(conf.ap.password)-1);
    conf.ap.channel = AP_CHANNEL;
    conf.ap.max_connection = 1;
    conf.ap.authmode = WIFI_AUTH_WPA2_PSK;
    conf.ap.ssid_hidden = 0;

    if (esp_wifi_set_mode(WIFI_MODE_AP) != ESP_OK)
        Serial.println("[ERR] set_mode(AP) failed");

    if (esp_wifi_set_config(WIFI_IF_AP, &conf) != ESP_OK)
        Serial.println("[ERR] set_config(AP) failed");

    if (esp_wifi_start() != ESP_OK)
        Serial.println("[ERR] wifi_start failed");

    apRunning = true;
    Serial.printf("[INFO] Meme AP started: \"%s\"\n", ssid);
}

void stopBaitAP() {
    if (!apRunning) return;
    if (esp_wifi_stop() != ESP_OK)
        Serial.println("[ERR] wifi_stop failed");
    apRunning = false;
    Serial.println("[INFO] AP stopped.");
}

void randomizeAPmac() {
    uint8_t mac[6];
    for (int i = 0; i < 6; i++) mac[i] = (uint8_t)random(0, 256);
    mac[0] = (mac[0] & 0xFE) | 0x02; // locally administered

    if (esp_wifi_set_mac(WIFI_IF_AP, mac) == ESP_OK) {
        char buf[32];
        sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        Serial.printf("[Info] AP MAC set to %s\n", buf);
    } else {
        Serial.println("[Erro] set_mac failed");
    }
}

void handleToggleIfNeeded() {
    unsigned long now = millis();

    if (now - windowStart > COOLDOWN_WINDOW_MS) {
        windowStart = now;
        togglesInWindow = 0;
    }

    if (togglesInWindow >= MAX_TOGGLES_PER_MIN) {
        Serial.println("[Warn] Max toggles reached, cooling down...");
        return;
    }

    stopBaitAP();

    int baseOff = random(MIN_OFF_MS, MAX_OFF_MS + 1);
    int jitter = random(-JITTER_MS, JITTER_MS + 1);
    int offTime = max(100, baseOff + jitter);

    Serial.printf("[Info] Sleeping AP for %d ms\n", offTime);
    delay(offTime);

    memeIndex = (memeIndex + 1) % memeCount;
    randomizeAPmac();
    startBaitAP(memeQuotes[memeIndex]);

    togglesInWindow++;
    lastToggleTime = now;
    Serial.printf("[Info] Toggle done. Toggles in window: %d\n", togglesInWindow);
}
