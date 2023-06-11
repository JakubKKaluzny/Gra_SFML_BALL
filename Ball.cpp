#include "Ball.h"

Ball::Ball(float x, float y, float radius)
{
    shape.setPosition(x, y);
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Magenta);
    shape.setOrigin(radius, radius);

    isDragging = false;
    originalPosition = sf::Vector2f(x, y);
}

const sf::CircleShape& Ball::getShape() const {
    return shape;
}


void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape);
}

void Ball::update(sf::RenderWindow& window)
{
    if (isDragging)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        shape.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }

    // Check boundaries
    sf::Vector2f position = shape.getPosition();
    sf::FloatRect bounds = shape.getGlobalBounds();
    float radius = bounds.width / 2.0f;

    if (position.x - radius < 0)
    {
        position.x = radius;
    }
    else if (position.x + radius > window.getSize().x)
    {
        position.x = window.getSize().x - radius;
    }

    if (position.y - radius < 0)
    {
        position.y = radius;
    }
    else if (position.y + radius > window.getSize().y)
    {
        position.y = window.getSize().y - radius;
    }

    shape.setPosition(position);
}

void Ball::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left && shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            isDragging = true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left && isDragging)
        {
            isDragging = false;
            sf::Vector2f currentPosition = shape.getPosition();
            sf::Vector2f velocity = originalPosition - currentPosition;
            setVelocity(velocity);
        }
    }
}

void Ball::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}

void Ball::move()
{
    shape.move(velocity);
}

