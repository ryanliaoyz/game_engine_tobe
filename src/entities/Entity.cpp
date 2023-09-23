//
// Created by Yunze Liao on 9/22/23.
//

#include "../../include/entities/Entity.h"

Entity::Entity(int x, int y, int health) : x(x), y(y), health(health) {}

int Entity::getX() const { return x; }
void Entity::setX(int x) { this->x = x; }
int Entity::getY() const { return y; }
void Entity::setY(int y) { this->y = y; }
int Entity::getHealth() const { return health; }
void Entity::setHealth(int health) { this->health = health; }

void Entity::move(int dx, int dy) {
    x += dx;
    y += dy;
    // Add boundary checks or other logic if needed
}

int Entity::getHeight() {
    return height;
}

int Entity::getWidth() {
    return width;
}

float Entity::getSpeedX() {
    return speedX;
}

void Entity::setSpeedX(float speedX) {
    this->speedX = speedX;
}

float Entity::getSpeedY() {
    return speedY;
}

void Entity::setSpeedY(float speedY) {
    this->speedY = speedY;
}

void Entity::applyGravity() {
    if (!isOnGround) {
        speedY += GRAVITY;
        y += speedY;
    }
}

void Entity::jump() {
    if (isOnGround) {
        speedY -= GRAVITY;
        isOnGround = false;
    }
}

void Entity::land(float groundY) {
    y = groundY;
    speedY = 0;
    isOnGround = true;
}

