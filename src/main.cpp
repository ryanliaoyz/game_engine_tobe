#include "world.h"
#include "movement.h"
#include "components.h"
#include <iostream>

int main() {
    tobe::World world;
    
    auto e1 = world.create_entity();
    world.add_component<tobe::Position>(e1, {0.0f, 0.0f});
    world.add_component<tobe::Velocity>(e1, {1.0f, 2.0f});
    
    auto e2 = world.create_entity();
    world.add_component<tobe::Position>(e2, {10.0f, 10.0f});
    // e2 has no velocity — shouldn't move
    
    for (int tick = 0; tick < 3; ++tick) {
        tobe::movement::update(world, 0.1f);
        auto* p1 = world.get_component<tobe::Position>(e1);
        auto* p2 = world.get_component<tobe::Position>(e2);
        std::cout << "tick " << tick 
                  << ": e1=(" << p1->x << "," << p1->y << ")"
                  << " e2=(" << p2->x << "," << p2->y << ")\n";
    }
    
    return 0;
}
