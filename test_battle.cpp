#include <iostream>
#include <cassert>
#include <vector>
#include "FirePokemon.h"
#include "WaterPokemon.h"
#include "GrassPokemon.h"
#include "PokemonEntity.h"
#include "Player.h"
#include "Bag.h"
#include "Move.h"
#include "BattleSystem.h"

// Create some test Moves
Move testFireMove("Flame", "Fire", 50);
Move testWaterMove("Aqua", "Water", 50);
Move testGrassMove("Leaf", "Grass", 50);

// Factory helpers
FirePokemon* makeFire(int lv = 10) {
    std::vector<Move> moves = {testFireMove};
    return new FirePokemon("Charmander", "Fire", lv, 1, 120, 0, moves);
}
WaterPokemon* makeWater(int lv = 10) {
    std::vector<Move> moves = {testWaterMove};
    return new WaterPokemon("Squirtle", "Water", lv, 1, 120, 0, moves);
}
GrassPokemon* makeGrass(int lv = 10) {
    std::vector<Move> moves = {testGrassMove};
    return new GrassPokemon("Bulbasaur", "Grass", lv, 1, 120, 0, moves);
}

int main() {
    initscr();            // Initialize ncurses screen
    cbreak();             // Disable line buffering
    noecho();             // Don't display typed characters
    curs_set(0);          // Hide cursor
    keypad(stdscr, TRUE); // Enable arrow keys

    // Prepare the player's bag with two Pokémon
    player.getBag().addPokemon(makeFire(10));
    player.getBag().addPokemon(makeGrass(10));
    player.getBag().addBalls(5);
    player.getBag().addPotion(5);

    // 1. Test player and wild Pokémon attack each other
    FirePokemon* fire = makeFire(10);
    WaterPokemon* wild = makeWater(10);

    int fire_hp_before = fire->getCurrentHP();
    wild->attack(fire, testWaterMove);
    assert(fire->getCurrentHP() < fire_hp_before); // Should take damage

    // 2. Type effectiveness: Water > Fire, damage increased
    fire->resetHP(fire->getMaxHP());
    int expected_damage = int(testWaterMove.getDamage() * 1.2);
    wild->attack(fire, testWaterMove);
    int real_damage = fire->getMaxHP() - fire->getCurrentHP();
    assert(abs(real_damage - expected_damage) <= 1); // Allow float->int rounding error

    // 3. Auto switch to alive pokemon; defeat if all faint
    player.getBag().getPokemonAt(0)->resetHP(0); // First Pokémon fainted
    player.getBag().getPokemonAt(1)->resetHP(50); // Second is alive
    assert(player.getBag().getActive()->isFainted());
    player.getBag().switchActive(1); // Switch to alive
    assert(!player.getBag().getActive()->isFainted());

    // Now faint all pokemons, simulate defeat scenario
    player.getBag().getPokemonAt(1)->resetHP(0);
    assert(player.getBag().getPokemonAt(0)->isFainted());
    assert(player.getBag().getPokemonAt(1)->isFainted());

    // 4. Wild pokemon fainted triggers playerWin, rewards exp & gold
    player.getBag().getPokemonAt(0)->resetHP(100);
    player.getBag().switchActive(0);
    int money_before = player.getMoneyAmount();
    int exp_before = player.getActivePokemon()->getExp();
    WaterPokemon* wild2 = makeWater(8);
    wild2->resetHP(0); // Simulate wild fainted
    BattleSystem battle(wild2);
    battle.playerWin();
    assert(player.getMoneyAmount() > money_before); // Money increased
    assert(player.getActivePokemon()->getExp() > exp_before); // Exp increased

    // 5. Item use logic: potion restores HP, pokeball usage reduces balls
    int hp_now = player.getActivePokemon()->getCurrentHP();
    player.getActivePokemon()->resetHP(hp_now - 30); // Hurt it
    int potion_amount = player.getBag().getPotionAmount();
    battle.usePotion();
    assert(player.getBag().getPotionAmount() == potion_amount - 1);
    assert(player.getActivePokemon()->getCurrentHP() > hp_now - 30);

    int balls_before = player.getBag().getBallAmount();
    battle.useBall(); // Will try to catch wild2 (fainted, so always succeed/fail)
    assert(player.getBag().getBallAmount() == balls_before - 1);

    endwin();

    std::cout << "All BattleSystem logic tests passed!" << std::endl;
    return 0;
}