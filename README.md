# APluginTemplate

A simple Amethyst Plugin Template.

## What files should I change to rename my project?
1. `README.md` > Change as needed.
2. `CMakeLists.txt` > Change `APluginTemplate` to whatever you need, this will remain the same. It is recommended you use `PascalCase` when naming your project.
3. `.vscode` > `tasks.json` > Replace `APluginTemplate` with what you exactly put for `CMakeLists.txt`.

## How do I build with VSCode?
1. Open the project.
2. Press `Ctrl + Shift + P` all at the same time, this will open VSCode's quick menu.
3. Search for `Task: Run Task` and select it.
4. Select `Build Mod`, you may need to change `tasks.json` depending on your Visual Studio version. If this is the case run `cmake --help` in a console to find valid CMake generators.