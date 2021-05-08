#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Object();

	void Draw(sf::RenderWindow& window);

	sf::RectangleShape body;
private:

};

