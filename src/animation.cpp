#include "animation.h"
#include <iostream>

//constructor
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
	//default values
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 1;

	//calculate height and width of each character
	uvRect.width  = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

//destructor
Animation::~Animation(){}

void Animation::Update(int row, float deltaTime, bool& idle, unsigned& addColumn, unsigned& addRow) {
	//set current row
	currentImage.y = row + addRow;
	//increment total time
	totalTime += deltaTime;

	//when time to switch
	if (idle == false) {
		if (totalTime >= switchTime) {
			//reset time
			totalTime -= switchTime;

			//add column
			currentImage.x++;

			//stop pecking animation
			if (currentImage.x == 9) {
				idle = true;
				addColumn = 0;
				currentImage.x = 1;
			}

			//reset column	
			if (currentImage.x > addColumn + 2 || currentImage.x < addColumn) {
				currentImage.x = addColumn;
			}
		}
	}
	else
		currentImage.x = 1 + addColumn;

	//set left and top offset
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top  = currentImage.y * uvRect.height;
}