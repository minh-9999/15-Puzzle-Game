#include "board.hh"
#include "createShape.hh"
#include "utilities.hh"
#include "UI.hh"

#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

constexpr int gap = 40; // Gap
constexpr int gapRight = 80;
constexpr int rectSize = 280;
constexpr int tileSize = rectSize + gap;
constexpr float cornerRadius = 20.f;

constexpr int headerHeight = 240;
constexpr int margin = 200; // Margin around the puzzle
constexpr int topMargin = 50;
constexpr int rightMargin = 50;
constexpr int bottomMargin = 160;
constexpr int sideMargin = 180;

constexpr int rightPanelWidth = 600; // Extra space on the right for music/hint

sf::Clock gameClock;   // Clock to track elapsed game time
int moveCount{0};      // Number of moves made by the player
bool gameWon = false;  // Flag indicating whether the puzzle has been solved
int finalTime = 0;     // Time taken to win (in seconds or chosen unit)
sf::Time winShownTime; // Duration for which the win screen/message is displayed

// Use main() only if you want to run the app with a console window
// int main(int argc, char *argv[])

// Standard Windows GUI entry point (no console window)
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main(int argc, char *argv[])
#endif

{
    auto window = createWindow(N, tileSize, margin, headerHeight, topMargin, rightPanelWidth);

    // ===== Add background music =====
    auto music = loadBackgroundMusic("assets/musics/bg_music.mp3");

    auto clickSound = loadSound("assets/musics/pick.wav");
    auto winSound = loadSound("assets/musics/win.mp3");

    // Initial board configuration (classic 15 puzzle)
    std::array<int, 16> board = {1, 2, 3, 4, 5, 6, 7, 8,
                                 9, 10, 11, 12, 13, 14, 15, 0};

    shuffleBoard(board); // Shuffle the board at start

    std::map<std::string, sf::Font> fonts;

    // Font files used for different UI elements
    std::map<std::string, std::string> fontFiles = {
        {"number", "assets/fonts/Montserrat-Bold.ttf"},
        {"title", "assets/fonts/Poppins-Bold.ttf"},
        {"info", "assets/fonts/Nunito-Regular.ttf"},
        {"button", "assets/fonts/Quicksand-Bold.otf"}};

    if (!loadFonts(fonts, fontFiles))
        return 1;

    int emptyIdx = std::find(board.begin(), board.end(), 0) - board.begin(); // index of empty tile
    bool musicPlaying = true;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            else if (auto *mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                // Calculate clicked tile position
                int x = (mouseButton->position.x - margin) / tileSize;
                int y = (mouseButton->position.y - headerHeight - topMargin) / tileSize;

                if (y >= 0 && y < N && x >= 0 && x < N)
                {
                    tryMoveTile(board, emptyIdx, x, y, moveCount, clickSound, music, winSound, gameClock, gameWon, finalTime, winShownTime);
                }
            }

            else if (auto *keyPress = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPress->code == sf::Keyboard::Key::R)
                {
                    // Reset board
                    board = {1, 2, 3, 4, 5, 6, 7, 8,
                             9, 10, 11, 12, 13, 14, 15, 0};

                    shuffleBoard(board);
                    emptyIdx = std::find(board.begin(), board.end(), 0) - board.begin();
                    moveCount = 0;
                    gameClock.restart();
                    gameWon = false;
                    finalTime = 0;
                    winShownTime = sf::Time::Zero;
                }

                // ===== Add shortcut key to toggle music =====
                else if (keyPress->code == sf::Keyboard::Key::M)
                {
                    if (musicPlaying)
                    {
                        musicPlaying = false;
                        music.pause();
                    }
                    else
                    {
                        music.play();
                        musicPlaying = true;
                    }
                }

                int ex = emptyIdx % N;
                int ey = emptyIdx / N;

                if (keyPress->code == sf::Keyboard::Key::Up && ey < N - 1)
                    tryMoveTile(board, emptyIdx, ex, ey + 1, moveCount, clickSound, music, winSound, gameClock, gameWon, finalTime, winShownTime);

                else if (keyPress->code == sf::Keyboard::Key::Down && ey > 0)
                    tryMoveTile(board, emptyIdx, ex, ey - 1, moveCount, clickSound, music, winSound, gameClock, gameWon, finalTime, winShownTime);

                else if (keyPress->code == sf::Keyboard::Key::Left && ex < N - 1)
                    tryMoveTile(board, emptyIdx, ex + 1, ey, moveCount, clickSound, music, winSound, gameClock, gameWon, finalTime, winShownTime);

                else if (keyPress->code == sf::Keyboard::Key::Right && ex > 0)
                    tryMoveTile(board, emptyIdx, ex - 1, ey, moveCount, clickSound, music, winSound, gameClock, gameWon, finalTime, winShownTime);
            }
        }

        // window.clear(sf::Color::White);
        window.clear(sf::Color(180, 140, 200)); // light purple background

        // Draw title
        sf::Text title(fonts["title"], "15 PUZZLE GAME", 80);
        title.setFillColor(sf::Color(128, 0, 128)); // purple color
        title.setStyle(sf::Text::Bold);
        centerText(title, margin, topMargin, N * tileSize, headerHeight);
        window.draw(title);

        // ===== Display elapsed time & move count =====
        int elapsedSeconds = static_cast<int>(gameClock.getElapsedTime().asSeconds());

        float RightX = margin + N * tileSize;
        float TopY = headerHeight + topMargin;

        drawUI(window, fonts["info"], musicPlaying, elapsedSeconds, finalTime, gameWon, moveCount, RightX, TopY, rightMargin, gapRight);

        drawBoard(window, board, fonts["number"], margin, headerHeight, topMargin, rectSize, cornerRadius);

        if (gameWon)
        {
            if (gameClock.getElapsedTime() - winShownTime < sf::seconds(3))
            {
                // Show semi-transparent overlay for win message
                sf::RectangleShape won(sf::Vector2f(window.getSize()));
                won.setFillColor(sf::Color(0, 0, 0, 150));
                window.draw(won);

                sf::Text winText(fonts["title"], " YOU WIN! ", 80);
                winText.setFillColor(sf::Color::Yellow);
                winText.setStyle(sf::Text::Bold);
                centerText(winText, 0, window.getSize().y / 2.f - 100, window.getSize().x, 200);
                window.draw(winText);
            }
            else
            {
                // Overlay expired, stop win sound and resume background music
                if (winSound)
                    winSound->stop();

                music.play();
            }
        }

        window.display();
    }

    music.stop(); // Stop background music when window closes
}
