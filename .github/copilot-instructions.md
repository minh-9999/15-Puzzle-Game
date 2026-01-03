<!-- Copilot/AI agent instructions for the 15-Puzzle-Game repo -->
# AI assistant guide — 15-Puzzle-Game (C++ / SFML)

Purpose: help an AI coding agent become productive quickly in this repository.

- **Big picture:** This is a single-binary C++20 SFML puzzle game. Core responsibilities are split between:
  - [src/main.cc](src/main.cc#L1-L40) — app bootstrap, SFML window, event loop, top-level constants (tile sizes, margins), font loading, and lifecycle.
  - [src/board.cc](src/board.cc#L1-L40) / [src/board.hh](src/board.hh#L1-L40) — game state and logic: `shuffleBoard`, `drawBoard`, `tryMoveTile`, `isSolved` (4x4 board backed by `std::array<int,16>`).
  - [src/UI.hh](src/UI.hh#L1-L40) — right-side UI panel drawing and `createWindow` helper.
  - [src/createShape.hh](src/createShape.hh#L1-L20) — rounded-rect and `centerText` helpers.
  - [src/utilities.hh](src/utilities.hh#L1-L40) — asset loaders: `loadFonts`, `loadBackgroundMusic`, `loadSound`.

- **Data flow & ownership patterns:**
  - The canonical board state is a `std::array<int,16>` in `main.cc`. `shuffleBoard` mutates it; `drawBoard` reads it; `tryMoveTile` mutates it and updates `emptyIdx` and `moveCount`.
  - Background music is stored as an `sf::Music` value (play/pause by reference). Short sound effects are created as `std::unique_ptr<sf::Sound>`.
  - Fonts are kept in a `std::map<std::string, sf::Font>`; keys used in `main.cc` are `"number"`, `"title"`, `"info"`, `"button"`.

- **Project-specific constants & conventions:**
  - Board dimension: `N` is defined as `constexpr int N = 4;` in `src/board.cc` and declared `extern` in `src/board.hh`.
  - Layout math: tile position = index * (rectSize + gap) + offsets (`margin`, `headerHeight`, `topMargin`) — constants live in `src/main.cc`.
  - Keep function signatures for rendering and input the same (e.g., `drawBoard(...)`, `drawUI(...)`) to avoid refactoring many call sites.

- **Build / run / debug instructions (explicit):**
  - Required: CMake ≥ 3.16, C++20 compiler, SFML 3.0.2.
  - Edit `CMakeLists.txt`: set `SFML_DIR` to your SFML install path containing the CMake config files.
  - Standard build steps (from README):
    - `cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -B build-release`
    - `cd build-release`
    - `cmake --build .` or `ninja`
  - Note: `CMakeLists.txt` contains platform-specific post-build copies for SFML binaries and `assets/` on Windows/macOS. If the app cannot find fonts/sounds at runtime, ensure `assets/` is copied alongside the binary or run from repo root.

- **Assets & paths:**
  - Files are referenced directly with `assets/...` paths in `src/main.cc` (e.g., `assets/musics/bg_music.mp3`, `assets/fonts/Montserrat-Bold.ttf`). Keep new assets under `assets/fonts` or `assets/musics`.

- **Patterns to preserve when editing:**
  - Use `std::array<int,16>` for board state (0 = empty). Do not swap to a dynamic container without updating all call sites.
  - Use `unique_ptr<sf::Sound>` for short sounds (ownership semantics used across `main.cc` and `board.hh`).
  - Use helpers: `centerText(...)` and `createRoundedRect(...)` for consistent appearance.

- **Where to implement common changes:**
  - Change visual/tile sizes: update constants in `src/main.cc` (e.g., `gap`, `rectSize`) and validate placements in `src/board.cc` draw logic.
  - Change game logic (shuffle/move/isSolved): modify `src/board.cc` and keep unit semantics (16 elements, 0 as empty).
  - Add UI elements: modify `drawUI` in `src/UI.hh`/implementation and update positions passed from `main.cc`.

- **Integration & dependencies:** SFML 3.0.2, no tests provided. CI is configured in the upstream repository (see README badges); locally rely on CMake steps above.

- **Quick troubleshooting hints for AI edits:**
  - When adding/removing assets, update `main.cc` paths and ensure `assets/` gets copied to the runtime folder (or run binary from project root).
  - If UI layout breaks after edits, re-check `tileSize` math and margins in `main.cc` and `drawBoard`.

If any section is unclear or you want targeted examples (e.g., how to add a new sound or change tile colors), tell me which area and I will expand with an exact code patch.
