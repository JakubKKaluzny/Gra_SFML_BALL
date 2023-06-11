#pragma once
#include <SFML/Graphics.hpp>


class Background : public sf::Drawable{
public:
	Background();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~Background();
private:
    sf::Texture grass;

};
