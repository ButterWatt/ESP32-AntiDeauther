# Overview
A repository that can stop mass deauth attacks
>[!CAUTION]
>This repository is created for educational purposes only, I am not responsible for any issue by using it and/or triggering someone. If you triggered some random kids with those AP names, then... I don't know, solve it yourself.
# Build
You can clone this repository (`git clone https://github.com/ButterWatt/ESP32-AntiDeauther.git`) and build it using VSCode and PlatformIO or using Github Actions.
# How it works
It will create an AP, after detecting deauth packages, it will shutdown the AP within 350 - 600ms, AP name and random MAC address will be change and hosted back.
>[!IMPORTANT]
>It will only stop mass deauth flood, not targeted deauth. It's likes preventing some kids try to use fake gun.
>
>If you blame me for this, please, read twice.
# License
All files within this repo are released under the GNU GPL V3 License as per the LICENSE file stored in the root of this repo.
