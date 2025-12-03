<p align="center">
  <a href="https://github.com/ATXLtheAxolotl/VidereLonge">
    <img src="./assets/banner.png" alt="VidereLonge Banner">
  </a>

  <p align="center">
    <a href="https://github.com/ATXLtheAxolotl/VidereLonge">Github</a>
    ·
    <a href="https://github.com/ATXLtheAxolotl/VidereLonge/issues/new">Report An Issue</a>
    ·
    <a href="https://github.com/ATXLtheAxolotl/VidereLonge/issues/new">Request A Feature</a>
  </p>
</p>

<div align="center">

  [![Contributors](https://img.shields.io/github/contributors/ATXLtheAxolotl/VidereLonge.svg?style=for-the-badge)](https://github.com/ATXLtheAxolotl/VidereLonge/graphs/contributors)
  [![Forks](https://img.shields.io/github/forks/ATXLtheAxolotl/VidereLonge.svg?style=for-the-badge)](https://github.com/ATXLtheAxolotl/VidereLonge/network/members)
  [![Stargazers](https://img.shields.io/github/stars/ATXLtheAxolotl/VidereLonge.svg?style=for-the-badge)](https://github.com/ATXLtheAxolotl/VidereLonge/stargazers)
  [![Issues](https://img.shields.io/github/issues/ATXLtheAxolotl/VidereLonge.svg?style=for-the-badge)](https://github.com/ATXLtheAxolotl/VidereLonge/issues)
  [![MIT License](https://img.shields.io/github/license/ATXLtheAxolotl/VidereLonge.svg?style=for-the-badge)](https://github.com/ATXLtheAxolotl/VidereLonge/blob/main/License.md)
</div>

## VidereLonge v1.3.1
Currently stable on Minecraft Bedrock Edition 1.21.0.3 with Amethyst Runtime 2.2.1

<video controls>
    <source src="./assets/VidereLongeExample.mp4" type="video/mp4">
</video>

## Contributions

* Thanks to [@KingRocco21](https://github.com/KingRocco21) for updating the mod to AmethystRuntime@1.4.1 [#9](https://github.com/AmethystAPI/VidereLonge/pull/9)

## To-do
[ ] #3 - Cleanup code (never!)

[ ] Move settings to the GUI.

[ ] #8 - Scroll to change zoom level.

## My game is crashing when I launch? What do I do?

Join the [Amethyst modding Discord guild](https://discord.gg/DcCksKssfD), we'll be happy to help (just don't spam the others)! Ping ATXL instead.

## How do I change the zoom keybind?
1. Go to your settings

    <img src="assets/titleScreen.png" width=400 />

2. Click `Keyboard & Mouse`

    <img src="assets/hoverKeyboardMouse.png" width=400 />

3. Scroll to the bottom for `Zoom`, then bind it to the desired key.

    <img src="assets/keybindHover.png" width=400 />

## How do I change the config?
1.  Open the mods folder.

    <img src="assets/openModsFolder.png" width=400 />

2. Find the VidereLonge folder.
    
    <img src="assets/movedFolders.png" width=400 />

3. Open `config.json` and change it to whatever you please.

    <img src="assets/modConfig.png" width=400 />

> **Note**
> A default config.json should be made automatically once you start the game however you can still manually make it if you like.
> ````json
> {
>   "zoomType": "gradual",
>   "sensitivityDampen": 90.0,
>   "targetFov": 10.0,
>   "duration": 0.2
> }
> ````

4. The config format is the following:
    * `zoomType` can either be `instant` or `gradual`. Instant sets your FOV to the `targetFov` the *intstant* you press the zoom key and `gradual` zooms in slowly.
    * `sensitivityDampen` is the percentage you want your sensitivity to decrease by when zoomed.
    * `targetFov` is the FOV the mod will stop at when you press the zoom key.
    * `duration` is for the `gradual` mode. In this amount of time (seconds) you will reach the `targetFov`.



## How was the banner made?
* This was made with Blender using two assets from Sketchfab.
* [Construction Steve](https://sketchfab.com/3d-models/construction-steve-41f6a232772c4b069eab765ef96a0ec1) by [Ghost99](https://sketchfab.com/Ghost99) using the [CC By 4.0 Deed License](https://creativecommons.org/licenses/by/4.0/). This work was modified.
* [Spyglass](https://sketchfab.com/3d-models/spyglass-d1c88de81f594dc79786f16d497fd908) by [Azumiru](https://sketchfab.com/Azumiru) using the [CC By 4.0 Deed License](https://creativecommons.org/licenses/by/4.0/).
