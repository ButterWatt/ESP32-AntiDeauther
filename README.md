# Overview
A repository that can stop mass deauthencation attacks
>[!CAUTION]
>This repository is created for educational purposes only, I am not responsible for any issue by using it and/or triggering someone. If you triggered some random kids with those AP names, then... I don't know, solve it yourself.
>
>If you try to report this repository for "ruining your mood", I can tell you are overreacting. 
# Build
You can clone this repository (`git clone https://github.com/ButterWatt/ESP32-AntiDeauther.git`) and build it using VSCode and PlatformIO or using Github Actions.
# How it works
It will create an AP, after detecting deauth packages, it will shutdown the AP within 350 - 600ms (± 50ms), AP name and random MAC address will be applied and hosted back.
>[!IMPORTANT]
>It will **only** stop mass deauthencation flood, not targeted deauthencation, which mean targeted deauthencation would out of its protection scope. Exactly likes preventing some kids try to use fake gun, not sniper.
>
>If you blame me due to its protection not doing well to your actual access point, please, read twice.

# Quote of the repo
**If you are looking for AI girlfriend, please find and touch grass immediately.** -Butter, who found themself writing complain in the dark.
>[!TIP]
>Little did you know: *I made this repository and quote when I was bored, basicly*
>
>The typo is *on purpose*, so... stay salty and don't remind me. By the way if you want to tell me there is a typo, you fail the vibe check :)

# License
All files within this repo are released under the GNU GPL V3 License as per the LICENSE file stored in the root of this repo.
