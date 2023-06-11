#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <SFML/Graphics.hpp>

class Triangle : public sf::Drawable {
public:
    Triangle(float x, float y, float size, float speed);
    void update(sf::RenderWindow& window);
    const sf::ConvexShape& getShape() const;

private:
    sf::ConvexShape shape;
    sf::Vector2f velocity;
    float speed;
    float rotationSpeed;

    void generateRandomVelocity();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
