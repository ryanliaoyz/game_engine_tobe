//
// Created by Yunze Liao on 9/22/23.
//
#include <iostream>
#include <SDL2/SDL.h>
#include "../include/world/world_generator.h"
#include "../include/entities/Player.h"
#include "../include/utilities/Camera.h"
#include "../include/config/GAME_CONFIG.h"
#include "../include/world/World_Handler.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Terraria-like Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    WorldGenerator world((SCREEN_WIDTH / TILE_SIZE) * 2, SCREEN_HEIGHT / TILE_SIZE);
    world.generate();

    Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,0,0); // Center the player
    Camera camera;
    WorldHandler worldHandler(world);

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE:
                        player.jump();// Player moves up
                        break;
                    case SDLK_d:
                        player.move(-player.getSpeedX(), 0); // Player moves left
                        break;
                    case SDLK_a:
                        player.move(player.getSpeedX(), 0); // Player moves right
                        break;
                }
                camera.centerOnPlayer(player, SCREEN_WIDTH, SCREEN_HEIGHT);
            }
        }
        worldHandler.handleEntityPhysics(player);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE; ++x) {
            for (int y = 0; y < SCREEN_HEIGHT / TILE_SIZE; ++y) {

                int worldX = x - (camera.getX() / TILE_SIZE);
                int worldY = y - (camera.getY() / TILE_SIZE);

                TileType tile = world.getTile(worldX, worldY).getTileType();
                SDL_Rect tileRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

                switch (tile) {
                    case TileType::AIR:
                        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue for air
                        break;
                    case TileType::DIRT:
                        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);  // Brown for dirt
                        break;
                        // TODO: Handle other tile types
                }

                SDL_RenderFillRect(renderer, &tileRect);
            }
        }


        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

// Get the player's position and dimensions
        SDL_Rect playerRect = {
                (SCREEN_WIDTH / 2),  // Since player is always at the center
                (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 8),
                player.getWidth(),
                player.getHeight()
        };

        SDL_RenderFillRect(renderer, &playerRect);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}