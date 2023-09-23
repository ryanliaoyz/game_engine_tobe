//
// Created by Yunze Liao on 9/22/23.
//
#pragma once
// WorldGenerator.h

#ifndef GAME_ENGINE_TOBE_WORLD_GENERATOR_H
#define GAME_ENGINE_TOBE_WORLD_GENERATOR_H

#include <vector>
#include <random>
#include "Tile.h"

class WorldGenerator {
public:
    // Constructor
    WorldGenerator(int width, int height);

    // Public member functions
    void generate();
    Tile getTile(int x, int y) const;

private:
    // Private member variables
    int width;
    int height;
    std::vector<std::vector<Tile>> tiles;  // 2D vector to store the tiles of the world
    std::mt19937 rng;  // Random number generator for world generation
};

#endif //GAME_ENGINE_TOBE_WORLD_GENERATOR_H