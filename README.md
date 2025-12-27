# 🎮 15 Puzzle Game

<!-- CI status badge -->

![CI](https://github.com/minh-9999/15-Puzzle-Game/actions/workflows/cpp-multi-platform.yml/badge.svg)

<!-- Latest release badge -->

![GitHub release (latest by date)](https://img.shields.io/github/v/release/minh-9999/15-Puzzle-Game)

<!-- License badge -->

![License](https://img.shields.io/github/license/minh-9999/15-Puzzle-Game)

<!-- Platform support -->

![Platform](https://img.shields.io/badge/Platform-Linux--Windows--MacOS-pink)

<!-- CMake badge -->

![CMake](https://img.shields.io/badge/Build%20system-CMake-informational)

<!-- C++ version -->

![C++20](https://img.shields.io/badge/C%2B%2B-20-magenta)

<!-- Lines of code (optional but cool) -->

![LOC](https://tokei.rs/b1/github/minh-9999/15-Puzzle-Game)

A cross-platform C++ puzzle game built with SFML, featuring clean architecture, sound effects, and CI/CD via GitHub Actions.

---

## ✨ Features

Board shuffling ensures solvable configurations.

Displays elapsed time and move count.

Click sound when moving tiles, win sound when solved.

Semi-transparent overlay with a win message for 3 seconds.

Background music with toggle option.  

  
<img src="https://raw.githubusercontent.com/minh-9999/15-Puzzle-Game/refs/heads/main/assets/Capture.PNG" alt="anh-mieu-ta" border="0">

---

## 🎹 Controls

Mouse: Click a tile to move it if adjacent to the empty space.

Arrow keys: Move the empty space up/down/left/right.

R: Reset the board.

M: Toggle background music.

---

## ⚙️ Requirements

- CMake ≥ 3.16
- Ninja (optional)
- C++20 compatible compiler

---

## 🚀 Build Instructions

- Install **SFML**.  
Download the SFML release latest: https://github.com/SFML/SFML/releases/tag/3.0.2  
Check the version compatible with your OS.     
Ex. Windows: SFML-3.0.2-Windows.VS2022.x64.zip if using .lib library or SFML-3.0.2-Windows.MinGW.x64.zip
if using .a library. 

- Install **CMake**.  
Download the CMake release: https://github.com/Kitware/CMake/releases/tag/v4.2.1  
Check the version compatible with your OS.    

- Edit path of SFML to make sure link sfml library when compiling  
Check at line of CMakeLists.txt: ***set(SFML_DIR "path of SFML library")***  
replace "path of SFML library" by your real-world SFML library which contains cmake configs  
Ex: Y:/Hai/SFML-3.0.2-CL/lib/cmake/SFML 

- When Ensure these steps were successful, now download the source codes
```bash
git clone https://github.com/minh-9999/15-Puzzle-Game
```

build commands
```bash
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -B build-release
cd build-release  
```

```bash
cmake --build .
```
or
```bash
ninja
```

---

## 🗂 Project Structure

| Folder           | Description                           |
| ---------------- | ------------------------------------- |
| `src/`           | Core source code                      |
| `assets/`        | Assets (icons, fonts, musics, etc.)   |
| `CMakeLists.txt` | CMake build configuration file        |

## 📫 Contact

📧 ngodinhhai.hcm@gmail.com

## 📜 License  

MIT License – free to use, modify, and distribute.  

