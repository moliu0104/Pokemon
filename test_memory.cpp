#include <iostream>
#include <vector>
#include <cassert>
#include "Bag.h"
#include "Player.h"
#include "FirePokemon.h"
#include "BattleSystem.h"

// Helper to create a simple Pokemon
FirePokemon* createSamplePokemon() {
    std::vector<Move> moves = { Move("Tackle", "Normal", 40) };
    return new FirePokemon("Charmander", "Fire", 5, 1, 60, 0, moves);
}

int main() {
    // Test Bag's memory management
    {
        Bag* bag = new Bag();
        assert(bag->getPokemonAmount() == 0);

        // Add Pokemon
        for (int i = 0; i < 3; ++i) {
            FirePokemon* p = createSamplePokemon();
            bool added = bag->addPokemon(p);
            assert(added);
            delete p; // Make sure Bag does its own copy/clone
        }
        assert(bag->getPokemonAmount() == 3);

        // Test getActive and getPokemonAt
        PokemonEntity* act = bag->getActive();
        assert(act != nullptr);

        for (int i = 0; i < 3; ++i) {
            assert(bag->getPokemonAt(i) != nullptr);
        }

        // Clear all pokemons (simulates player clears bag or quits)
        bag->clear();
        assert(bag->getPokemonAmount() == 0);

        // Delete bag, should not leak memory
        delete bag;
    }

    // Test Player's dynamic Bag management
    {
        Player* player = new Player();
        assert(player->getMoneyAmount() == 0);

        // Add pokemon to player's bag
        FirePokemon* p = createSamplePokemon();
        player->addPokemonToBag(p);
        delete p; // Bag should clone/copy

        // Check active pokemon
        assert(player->getActivePokemon() != nullptr);

        // Delete player, should not leak
        delete player;
    }

    // Test BattleSystem dynamic creation and deletion
    {
        // Need at least one Pokemon in player bag before battle
        Player* player = new Player();
        FirePokemon* p = createSamplePokemon();
        player->addPokemonToBag(p);
        delete p;

        // Create a wild Pokemon
        FirePokemon* wild = createSamplePokemon();

        // Start a battle system (even if just create and delete)
        BattleSystem* battle = new BattleSystem(wild);
        delete battle;
        delete wild;
        delete player;
    }

    std::cout << "Memory management & dynamic allocation tests passed." << std::endl;
    return 0;
}