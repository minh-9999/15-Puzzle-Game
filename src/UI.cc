#include "UI.hh"

/**
 * Draw the right-side UI panel with game information and controls.
 *
 * This panel lives to the right of the puzzle grid. It shows:
 *  - Music status (ON/OFF) and the shortcut key to toggle (M)
 *  - Hints for controls (M, R)
 *  - Live elapsed time (or final time after a win)
 *  - Total move count
 *
 * Coordinate system notes:
 *  - RightX: the x-origin of the right panel (typically margin + N * tileSize)
 *  - TopY:   the y-origin aligned with the top of the puzzle area (headerHeight + topMargin)
 *  - rightMargin: inner padding from the left edge of the right panel
 *  - gapRight: vertical spacing step used to place elements line by line
 *
 * Rendering notes:
 *  - Uses fontInfo for all text elements in this panel.
 *  - Colors: red/gray for music status, soft gray for hints, white for data.
 *  - Text sizes: status/time/moves at 50px; hints at 40px.
 */
void drawUI(sf::RenderWindow &window,
            const sf::Font &fontInfo,
            bool musicPlaying,
            int elapsedSeconds, int finalTime,
            bool gameWon, int moveCount,
            float RightX, float TopY,
            float rightMargin, float gapRight,
            unsigned int fontSize)
{
    // Music status indicator (shows current state and shortcut key)
    // Position: first line of the panel
    sf::Text musicStatus(fontInfo,
                         musicPlaying ? "[ON] Music: (M)" : "[OFF] Music: (M)",
                         fontSize);
    // ON = warm red; OFF = neutral gray
    musicStatus.setFillColor(musicPlaying ? sf::Color(220, 50, 50)
                                          : sf::Color(150, 150, 150));
    musicStatus.setStyle(sf::Text::Bold);
    musicStatus.setPosition(sf::Vector2f(RightX + rightMargin, TopY));
    window.draw(musicStatus);

    // Shortcut hints (placed below status with vertical spacing)
    unsigned int hintSize = static_cast<unsigned int>(fontSize * 0.6f);
    sf::Text hint1(fontInfo, "Press M to toggle music", hintSize);
    sf::Text hint2(fontInfo, "Press R to restart", hintSize);
    hint1.setFillColor(sf::Color(220, 220, 220)); // soft gray, lower emphasis
    hint2.setFillColor(sf::Color(220, 220, 220));
    hint1.setPosition(sf::Vector2f(RightX + rightMargin, TopY + gapRight * 2));
    hint2.setPosition(sf::Vector2f(RightX + rightMargin, TopY + gapRight * 3));
    window.draw(hint1);
    window.draw(hint2);

    // Time: shows live elapsed time until win, then locks to finalTime
    // Positioned further down to visually separate from hints
    const int timeValue = gameWon ? finalTime : elapsedSeconds;
    sf::Text timeText(fontInfo, "TIME  " + std::to_string(timeValue) + "s", fontSize);
    timeText.setFillColor(sf::Color::White);
    timeText.setStyle(sf::Text::Bold);
    timeText.setPosition(sf::Vector2f(RightX + rightMargin, TopY + gapRight * 5));
    window.draw(timeText);

    // Moves: total number of player actions (swaps)
    // Placed one line below time
    sf::Text moveText(fontInfo, "MOVES  " + std::to_string(moveCount), fontSize);
    moveText.setFillColor(sf::Color::White);
    moveText.setStyle(sf::Text::Bold);
    moveText.setPosition(sf::Vector2f(RightX + rightMargin, TopY + gapRight * 7));
    window.draw(moveText);
}

/**
 * Create and return the main game window.
 *
 * Size calculation:
 *  - Width  = puzzle width (N * tileSize) + 2 * margin + rightPanelWidth
 *  - Height = puzzle height (N * tileSize) + headerHeight + topMargin
 *
 * Title: "15 Puzzle"
 * Icon: attempts to load "assets/puzzle.png" and set it as the window icon.
 *       If loading fails, the default window icon is used.
 *
 * Parameters:
 *  - N: puzzle dimension (e.g., 4 for 4x4)
 *  - tileSize: pixel size of each tile (square)
 *  - margin: left/right padding around the puzzle area
 *  - headerHeight: vertical space reserved for the title/header
 *  - topMargin: additional padding above the puzzle grid
 *  - rightPanelWidth: extra horizontal space for the right-side UI panel
 */
sf::RenderWindow createWindow(
    unsigned int N,
    unsigned int tileSize,
    unsigned int margin,
    unsigned int headerHeight,
    unsigned int topMargin,
    unsigned int rightPanelWidth,
    unsigned int bottomMargin)
{
    // Compute the final window size from layout parameters
    sf::Vector2u size(
        N * tileSize + margin * 2 + rightPanelWidth,           // total width
        N * tileSize + headerHeight + topMargin + bottomMargin // total height
    );

    // Create the window with a fixed size and a descriptive title
    sf::RenderWindow window(sf::VideoMode(size), "15 Puzzle");

    // Try to set a custom window icon (non-fatal if missing)
    sf::Image icon;
    if (icon.loadFromFile("assets/puzzle.png"))
    {
        window.setIcon(icon);
    }

    return window;
}
