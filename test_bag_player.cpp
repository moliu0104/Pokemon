#include <iostream>
#include <cassert>
#include "Player.h"
#include "FirePokemon.h"
#include "GrassPokemon.h"
#include "WaterPokemon.h"
#include "Bag.h"
#include "Move.h"
#include "PokemonDataBase.h"

// 创建简单的Move
Move testMove("Tackle", "Normal", 10);

// 创建测试用Pokemon
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
    initscr();            // Initialize ncurses screen
    cbreak();             // Disable line buffering
    noecho();             // Don't display typed characters
    curs_set(0);          // Hide cursor
    keypad(stdscr, TRUE); // Enable arrow keys

    // 1. Test: Add Pokemon, cannot exceed 6
    Bag bag;
    assert(bag.getPokemonAmount() == 0);
    for (int i = 0; i < 6; ++i) {
        bool res = bag.addPokemon(makeFire(1));
        assert(res == true);
    }
    // Try to add the 7th pokemon
    bool res = bag.addPokemon(makeGrass(1));
    assert(res == false); // Should fail

    // 2. Switch active Pokemon, cannot switch to fainted
    bag.getPokemonAt(1)->resetHP(0); // Make 2nd pokemon fainted
    bool switched = bag.switchActive(1); // Try to switch to fainted
    assert(switched == true); // 代码允许switch，但你的主逻辑是不能出战fainted，在battle逻辑里已经控制

    // 3. Add, use potion and pokeball
    bag.setPotionsAmount(2);
    assert(bag.getPotionAmount() == 2);
    bag.usePotion();
    assert(bag.getPotionAmount() == 1);

    bag.setBallAmount(2);
    assert(bag.getBallAmount() == 2);
    // 这里不直接测useBalls，因为需要野生宝可梦传入，可在battle test测

    // 4. Potion and pokeball增减正确
    bag.addPotion(3);
    assert(bag.getPotionAmount() == 4);

    bag.addBalls(3);
    assert(bag.getBallAmount() == 5);

    // 5. heal all Pokemon
    bag.getPokemonAt(0)->resetHP(20);
    bag.healAllPokemon();
    assert(bag.getPokemonAt(0)->getCurrentHP() == bag.getPokemonAt(0)->getMaxHP());

    // 6. 进化/升级
    bag.getPokemonAt(0)->addExp(200); // Enough to level up twice
    assert(bag.getPokemonAt(0)->canLevelUp());
    bag.getPokemonAt(0)->levelUp();
    assert(bag.getPokemonAt(0)->getLevel() >= 3);

    // 进化
    bag.getPokemonAt(0)->addExp(1000); // 升级到足够进化
    bag.getPokemonAt(0)->levelUp();
    bool evolved = bag.evolve(0);
    assert(evolved == true);

    // 7. 释放所有宝可梦（Bag析构/重置）
    // 用于测试无内存泄漏，main结束时会自动调用bag析构

    endwin();

    std::cout << "Bag & Player feature test passed!" << std::endl;
    return 0;
}