//
// Created by Yunze Liao on 9/22/23.
//

#include "../../include/entities/Player.h"

Player::Player(int x, int y, int health, int lives) : Entity(x, y, health), lives(lives)  {
    height = 20;
    width = 10;
    speedX = 5;
}

int Player::getLives() const { return lives; }
void Player::setLives(int lives) { this->lives = lives; }
void Player::increaseLife() { lives++; }
void Player::decreaseLife() { lives--; }