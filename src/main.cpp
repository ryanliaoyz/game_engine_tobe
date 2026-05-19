#include "world.h"
#include <iostream>

struct Position { float x, y; };
struct Velocity { float dx, dy; };
struct Genome { int seed; };

int main() {
    tobe::World world;

    std::cout << "=== entity creation ===\n";
    auto e1 = world.create_entity();
    auto e2 = world.create_entity();
    auto e3 = world.create_entity();
    std::cout << "e1=" << e1 << " e2=" << e2 << " e3=" << e3 << "\n\n";

    std::cout << "=== adding components ===\n";
    world.add_component<Position>(e1, Position{1.0f, 2.0f});
    world.add_component<Velocity>(e1, Velocity{0.1f, 0.0f});
    world.add_component<Position>(e2, Position{10.0f, 20.0f});
    world.add_component<Genome>(e3, Genome{42});
    std::cout << "added Position+Velocity to e1, Position to e2, Genome to e3\n\n";

    std::cout << "=== basic gets ===\n";
    auto* p1 = world.get_component<Position>(e1);
    std::cout << "e1 Position: (" << p1->x << ", " << p1->y << ")\n";
    auto* v1 = world.get_component<Velocity>(e1);
    std::cout << "e1 Velocity: (" << v1->dx << ", " << v1->dy << ")\n";
    auto* g3 = world.get_component<Genome>(e3);
    std::cout << "e3 Genome seed: " << g3->seed << "\n\n";

    std::cout << "=== has checks ===\n";
    std::cout << "e1 has Position: " << world.has_component<Position>(e1) << "\n";
    std::cout << "e1 has Velocity: " << world.has_component<Velocity>(e1) << "\n";
    std::cout << "e1 has Genome:   " << world.has_component<Genome>(e1) << "\n";
    std::cout << "e2 has Velocity: " << world.has_component<Velocity>(e2) << "\n";
    std::cout << "e3 has Position: " << world.has_component<Position>(e3) << "\n\n";

    std::cout << "=== overwrite behavior ===\n";
    world.add_component<Position>(e1, Position{99.0f, 99.0f});
    auto* p1_new = world.get_component<Position>(e1);
    std::cout << "after re-add e1 Position: (" << p1_new->x << ", " << p1_new->y << ")\n";
    std::cout << "(if these are 1,2 then emplace did NOT overwrite; if 99,99 it did)\n\n";

    std::cout << "=== get on nonexistent ===\n";
    auto* p_missing = world.get_component<Position>(999);
    std::cout << "get<Position>(999) is null: " << (p_missing == nullptr) << "\n";
    auto* g_e1 = world.get_component<Genome>(e1);
    std::cout << "get<Genome>(e1) is null:    " << (g_e1 == nullptr) << "\n\n";

    std::cout << "=== remove behavior ===\n";
    std::cout << "remove<Position>(e1): " << world.remove_component<Position>(e1) << " (was present)\n";
    std::cout << "remove<Position>(e1): " << world.remove_component<Position>(e1) << " (now absent)\n";
    std::cout << "remove<Genome>(e1):   " << world.remove_component<Genome>(e1) << " (never had Genome)\n\n";

    std::cout << "=== const access ===\n";
    const tobe::World& cw = world;
    auto* p2_const = cw.get_component<Position>(e2);
    std::cout << "const e2 Position: (" << p2_const->x << ", " << p2_const->y << ")\n";
    std::cout << "const has<Velocity>(e1): " << cw.has_component<Velocity>(e1) << "\n";
    std::cout << "const get<Genome>(e1) null: " << (cw.get_component<Genome>(e1) == nullptr) << "\n\n";

    std::cout << "=== destroy_entity ===\n";
    world.destroy_entity(e1);
    std::cout << "after destroy e1, has Velocity:  " << world.has_component<Velocity>(e1) << "\n";
    std::cout << "after destroy e1, e2 Position:   ";
    auto* p2_after = world.get_component<Position>(e2);
    if (p2_after) std::cout << "(" << p2_after->x << ", " << p2_after->y << ")\n";
    else std::cout << "null\n";
    std::cout << "after destroy e1, e3 Genome:     " << world.has_component<Genome>(e3) << "\n";

    return 0;
}
