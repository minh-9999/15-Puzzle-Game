#include "board.hh"
#include "createShape.hh"
#include <random>

// Board size (4x4 puzzle)
constexpr int N = 4;

// Gap between tiles
#if defined(__APPLE__)
constexpr int gap = 30;
#else
constexpr int gap = 40;
#endif

/**
 * Shuffle the puzzle board by performing random valid moves.
 *
 * This function simulates actual moves of the empty tile to ensure
 * the resulting board configuration is always solvable.
 *
 * @param board Reference to the puzzle board (array of 16 integers).
 *              Values 1–15 represent tiles, 0 represents the empty space.
 */
void shuffleBoard(std::array<int, 16> &board)
{
    std::random_device rd;
    std::mt19937 g(rd());

    int emptyPos = 15;             // Start with empty tile at last position
    for (int i = 0; i < 1000; ++i) // Perform 1000 random moves
    {
        int ex = emptyPos % N, ey = emptyPos / N;
        std::vector<int> validMoves;

        // Collect valid neighbor positions
        if (ex > 0)
            validMoves.push_back(emptyPos - 1); // left
        if (ex < N - 1)
            validMoves.push_back(emptyPos + 1); // right
        if (ey > 0)
            validMoves.push_back(emptyPos - N); // up
        if (ey < N - 1)
            validMoves.push_back(emptyPos + N); // down

        // Pick a random valid move
        std::uniform_int_distribution<> dis(0, validMoves.size() - 1);
        int newPos = validMoves[dis(g)];

        // Swap empty tile with chosen neighbor
        std::swap(board[emptyPos], board[newPos]);
        emptyPos = newPos;
    }
}

/**
 * Draw the puzzle board with tiles and numbers.
 *
 * Each tile is drawn as a rounded rectangle with a color depending on its state:
 *  - Purple for the empty tile
 *  - Orange for tiles in the correct position
 *  - Teal for tiles in the wrong position
 *
 * @param window       Render target window.
 * @param board        Current puzzle board state.
 * @param fontNumber   Font used for drawing numbers.
 * @param margin       Horizontal margin around the puzzle.
 * @param headerHeight Vertical space reserved for header.
 * @param topMargin    Extra margin above the puzzle grid.
 * @param rectSize     Size of each tile rectangle.
 * @param cornerRadius Radius for rounded corners.
 */
void drawBoard(sf::RenderWindow &window,
               const std::array<int, 16> &board,
               const sf::Font &fontNumber,
               float margin, float headerHeight, float topMargin,
               float rectSize, float cornerRadius, unsigned int fontSize)
{
    for (int i = 0; i < 16; ++i)
    {
        int val = board[i]; // Tile value (0 = empty)
        int xIndex = i % N; // Column index
        int yIndex = i / N; // Row index

        float offsetX = margin;
        float offsetY = headerHeight + topMargin;

        // Calculate tile position
        float x = xIndex * (rectSize + gap) + offsetX;
        float y = yIndex * (rectSize + gap) + offsetY;

        // Create rounded rectangle tile
        sf::ConvexShape rect = createRoundedRect(rectSize, rectSize, cornerRadius);
        rect.setPosition({x, y});

        // Color based on tile state
        if (val == 0)
            rect.setFillColor(sf::Color(128, 0, 128)); // Empty tile (purple)
        else if (val == i + 1)
            rect.setFillColor(sf::Color(255, 165, 0)); // Correct position (orange)
        else
            rect.setFillColor(sf::Color(60, 180, 170)); // Wrong position (teal)

        rect.setOutlineThickness(1);
        rect.setOutlineColor(sf::Color::Black);
        window.draw(rect);

        // Draw number if not empty
        if (val)
        {
            sf::Text text(fontNumber, std::to_string(val), fontSize);
            text.setFillColor(sf::Color::White);
            centerText(text, x, y, rectSize, rectSize);
            window.draw(text);
        }
    }
}

/**
 * Attempt to move a tile into the empty space if adjacent.
 *
 * Updates the board state, increments move count, plays click sound,
 * and checks for win condition. If solved, updates game state and plays win sound.
 *
 * @param board        Puzzle board state.
 * @param emptyIdx     Index of the empty tile (updated if move succeeds).
 * @param targetX      Target tile column index.
 * @param targetY      Target tile row index.
 * @param moveCount    Reference to move counter.
 * @param clickSound   Sound effect played on tile move.
 * @param music        Background music (paused on win).
 * @param winSound     Sound effect played on win.
 * @param gameClock    Clock tracking elapsed time.
 * @param gameWon      Flag set to true if puzzle is solved.
 * @param finalTime    Time taken to solve puzzle.
 * @param winShownTime Timestamp when win was achieved.
 */
void tryMoveTile(std::array<int, 16> &board,
                 int &emptyIdx, int targetX, int targetY,
                 int &moveCount,
                 std::unique_ptr<sf::Sound> &clickSound,
                 sf::Music &music, std::unique_ptr<sf::Sound> &winSound,
                 sf::Clock &gameClock, bool &gameWon,
                 int &finalTime, sf::Time &winShownTime)
{
    int ex = emptyIdx % N; // Empty tile column
    int ey = emptyIdx / N; // Empty tile row

    // Check adjacency (Manhattan distance = 1)
    if ((abs(ex - targetX) + abs(ey - targetY)) == 1)
    {
        int idx = targetY * N + targetX;
        std::swap(board[idx], board[emptyIdx]);
        emptyIdx = idx;
        moveCount++;

        if (clickSound)
            clickSound->play();

        // Check if puzzle is solved
        if (isSolved(board))
        {
            gameWon = true;
            finalTime = static_cast<int>(gameClock.getElapsedTime().asSeconds());
            winSound->play();
            music.pause();
            winShownTime = gameClock.getElapsedTime();
        }
    }
}

/**
 * Check if the puzzle board is solved.
 *
 * The solved state requires tiles 1–15 to be in ascending order
 * and the last tile (index 15) to be empty (0).
 *
 * @param board Puzzle board state.
 * @return true if solved, false otherwise.
 */
bool isSolved(const std::array<int, 16> &board)
{
    for (auto a{0}; a < 15; ++a)
        if (board[a] != a + 1)
            return false;

    return board[15] == 0; // Last tile must be empty
}
