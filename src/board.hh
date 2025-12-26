#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <array>

extern const int N;

/**
 * Shuffle the puzzle board by performing random valid moves.
 *
 * This function simulates moves of the empty tile (value 0) to produce
 * a randomized yet solvable configuration. It modifies the input board in place.
 *
 * @param board Puzzle board array (size 16). Values 1–15 are tiles; 0 is the empty space.
 */
void shuffleBoard(std::array<int, 16> &);

/**
 * Render the puzzle grid and its tiles onto the target window.
 *
 * Each tile is drawn as a rounded rectangle. Colors indicate state:
 *  - Empty tile (0): purple
 *  - Correctly placed tile: orange
 *  - Misplaced tile: teal
 * The tile number is centered inside non-empty tiles using fontNumber.
 *
 * Layout:
 *  - Grid size is determined by global N (e.g., 4x4).
 *  - Tile position = (index * (rectSize + gap)) + corresponding offset.
 *  - Offsets: margin (X), headerHeight + topMargin (Y).
 *
 * @param window       Render target window.
 * @param board        Current board state (read-only).
 * @param fontNumber   Font used to draw tile numbers.
 * @param margin       Horizontal offset from the left of the window to the grid.
 * @param headerHeight Vertical space reserved for the title/header above the grid.
 * @param topMargin    Extra top padding below the header.
 * @param rectSize     Tile width/height (square).
 * @param cornerRadius Corner radius for rounded tile rectangles.
 */
void drawBoard(sf::RenderWindow &window,
               const std::array<int, 16> &board,
               const sf::Font &fontNumber,
               float margin, float headerHeight, float topMargin,
               float rectSize, float cornerRadius);

/**
 * Attempt to move a tile into the empty space if it is adjacent.
 *
 * Behavior:
 *  - Valid move: Manhattan distance between target tile and empty tile == 1.
 *  - On success: swaps tiles, updates emptyIdx and moveCount, plays clickSound.
 *  - Win check: if the board is solved, sets gameWon, records finalTime,
 *               pauses background music and plays winSound, stores winShownTime.
 *
 * Notes:
 *  - Sounds are passed as unique_ptr to align with ownership in the main module.
 *  - Time values are based on gameClock (seconds).
 *
 * @param board         Puzzle board (modified in place).
 * @param emptyIdx      Index of the empty tile in the board (updated on move).
 * @param targetX       Column of the tile to move (0-based).
 * @param targetY       Row of the tile to move (0-based).
 * @param moveCount     Reference to the total number of successful moves (incremented).
 * @param clickSound    Sound effect to play on a successful tile move.
 * @param music         Background music (paused when the player wins).
 * @param winSound      Sound effect to play when the puzzle is solved.
 * @param gameClock     Clock used to compute elapsed time and win timestamp.
 * @param gameWon       Flag set to true when the puzzle is solved.
 * @param finalTime     Elapsed time in seconds at the moment of victory.
 * @param winShownTime  Timestamp (sf::Time) when the win screen was triggered.
 */
void tryMoveTile(std::array<int, 16> &board,
                 int &emptyIdx, int targetX, int targetY,
                 int &moveCount,
                 std::unique_ptr<sf::Sound> &clickSound,
                 sf::Music &music, std::unique_ptr<sf::Sound> &winSound,
                 sf::Clock &gameClock, bool &gameWon,
                 int &finalTime, sf::Time &winShownTime);

/**
 * Determine whether the board is in the solved state.
 *
 * A solved board has tiles 1–15 in ascending order and the last slot (index 15)
 * is the empty tile (0).
 *
 * @param board Current board state.
 * @return true if solved; false otherwise.
 */
bool isSolved(const std::array<int, 16> &board);


