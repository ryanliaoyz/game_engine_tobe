//
// Created by Yunze Liao on 9/22/23.
//

#include "../../include/world/Tile.h"

Tile::Tile(TileType type) : type(type) {}

bool Tile::isPenetrable() const {
    switch (type) {
        case TileType::AIR:
            return true;
        case TileType::DIRT:
            return false;
            // ... cases for other tile types
    }
    return false;
}