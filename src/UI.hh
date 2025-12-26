
#pragma once

#include <SFML/Graphics.hpp>

// Draw the right-side UI panel with game information
// Displays elapsed time, final time (if won), move count, and music status
void drawUI(sf::RenderWindow &window,
            const sf::Font &fontInfo, // font used for info text
            bool musicPlaying,        // whether background music is currently playing
            int elapsedSeconds,       // current elapsed time in seconds
            int finalTime,            // time taken to win (if gameWon is true)
            bool gameWon,             // flag indicating if the puzzle is solved
            int moveCount,            // number of moves made
            float RightX,             // starting X position of the right panel
            float TopY,               // starting Y position of the right panel
            float rightMargin,        // margin on the right side
            float gapRight);          // gap between UI elements in the right panel

// Create and return the main game window
// Window size is calculated based on puzzle size, margins, header height, and right panel width
sf::RenderWindow createWindow(
    unsigned int N,              // puzzle dimension (e.g., 4 for 4x4)
    unsigned int tileSize,       // size of each tile
    unsigned int margin,         // margin around the puzzle
    unsigned int headerHeight,   // height of the header area
    unsigned int topMargin,      // margin above the puzzle
    unsigned int rightPanelWidth // extra space on the right for UI panel
);
