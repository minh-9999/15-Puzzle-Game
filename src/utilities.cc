#include "utilities.hh"
#include <iostream>

// Load multiple fonts from given file paths into a font map
// Returns true if all fonts are loaded successfully, false if any font fails
bool loadFonts(std::map<std::string, sf::Font> &fonts,
               const std::map<std::string, std::string> &fontFiles)
{
    for (const auto &[name, path] : fontFiles)
    {
        sf::Font font;
        if (!font.openFromFile(path))
        {
            // Print error if font file cannot be found or loaded
            std::cerr << "Font " << name << " not found at " << path << "\n";
            return false;
        }
        // Store loaded font in the map under its name
        fonts[name] = std::move(font);
    }
    return true;
}

// Load background music from a file path
// If successful, sets looping and starts playing immediately
// Returns an sf::Music object (empty if loading failed)
sf::Music loadBackgroundMusic(const std::string &path)
{
    sf::Music music;
    if (!music.openFromFile(path))
    {
        // Print error if music file cannot be found
        std::cerr << "Music file not found!\n";
    }
    else
    {
        music.setLooping(true); // repeat indefinitely
        music.play();           // start playback
    }

    return music;
}

// Load a sound effect from a file path
// Returns a unique_ptr to sf::Sound if successful, nullptr if loading failed
std::unique_ptr<sf::Sound> loadSound(const std::string &path)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(path))
    {
        // Print error if sound file cannot be found
        std::cerr << path << " not found!\n";
        return nullptr;
    }

    // Create a sound object using the loaded buffer
    return std::make_unique<sf::Sound>(buffer);
}
