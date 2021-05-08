#include "player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	//initializing list
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
    addColumn = 0;
    addRow = 0;
    colliding = false;

    //player properties
    body.setSize(chocosize);
    body.setOrigin(50.0f, 50.0f);
    body.setPosition(400.0f, 400.0f);
    body.setTexture(texture);

    buffer2.loadFromFile("audio/step 1.wav");
    step1.setBuffer(buffer2);
}

Player::~Player(){}

void Player::Update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);
    //bool idle = true;

    //keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        movement.y -= speed *deltaTime;        
        row = 1;
        this->addColumn = 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        movement.y += speed *deltaTime;
        row = 0;
        this->addColumn = 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        movement.x -= speed *deltaTime;
        row = 0;
        this->addColumn = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {       
        movement.x += speed *deltaTime;
        row = 1;
        this->addColumn = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        this->addColumn = 6;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
        this->addRow = 0;
    }
    /* For sprite sheet that has additional colors
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) {
        this->addRow = 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B)) {
        this->addRow = 4;
    }
    */

    //analyze if player is idle
    if (movement.x == 0.0 && movement.y == 0.0 && addColumn != 6) {
        idle = true;
    }
    else {
        idle = false;
    }

    //update player info
    animation.Update(row, deltaTime, idle, this->addColumn, this->addRow);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
    body.setSize(chocosize);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::checkColliding(Object object1, Object object2, Object object3, Object object4, Object object5)
{
    while ((this->body.getGlobalBounds().intersects(object1.body.getGlobalBounds()))) {
        this->body.move(0.0f, 0.1f);
    }
    while ((this->body.getGlobalBounds().intersects(object2.body.getGlobalBounds()))) {
        this->body.move(0.0f, -0.1f);
    }
    while ((this->body.getGlobalBounds().intersects(object3.body.getGlobalBounds()))) {
        this->body.move(0.1f, 0.0f);
    }
    while ((this->body.getGlobalBounds().intersects(object4.body.getGlobalBounds()))) {
        this->body.move(-0.1f, 0.0f);
    }
    while ((this->body.getGlobalBounds().intersects(object5.body.getGlobalBounds()))) {

        float chox = this->body.getPosition().x - object5.body.getPosition().x;
        float choy = this->body.getPosition().y - object5.body.getPosition().y;

        float overlapX = 83 - abs(chox);
        float overlapY = 65 - abs(choy);

        if (overlapY > overlapX) {
            if (chox < 0) {
                while ((this->body.getGlobalBounds().intersects(object5.body.getGlobalBounds()))) {
                    this->body.move(-0.1f, 0.0f);
                }
            }
            if (chox > 0) {
                while ((this->body.getGlobalBounds().intersects(object5.body.getGlobalBounds()))) {
                    this->body.move(0.1f, 0.0f);
                }
            }
        }
        else if (overlapY < overlapX) {
            if (choy < 0) {
                while ((this->body.getGlobalBounds().intersects(object5.body.getGlobalBounds()))) {
                    this->body.move(0.0f, -0.1f);
                }
            }
            if (choy > 0) {
                while ((this->body.getGlobalBounds().intersects(object5.body.getGlobalBounds()))) {
                    this->body.move(0.0f, 0.1f);
                }
            }
        }
    }
}