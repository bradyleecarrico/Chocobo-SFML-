#include "sound.h"

soundeffect::soundeffect(sf::String filename)
{
	buffer.loadFromFile(filename);
	sound.setBuffer(buffer);
}

soundeffect::~soundeffect(){}

void soundeffect::playsound() {
	sound.play();
}