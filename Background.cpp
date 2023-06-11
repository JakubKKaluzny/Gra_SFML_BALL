#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

class Background {
public:
    Background() {
        // Load texture
        if (!texture.loadFromFile("background.png")) {
            // Error if fails to load
            std::cerr << "Failed to load background.png" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Create sprite
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) {
        // Draw sprite on window
        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};
