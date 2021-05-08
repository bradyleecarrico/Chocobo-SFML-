#include <SFML\Audio.hpp>

class soundeffect
{
public:
    soundeffect(sf::String filename);
    ~soundeffect();
    void playsound();

    sf::SoundBuffer buffer;
    sf::Sound sound;
};

