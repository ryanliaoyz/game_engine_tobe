//
// Created by Yunze Liao on 9/22/23.
//

#pragma once
#ifndef GAME_ENGINE_TOBE_TILE_H
#define GAME_ENGINE_TOBE_TILE_H


enum class TileType {
    AIR,
    DIRT
};

class Tile {
public:
    Tile(TileType type);
    TileType getTileType() {return this->type;}
    // Define other properties of the tile
    bool isPenetrable() const;
    // ... Any other tile-specific methods

private:
    TileType type;
    // ... Any other tile-specific member variables
};

#endif //GAME_ENGINE_TOBE_TILE_H
