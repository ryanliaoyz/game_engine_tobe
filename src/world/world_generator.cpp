// WorldGenerator.cpp

#include "../../include/world/world_generator.h"

WorldGenerator::WorldGenerator(int width, int height) :
        width(width),
        height(height),
        tiles(width, std::vector<Tile>(height, Tile(TileType::AIR)))
{
    // Seed the random number generator
    std::random_device rd;
    rng = std::mt19937(rd());
}

void WorldGenerator::generate() {
    std::uniform_int_distribution<int> heightDist(0, height / 20); // Random height variation

    // Introduce randomness by allowing the dirt level to vary.
    for (int x = 0; x < width; ++x) {
        int randomHeight = height / 2 + heightDist(rng); // Halfway down the screen + a random offset

        for (int y = 0; y < height; ++y) {
            if (y > randomHeight) {
                tiles[x][y] = Tile(TileType::DIRT);
            }
        }
    }
}

Tile WorldGenerator::getTile(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[x][y];
    }
    return Tile(TileType::AIR); // Default to AIR if out of bounds.
}
