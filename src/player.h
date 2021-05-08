#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "animation.h"
#include "Object.h"

class Player
{
public: //functions
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void checkColliding(Object object1, Object object2, Object object3, Object object4, Object object5);

public: //variables
	sf::RectangleShape body;
	int colliding;
	Animation animation;
	unsigned int addColumn;
	sf::Vector2f chocosize = sf::Vector2f(100.0f, 100.0f);

	sf::SoundBuffer buffer2;	
	sf::Sound step1;
	bool idle = true;
	

private: //variables	
	unsigned int row;
	unsigned int addRow;
	float speed;

	
};

