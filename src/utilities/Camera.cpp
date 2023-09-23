//
// Created by Yunze Liao on 9/22/23.
//

#include "../../include/utilities/Camera.h"
Camera::Camera() : x(0), y(0) {}

void Camera::centerOnPlayer(const Player& player, int screenWidth, int screenHeight) {
    x = player.getX() - screenWidth / 2;
    y = player.getY() - screenHeight / 2;
}

int Camera::getX() const {
    return x;
}

int Camera::getY() const {
    return y;
}