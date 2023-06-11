#include "Triangle.h"
#include <random>

Triangle::Triangle(float x, float y, float size, float speed) : speed(speed) {
    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(0.f, 0.f));
    shape.setPoint(1, sf::Vector2f(size, 0.f));
    shape.setPoint(2, sf::Vector2f(size / 1 / 5.f, size));

    shape.setOrigin(size / 2.f, size / 2.f); // Set the origin to the center of the triangle

    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);

    generateRandomVelocity();
}

const sf::ConvexShape& Triangle::getShape() const {
    return shape;
}

void Triangle::update(sf::RenderWindow& window) {
    shape.move(velocity);

    // Check screen boundaries
    sf::FloatRect bounds = shape.getGlobalBounds();
    if (bounds.left < 0.f || bounds.left + bounds.width > window.getSize().x) {
        velocity.x *= -1.f;
    }
    if (bounds.top < 0.f || bounds.top + bounds.height > window.getSize().y) {
        velocity.y *= -1.f;
    }

    // Update rotation
    shape.rotate(rotationSpeed);
}

void Triangle::generateRandomVelocity() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-speed, speed);
    velocity.x = dist(gen);
    velocity.y = dist(gen);

    // Generate random rotation speed
    std::uniform_real_distribution<float> rotationDist(-3.f, 3.f);
    rotationSpeed = rotationDist(gen);
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape);
}
