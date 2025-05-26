// Create a simple Move for testing
Move testMove("Tackle", "Normal", 10);

// Helper functions to create test Pokémon with default values
FirePokemon* makeFire(int lv = 1) {
    std::vector<Move> moves = {testMove};
    return new FirePokemon("Charmander", "Fire", lv, 1, 100, 0, moves);
}
GrassPokemon* makeGrass(int lv = 1) {
    std::vector<Move> moves = {testMove};
    return new GrassPokemon("Bulbasaur", "Grass", lv, 1, 100, 0, moves);
}
WaterPokemon* makeWater(int lv = 1) {
    std::vector<Move> moves = {testMove};
    return new WaterPokemon("Squirtle", "Water", lv, 1, 100, 0, moves);
}

int main() {
    initscr();            // Initialize ncurses screen for UI testing
    cbreak();             // Disable line buffering for immediate input
    noecho();             // Do not display typed characters
    curs_set(0);          // Hide the cursor
    keypad(stdscr, TRUE); // Enable support for arrow keys

    // 1. Test: Add Pokemon to the bag, cannot exceed 6 slots
    Bag bag;
    assert(bag.getPokemonAmount() == 0);
    for (int i = 0; i < 6; ++i) {
        bool res = bag.addPokemon(makeFire(1));
        assert(res == true); // Should be able to add up to capacity
    }
    // Try to add a 7th Pokémon, should fail
    bool res = bag.addPokemon(makeGrass(1));
    assert(res == false); // Cannot add more than bag capacity

    // 2. Test: Switch active Pokemon, can switch even if fainted (handled in battle logic)
    bag.getPokemonAt(1)->resetHP(0); // Set the 2nd Pokémon's HP to 0 (fainted)
    bool switched = bag.switchActive(1); // Try to switch to a fainted Pokémon
    assert(switched == true); // Bag allows switch, battle logic restricts usage

    // 3. Test: Add, use potion and Pokéball
    bag.setPotionsAmount(2);
    assert(bag.getPotionAmount() == 2);
    bag.usePotion();
    assert(bag.getPotionAmount() == 1);

    bag.setBallAmount(2);
    assert(bag.getBallAmount() == 2);
    // Not testing useBalls directly here, since a wild Pokémon target is needed (tested in battle logic)

    // 4. Test: Increasing and decreasing potions and Pokéballs
    bag.addPotion(3);
    assert(bag.getPotionAmount() == 4);

    bag.addBalls(3);
    assert(bag.getBallAmount() == 5);

    // 5. Test: Heal all Pokémon in the bag
    bag.getPokemonAt(0)->resetHP(20); // Set HP to a non-max value
    bag.healAllPokemon();
    assert(bag.getPokemonAt(0)->getCurrentHP() == bag.getPokemonAt(0)->getMaxHP());

    // 6. Test: Level up and evolve
    bag.getPokemonAt(0)->addExp(200); // Enough experience to level up twice
    assert(bag.getPokemonAt(0)->canLevelUp());
    bag.getPokemonAt(0)->levelUp();
    assert(bag.getPokemonAt(0)->getLevel() >= 3);

    // Test evolution
    bag.getPokemonAt(0)->addExp(1000); // Gain enough EXP for evolution
    bag.getPokemonAt(0)->levelUp();
    bool evolved = bag.evolve(0);
    assert(evolved == true);

    // 7. Test: Release all Pokémon (Bag destructor will be called)
    // When main ends, bag destructor should release all Pokémon to prevent memory leaks

    endwin(); // End ncurses mode

    std::cout << "Bag & Player feature test passed!" << std::endl;
    return 0;
}