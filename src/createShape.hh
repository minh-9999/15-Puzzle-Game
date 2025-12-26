#pragma once

#include <SFML/Graphics.hpp>

// Helper function to center text
void centerText(sf::Text &text, float x, float y, float width, float height);

sf::ConvexShape createRoundedRect(float width, float height, float radius, int pointCount = 8);