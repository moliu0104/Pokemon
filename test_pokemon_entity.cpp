#include <iostream>
#include <cassert>
#include "FirePokemon.h"
#include "GrassPokemon.h"
#include "WaterPokemon.h"
#include "PokemonDataBase.h"

// Helper: make test Move and Pokemon
Move testMove("Tackle", "Normal", 10);
std::vector<Move> testMoves = {testMove};

FirePokemon* makeFire(int level = 1, int stage = 1, int maxhp = 50, int exp = 0) {
    return new FirePokemon("Charmander", "Fire", level, stage, maxhp, exp, testMoves);
}

int main() {
    // 1. HP changes and clamp test (cannot exceed max, below 0)
    FirePokemon* p = makeFire(10, 2, 100);
    p->resetHP(80);
    p->heal(50); // heal will clamp
    assert(p->getCurrentHP() == 100); // Should not exceed maxHP
    p->resetHP(-5);
    p->clampHP();
    assert(p->getCurrentHP() == 0); // Should not go below 0

    // 2. Experience addition, level-up & multi-level upgrade
    p->addExp(250); // Should be enough for 2 levels if 100 per level
    assert(p->canLevelUp());
    p->levelUp();
    assert(p->getLevel() == 12); // 10 + 2

    // 3. isFainted(), heal(), addExp() basic status method
    p->resetHP(0);
    assert(p->isFainted() == true); // HP 0 = fainted
    p->heal(30);
    assert(p->isFainted() == false); // Healed, not fainted



    // Clean up
    delete p;

    std::cout << "\nPokemonEntity feature test passed!\n" << std::endl;
    return 0;
}