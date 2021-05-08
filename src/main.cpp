/*
    "Can you make a chicken that eats eggs and gets bigger every time it eats the egg?"

    Happy birthday kiddo!
*/
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "player.h"
#include "object.h"
#include "sound.h"
#include <cstdlib>
#include <ctime>

int main()
{
    //window
    sf::RenderWindow window(sf::VideoMode(800, 500), "Chocobo", sf::Style::Close | sf::Style::Titlebar);

    //egg coordinates
    float eggX = 50.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (750.0 - 50.0)));
    float eggY = 50.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (350.0 - 50.0)));

    //music + SFX
    soundeffect whiteMagesTheme("audio/white_mages_theme.wav");
    whiteMagesTheme.playsound();    
    sf::SoundBuffer buffer1;
    buffer1.loadFromFile("audio/peck.wav");
    sf::Sound peck;
    peck.setBuffer(buffer1);

    //textures
    sf::Texture chocoboTexture;
    chocoboTexture.loadFromFile("images/chocobo fixed.png");
    sf::Texture grassTexture;
    grassTexture.loadFromFile("images/grass.png");
    sf::Texture wallTexture1;
    wallTexture1.loadFromFile("images/wall1.png");
    sf::Texture wallTexture2;
    wallTexture2.loadFromFile("images/wall2.png");
    sf::Texture treeTexture;
    treeTexture.loadFromFile("images/tree.png");
    sf::Texture transparent;
    transparent.loadFromFile("images/1x1.png");

    //objects
    Player chocobo(&chocoboTexture, sf::Vector2u(9, 2), 0.15f, 200.0f);
    Object grass(&grassTexture, sf::Vector2f(800.0f, 500.0f), sf::Vector2f(400.0f, 250.0f));
    Object wall1(&wallTexture1, sf::Vector2f(800.0f, 20.0f), sf::Vector2f(400.0f, 10.0f));
    Object wall2(&wallTexture1, sf::Vector2f(800.0f, 20.0f), sf::Vector2f(400.0f, 490.0f));
    Object wall3(&wallTexture2, sf::Vector2f(20.0f, 500.0f), sf::Vector2f(10.0f, 250.0f));
    Object wall4(&wallTexture2, sf::Vector2f(20.0f, 500.0f), sf::Vector2f(790.0f, 250.0f));
    Object tree(&treeTexture, sf::Vector2f(150.0f, 150.0f), sf::Vector2f(400.0f, 215.0f));
    Object treebox(&transparent, sf::Vector2f(66.0f, 30.0f), sf::Vector2f(410.0f, 257.0f));

    //text objects
    sf::Font eightBit;
    eightBit.loadFromFile("fonts/eggs.ttf");
    std::string happybirthday = "HAPPYBIRTHDAY!";
    int snumber = 0;
    sf::Text seed(happybirthday[snumber], eightBit, 40);
    seed.setFillColor(sf::Color::White);
    seed.setOutlineColor(sf::Color::Black);
    seed.setOutlineThickness(2.0f);

    //time
    float deltaTime = 0.0f;
    sf::Clock clock;
    sf::Clock elapsed;

    //application loop
    while (window.isOpen())
    {
        //reset time
        deltaTime = clock.restart().asSeconds();

        //repeat music
        if (elapsed.getElapsedTime().asSeconds() > 181) {
            whiteMagesTheme.playsound();
            elapsed.restart().asSeconds();
        }

        //detect events
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            sf::Clock wait;
            while (wait.getElapsedTime().asSeconds() < 0.5f) {
            }
            window.close();
        }

        //update   
        chocobo.Update(deltaTime);
        seed.setPosition(eggX, eggY);
        
        //check collision
        chocobo.checkColliding(wall1, wall2, wall3, wall4, treebox);

        //chocobo interaction with egg
        if (chocobo.body.getGlobalBounds().intersects(seed.getGlobalBounds())) {
            seed.setFillColor(sf::Color::Black);
            seed.setOutlineColor(sf::Color::White);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                if (chocobo.animation.currentImage.x + chocobo.addColumn > 9) {
                    peck.play();
                    if (chocobo.chocosize.x < 145) {
                        chocobo.chocosize.x++;
                        chocobo.chocosize.y++;
                    }
                    eggX = 50.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (750.0 - 50.0)));
                    eggY = 50.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (350.0 - 50.0)));
                    //seed can't appear near the tree
                    while ((eggX > 325 && eggX < 475 && eggY > 140 && eggY < 290) || 
                        chocobo.body.getGlobalBounds().intersects(seed.getGlobalBounds())) {
                        eggX = 50.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (750.0 - 50.0)));
                        eggY = 50.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (350.0 - 50.0)));
                        seed.setPosition(eggX, eggY);
                    }
                    snumber++;
                    if (snumber > 13){
                        snumber = 0;
                    }
                    seed.setString(happybirthday[snumber]);                    
                }
            }
        }
        else {
            seed.setFillColor(sf::Color::White);
            seed.setOutlineColor(sf::Color::Black);
        }
        
        //clear, draw, display
        window.clear();
        grass.Draw(window);
        window.draw(seed);
        chocobo.Draw(window);
        wall1.Draw(window);
        wall2.Draw(window);
        wall3.Draw(window);
        wall4.Draw(window);
        tree.Draw(window);
        window.display();
    }
    return 0;
}