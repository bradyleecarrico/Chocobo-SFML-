#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public: //functions
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();
	void Update(int row, float deltaTime, bool& idle, unsigned& addColumn, unsigned& addRow);

public: //variables
	sf::IntRect uvRect;
	sf::Vector2u currentImage;

private: //functions
	sf::Vector2u imageCount;	

	float totalTime;
	float switchTime;
};

