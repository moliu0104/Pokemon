#include <iostream>
#include <vector>
#include <cassert>
#include "Move.h"
#include "Pokemon.h"
#include "PokemonEntity.h"
#include "FirePokemon.h"
#include "WaterPokemon.h"
#include "GrassPokemon.h"
#include "Bag.h"
#include "Player.h"

using namespace std;

// Test the base Pokemon class for constructor, getters, and setters
void test_pokemon_base() {
    // Create a basic Pokemon with two moves
    vector<Move> moves = { Move("Tackle", "Normal", 10), Move("Growl", "Normal", 0) };
    Pokemon p("Bulbasaur", "Grass", 1, 39, moves);

    // Check basic properties
    assert(p.getName() == "Bulbasaur");
    assert(p.getType() == "Grass");
    assert(p.getStage() == 1);
    assert(p.getMaxHP() == 39);
    assert(p.getMoveSet().size() == 2);

    // Test setters
    p.setName("Ivysaur");
    assert(p.getName() == "Ivysaur");
    p.setStage(2);
    assert(p.getStage() == 2);

    cout << "Base Pokemon class test passed!" << endl;
}

// Test the abstract interface of PokemonEntity using a derived class (WaterPokemon)
void test_pokemon_entity_abstract() {
    // Create a WaterPokemon with one move
    vector<Move> moves = { Move("Water Gun", "Water", 20) };
    WaterPokemon wp("Squirtle", "Water", 5, 1, 44, moves);

    // Check properties
    assert(wp.getName() == "Squirtle");
    assert(wp.getType() == "Water");
    assert(wp.getLevel() == 5);
    assert(wp.getStage() == 1);
    assert(wp.getMaxHP() == 44);
    assert(wp.getMoveSet().size() == 1);

    // Test virtual methods for HP manipulation
    wp.takeDamage(10);
    assert(wp.getCurrentHP() == 34); // Should be 44 - 10

    wp.heal(5);
    assert(wp.getCurrentHP() == 39);

    // Test experience, leveling up
    wp.addExp(120);
    assert(wp.canLevelUp() == true);
    wp.levelUp();
    assert(wp.getLevel() == 6);

    cout << "PokemonEntity and WaterPokemon inheritance test passed!" << endl;
}

// Test dynamic polymorphism and cloning functionality
void test_polymorphism_and_clone() {
    // Create a FirePokemon dynamically
    vector<Move> moves = { Move("Ember", "Fire", 20) };
    FirePokemon* fp = new FirePokemon("Charmander", "Fire", 7, 1, 39, moves);

    // Clone as a base class pointer
    PokemonEntity* polymorph = fp->clone(); // Should create a deep copy
    assert(polymorph->getName() == "Charmander");
    assert(polymorph->getLevel() == 7);

    // Test virtual method for taking damage
    polymorph->takeDamage(15);
    assert(polymorph->getCurrentHP() == 24);

    // Clean up dynamic memory
    delete fp;
    delete polymorph;

    cout << "Polymorphism (virtual clone/takeDamage) test passed!" << endl;
}

// Test Player and Bag class for basic usage and composition
void test_player_and_bag() {
    // Player starts with 0 money
    Player testPlayer;
    assert(testPlayer.getMoneyAmount() == 0);

    // Add and check money
    testPlayer.addMoney(100);
    assert(testPlayer.getMoneyAmount() == 100);

    // Add a Pokemon to the player's bag
    vector<Move> moves = { Move("Vine Whip", "Grass", 20) };
    GrassPokemon* gp = new GrassPokemon("Bulbasaur", "Grass", 1, 1, 45, moves);
    testPlayer.addPokemonToBag(gp);
    assert(testPlayer.getBag().getPokemonAmount() == 1);

    // Test retrieving the active Pokemon
    PokemonEntity* active = testPlayer.getActivePokemon();
    assert(active->getName() == "Bulbasaur");

    // Clean up dynamic memory (Bag will own the pointer in your impl, but this is safe for most designs)
    delete gp;

    cout << "Player and Bag class test passed!" << endl;
}

// Entry point: run all tests for class structure and object behavior
int main() {
    cout << "\n==== Start class & object tests ====" << endl;

    test_pokemon_base();
    test_pokemon_entity_abstract();
    test_polymorphism_and_clone();
    test_player_and_bag();

    cout << "==== All class & object tests passed! ====\n" << endl;
    return 0;
}