#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable
{
public:
    Ball(float x, float y, float radius);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);
    void setVelocity(sf::Vector2f velocity);
    void move();
    const sf::CircleShape& getShape() const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    bool isDragging;
    sf::Vector2f originalPosition;
};

#endif
