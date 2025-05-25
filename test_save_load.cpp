// test_save_load.cpp
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstdio>
#include "Game.h"
#include "Player.h"
#include "Bag.h"
#include "FirePokemon.h"
#include "GrassPokemon.h"
#include "WaterPokemon.h"
#include "PokemonDataBase.h"

// Use a separate file for testing
const std::string TEST_SAVE_FILE = "test_savefile.txt";

int main() {
    initscr();            // Initialize ncurses screen
    cbreak();             // Disable line buffering
    noecho();             // Don't display typed characters
    curs_set(0);          // Hide cursor
    keypad(stdscr, TRUE); // Enable arrow keys

    // 1. Test game initialization (initGame)
    Game::initGame();

    // Should have at least 1 Pokémon, 3 potions, 3 balls, 200 gold
    assert(player.getBag().getPokemonAmount() >= 1);
    assert(player.getBag().getPotionAmount() == 3);
    assert(player.getBag().getBallAmount() == 3);
    assert(player.getMoneyAmount() == 200);

    // Add some changes: more Pokémon, more items, more gold
    std::vector<Move> moves = {Move("TestMove", "Normal", 10)};
    player.getBag().addPokemon(new FirePokemon("Charmander", "Fire", 5, 1, 50, 100, moves));
    player.getBag().addBalls(2);
    player.getBag().addPotion(1);
    player.addMoney(50);

    int pokemonCountBefore = player.getBag().getPokemonAmount();
    int potionsBefore = player.getBag().getPotionAmount();
    int ballsBefore = player.getBag().getBallAmount();
    int moneyBefore = player.getMoneyAmount();
    std::string nameBefore = player.getBag().getPokemonAt(0)->getName();

    // 2. Save game
    Game::saveGame(TEST_SAVE_FILE);

    // 3. Reset player state (simulate exiting the game)
    player.getBag().clear(); // Assume you have clear/reset for bag, or else reconstruct player/bag
    player.setMoneyAmount(0);

    assert(player.getBag().getPokemonAmount() == 0);
    assert(player.getBag().getPotionAmount() == 0);
    assert(player.getBag().getBallAmount() == 0);
    assert(player.getMoneyAmount() == 0);

    // 4. Load game from save
    bool loaded = Game::loadGame(TEST_SAVE_FILE);
    assert(loaded);

    // 5. Check for consistency of all values
    assert(player.getBag().getPokemonAmount() == pokemonCountBefore);
    assert(player.getBag().getPotionAmount() == potionsBefore);
    assert(player.getBag().getBallAmount() == ballsBefore);
    assert(player.getMoneyAmount() == moneyBefore);
    assert(player.getBag().getPokemonAt(0)->getName() == nameBefore);

    // 6. Check Pokémon attributes loaded correctly
    PokemonEntity* testFire = nullptr;
    for(int i = 0; i < player.getBag().getPokemonAmount(); ++i) {
        if(player.getBag().getPokemonAt(i)->getName() == "Charmander") {
            testFire = player.getBag().getPokemonAt(i);
        }
    }
    assert(testFire != nullptr);
    assert(testFire->getLevel() == 5);
    assert(testFire->getType() == "Fire");

    endwin();

    std::cout << "Game save/load test passed! All data consistent." << std::endl;

    // 7. Clean up test save file
    std::remove(TEST_SAVE_FILE.c_str());

    return 0;
}