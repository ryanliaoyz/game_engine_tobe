//
// Created by Yunze Liao on 9/22/23.
//
#pragma once
#ifndef GAME_ENGINE_TOBE_CAMERA_H
#define GAME_ENGINE_TOBE_CAMERA_H



#include "../entities/Player.h"

class Camera {
private:
    int x, y;

public:
    Camera();

    // This function will keep the player in the center of the screen by adjusting the camera's x and y.
    void centerOnPlayer(const Player& player, int screenWidth, int screenHeight);

    int getX() const;
    int getY() const;
};


#endif //GAME_ENGINE_TOBE_CAMERA_H
