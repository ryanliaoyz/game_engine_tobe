//
// Created by Yunze Liao on 9/23/23.
//

#include "../../include/world/World_Handler.h"
#include "../../include/config/GAME_CONFIG.h"

WorldHandler::WorldHandler(WorldGenerator& w) : world(w) {}

void WorldHandler::handleEntityPhysics(Entity& entity) {
    // Get the tile below the entity
    int tileX = entity.getX() / TILE_SIZE;
    int tileY = (entity.getY() + entity.getHeight()) / TILE_SIZE;
    Tile tileBelow = world.getTile(tileX, tileY);

    entity.applyGravity();

    if (!tileBelow.isPenetrable()) {
        entity.land((tileY * TILE_SIZE) - entity.getHeight());  // Adjust entity's position to sit on the ground
    }
}