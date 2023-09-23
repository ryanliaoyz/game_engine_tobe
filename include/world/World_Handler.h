//
// Created by Yunze Liao on 9/23/23.
//
#pragma once
#ifndef GAME_ENGINE_TOBE_WORLD_HANDLER_H
#define GAME_ENGINE_TOBE_WORLD_HANDLER_H


#include "../entities/Entity.h"
#include "world_generator.h"

class WorldHandler {
    WorldGenerator& world;  // Reference to the world/tiles

public:
    WorldHandler(WorldGenerator& w);
    void handleEntityPhysics(Entity& entity);
};


#endif //GAME_ENGINE_TOBE_WORLD_HANDLER_H
