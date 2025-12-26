#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <map>

// Load multiple fonts from given file paths into a font map
// Returns true if all fonts are loaded successfully
bool loadFonts(std::map<std::string, sf::Font> &fonts,
               const std::map<std::string, std::string> &fontFiles);

// Load background music from a file path
// Returns an sf::Music object that can be played/paused/stopped
sf::Music loadBackgroundMusic(const std::string &path);

// Load a sound effect from a file path
// Returns a unique_ptr to sf::Sound for safe memory management
std::unique_ptr<sf::Sound> loadSound(const std::string &path);
