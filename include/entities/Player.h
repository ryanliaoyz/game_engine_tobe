//
// Created by Yunze Liao on 9/22/23.
//

#ifndef GAME_ENGINE_TOBE_PLAYER_H
#define GAME_ENGINE_TOBE_PLAYER_H


#pragma once
#include "Entity.h"

class Player : public Entity {
private:
    int lives; // Additional attribute specific to player

public:
    Player(int x, int y, int health, int lives);

    int getLives() const;
    void setLives(int lives);
    void increaseLife();
    void decreaseLife();

    // Override any methods if needed or add new methods specific to Player
};

#endif //GAME_ENGINE_TOBE_PLAYER_H
