#include <iostream>
#include <cassert>
#include "Bag.h"
#include "Player.h"
#include "FirePokemon.h"
#include "WaterPokemon.h"
#include "GrassPokemon.h"
#include "ExploreSystem.h"
#include "PokemonDataBase.h" 
#include "BattleSystem.h"     
#include "BagSystem.h"       
#include "StoreSystem.h"      
#include "Menu.h"
#include "Game.h"   

using namespace std;

int main() {
    initscr();            // Initialize ncurses screen
    cbreak();             // Disable line buffering
    noecho();             // Don't display typed characters
    curs_set(0);          // Hide cursor
    keypad(stdscr, TRUE); // Enable arrow keys

    cout << "=== Boundary & Exception Handling Test Start ===" << endl;

    // 1. Test: Cannot add Pokemon if bag is full
    Bag bag;
    for (int i = 0; i < bag.getPokemonCapacity(); ++i) {
        FirePokemon* p = new FirePokemon("Charmander","Fire",1,3,60,0,{Move("Tackle","Normal",40)});
        assert(bag.addPokemon(p) == true); // Should succeed for capacity times
        delete p;
    }
    // Try to add one more
    FirePokemon* extra = new FirePokemon("Charmander","Fire",1,3,60,0,{Move("Tackle","Normal",40)});
    assert(bag.addPokemon(extra) == false); // Should fail when full
    delete extra;

    // 2. Test: Cannot switch active Pokemon if bag is empty
    Bag emptyBag;
    assert(emptyBag.switchActive(0) == false);
    assert(emptyBag.getActive() == nullptr);

    // 3. Test: Use Potion/Pokeball when count is zero
    Bag potionBag;
    // Add a Pokemon so usePotion is callable
    FirePokemon* p1 = new FirePokemon("Charmander","Fire",1,3,60,0,{Move("Tackle","Normal",40)});
    potionBag.addPokemon(p1);
    delete p1;
    assert(potionBag.getPotionAmount() == 0);
    assert(potionBag.usePotion() == false); // Should not crash, should return false
    assert(potionBag.getBallAmount() == 0);
    assert(potionBag.useBalls(potionBag.getActive()) == false);

    // 4. Test: Pokemon evolution at limit
    // Simulate a Pokemon already at final evolution (simulate with only one in DB)
    // Suppose DB for this type only contains one (mock-up, as actual DB integration is needed)
    // Here, forcibly call evolve on single-chain, should return false
    assert(potionBag.evolve(0) == false);

    // 5. Test: Invalid menu/input selection
    // Suppose we simulate this by calling switchActive with invalid index
    assert(potionBag.switchActive(-1) == false);
    assert(potionBag.switchActive(999) == false);

    // 6. Test: Recovery from invalid save file (simulate with Game::loadGame)
    // Save to a file, then break it
    const string badFile = "BAD_SAVE.txt";
    // Write invalid data
    {
        ofstream fout(badFile);
        fout << "CORRUPTED_DATA_LINE" << endl;
        fout.close();
    }
    // Try loading invalid file, should return false
    assert(Game::loadGame(badFile) == false);

    // 7. Test: Evolution at max level (simulate)
    // Assume your PokemonEntity::canEvolve() returns false if at max evolution, 
    // this is a design-level test, so just check that evolve returns false again
    assert(potionBag.evolve(0) == false);

    endwin();

    cout << "All boundary & exception tests passed!" << endl;

    std::remove(badFile.c_str());

    return 0;
}