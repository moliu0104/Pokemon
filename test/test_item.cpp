#include <iostream>
#include <cassert>
#include "Potion.h"
#include "PokemonBall.h"
#include "PokemonDataBase.h"
#include "FirePokemon.h"
#include "GrassPokemon.h"
#include "WaterPokemon.h"
#include "Bag.h"
#include "Player.h"
#include "Menu.h"

// Helper move for testing
Move testMove("Tackle", "Normal", 10);

// Create a simple Pokemon
FirePokemon* makeFire(int lv = 1, int hp = 100) {
    std::vector<Move> moves = {testMove};
    return new FirePokemon("Charmander", "Fire", lv, 1, hp, 0, moves);
}

int main() {
    initscr();            // Initialize ncurses screen
    cbreak();             // Disable line buffering
    noecho();             // Don't display typed characters
    curs_set(0);          // Hide cursor
    keypad(stdscr, TRUE); // Enable arrow keys

    // 1. Potion use: test healing and potion depletion
    Bag bag;
    bag.addPokemon(makeFire(1, 50));
    bag.setPotionsAmount(1);
    PokemonEntity* pk = bag.getPokemonAt(0);
    pk->resetHP(10); // Set low HP

    // Use potion
    bool used = bag.usePotion();
    assert(used == true); // Should be used
    assert(pk->getCurrentHP() > 10); // HP increased
    assert(bag.getPotionAmount() == 0); // Potion depleted

    // Try use again when no potion
    bool used2 = bag.usePotion();
    assert(used2 == false); // No potion left

    // 2. PokemonBall: capture wild pokemon, probability and full bag
    bag.setBallAmount(1);
    FirePokemon* wild = makeFire(1, 20); // Lower HP to increase catch chance

    int bagCount = bag.getPokemonAmount();
    bool captured = bag.useBalls(wild);
    // Because catching is probabilistic, we just check ball count decrease
    assert(bag.getBallAmount() == 0);

    // If catch success, number of pokemon in bag increases (unless full)
    if (captured) {
        assert(bag.getPokemonAmount() == bagCount + 1);
    } else {
        assert(bag.getPokemonAmount() == bagCount); // Not caught
    }

    // Test full bag: fill up to 6 pokemons
    while (bag.getPokemonAmount() < 6) {
        bag.addPokemon(makeFire());
    }
    bag.setBallAmount(1);
    FirePokemon* wild2 = makeFire(1, 20);
    bool captured2 = bag.useBalls(wild2);
    // If full, capture will fail
    assert(bag.getBallAmount() == 0);
    assert(bag.getPokemonAmount() == 6);

    endwin();

    std::cout << "\nPotion & PokemonBall feature test passed!\n" << std::endl;
    return 0;
}