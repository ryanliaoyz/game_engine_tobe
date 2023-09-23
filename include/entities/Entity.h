//
// Created by Yunze Liao on 9/22/23.
//
#pragma once
#ifndef GAME_ENGINE_TOBE_ENTITY_H
#define GAME_ENGINE_TOBE_ENTITY_H

class Entity {
protected:
    int x, y; // Position coordinates
    int health;
    int height, width;
    float speedX, speedY;
    bool isOnGround = false;
    const float GRAVITY = 1.0f;
    const float JUMP_STRENGTH = 10.0f;

public:
    Entity(int x, int y, int health);

    // Accessors and mutators for x, y, and health
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    int getHealth() const;
    void setHealth(int health);
    int getHeight();
    int getWidth();
    float getSpeedX();
    void setSpeedX(float speedX);
    float getSpeedY();
    void setSpeedY(float speedY);

    virtual void move(int dx, int dy);
    void applyGravity();
    void jump();
    void land(float groundY);
    // ... other methods common to all entities
};

#endif //GAME_ENGINE_TOBE_ENTITY_H
