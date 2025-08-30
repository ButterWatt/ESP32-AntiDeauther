# Overview
A repository that can stop mass deauthencation attacks
>[!CAUTION]
>This repository is created for educational purposes only, I am not responsible for any issue by using it and/or triggering someone. If you triggered some random kids with those AP names, then... I don't know, solve it yourself, you must be responsible for your actions.
>
>*YOU MUST BE RESPONSIBLE FOR YOUR ACTIONS, RIGHT???*
>
>I know you don't want to do bird or money flies away, so you know what you should do and what should not.
>
>If you try to report this repository for "ruining your mood", I can tell you are overreacting. 
# Build
You can clone this repository (`git clone https://github.com/ButterWatt/ESP32-AntiDeauther.git`) and build it using VSCode and PlatformIO or using Github Actions.
>[!NOTE]
>You can try `dev` branch if you want Nokia Tune, that's a legendary sound I ever heard. Unlike someone that still protecting their iPad and watch brainrot lol 😏
# How it works
It will create an AP, after detecting deauth packages, it will shutdown the AP within 350 - 600ms (± 60ms jitter), AP name and random MAC address will be applied and hosted back.
*Which mean some deauthers cannot track it normally by its behaviors*
>[!IMPORTANT]
>It will **only** stop mass deauthencation flood, not targeted deauthencation, which mean targeted deauthencation would out of its protection scope. Exactly likes preventing some kids try to use fake gun, not sniper.
>
>If you blame me due to its protection not doing well to your actual access point, please, read twice. Remember that's not my fault when that situation occurs.

 # Quote of the repo
**If you are looking for AI girlfriend, please find and touch grass immediately.** -Butter, who found themself writing complain in the dark.
>[!TIP]
>Little did you know: *I made this repository and the quote when I was bored, basicly*
>
>The typos are *on purpose*, so... stay salty. By the way, if you want to correct them, you fail the vibe check 😁

# License
All files within this repo are released under the GNU GPL V3 License as per the LICENSE file stored in the root of this repo. *You won't have any way to sell this without sharing the source bruh, also I won't expect that.*
