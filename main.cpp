#include <SFML/Graphics.hpp>
#include <sstream>
#include "background.cpp"
#include "Ball.h"
#include "Triangle.h"

int main() {
    enum class ScreenState { StartScreen, GameScreen, GameOverScreen };

    sf::RenderWindow window(sf::VideoMode(800, 600), "GALAXY BALL");

    Background background;
    Ball ball(400, 300, 20);

    Triangle triangle1(100, 200, 50, 1/4.f);
    Triangle triangle2(600, 400, 70, 1/5.f);
    Triangle triangle3(200, 100, 30, 1/6.f);
    Triangle triangle4(600, 400, 100, 1/7.f);

    bool trianglesCanMove = false;  // move
    bool collisionOccurred = false; // collision state

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font loading error
        return 1;
    }

    sf::Text startText;
    startText.setFont(font);
    startText.setString("Press 'SPACEBAR' to start");
    startText.setCharacterSize(28);
    startText.setFillColor(sf::Color::White);
    startText.setStyle(sf::Text::Bold);
    startText.setPosition(window.getSize().x / 2.f - startText.getGlobalBounds().width / 2.f,
                          window.getSize().y / 2.f - startText.getGlobalBounds().height / 2.f - 100);

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(window.getSize().x / 2.f - gameOverText.getGlobalBounds().width / 2.f,
                             window.getSize().y / 2.f - gameOverText.getGlobalBounds().height / 2.f);

    ScreenState currentScreen = ScreenState::StartScreen;

    sf::Clock clock;  // Timer
    sf::Time gameDuration;  // Game duration

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check if the spacebar is pressed
            if (currentScreen == ScreenState::StartScreen && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                currentScreen = ScreenState::GameScreen;
                trianglesCanMove = true;
                clock.restart();  // Start the timer when the game starts
            }

            ball.handleEvent(event);
        }

        // Check collision between ball and triangles
        if (!collisionOccurred && trianglesCanMove &&
            (triangle1.getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds()) ||
             triangle2.getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds()))) {
            collisionOccurred = true;
            trianglesCanMove = false;
            currentScreen = ScreenState::GameOverScreen;
            gameDuration = clock.getElapsedTime();  // Store the game timer
        }

        window.clear();

        background.draw(window);

        ball.update(window);
        window.draw(ball);

        if (currentScreen == ScreenState::StartScreen) {
            window.draw(startText);
        } else if (currentScreen == ScreenState::GameOverScreen) {
            window.draw(gameOverText);

            // Game time display
            sf::Text durationText;
            durationText.setFont(font);
            durationText.setCharacterSize(24);
            durationText.setFillColor(sf::Color::White);
            durationText.setStyle(sf::Text::Bold);
            durationText.setPosition(window.getSize().x / 2.f - durationText.getGlobalBounds().width / 2.f - 300,
                                     gameOverText.getPosition().y + gameOverText.getGlobalBounds().height + 50.f);

            // Format the game time as string
            std::stringstream ss;
            ss << "Game Duration: " << gameDuration.asSeconds() << "s";
            durationText.setString(ss.str());

            window.draw(durationText);
        } else {
            triangle1.update(window);
            triangle2.update(window);
            triangle3.update(window);
            triangle4.update(window);

            window.draw(triangle1);
            window.draw(triangle2);
            window.draw(triangle3);
            window.draw(triangle4);

            // Timer display
            sf::Text timerText;
            timerText.setFont(font);
            timerText.setCharacterSize(16);
            timerText.setFillColor(sf::Color::White);
            timerText.setStyle(sf::Text::Bold);
            timerText.setPosition(10.f, window.getSize().y - 30.f);

            // Get the elapsed time & convert to seconds
            sf::Time elapsedTime = clock.getElapsedTime();
            float seconds = elapsedTime.asSeconds();

            // Format the time as string
            std::stringstream ss;
            ss << "Time: " << seconds << "s";
            timerText.setString(ss.str());

            window.draw(timerText);
        }

        window.display();
    }

    return 0;
}
