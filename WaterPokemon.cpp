#include "WaterPokemon.h"

// Default constructor: initializes all properties to default values.
WaterPokemon::WaterPokemon() {
    name = "";
    type = "";
    level = 0;
    stage = 0;
    maxHP = 0;
    currentHP = maxHP;
    experience = 0;
    moveSet = {};
}

// Constructor: creates a WaterPokemon with given info and experience = 0 (e.g., when caught)
WaterPokemon::WaterPokemon(std::string name, std::string type, int level, int stage, int maxHP, std::vector<Move> moveSet)
    : PokemonEntity(name, type, level, stage, maxHP, 0, moveSet) {}

// Constructor: creates a WaterPokemon with given info and experience (e.g., when loaded from save file)
WaterPokemon::WaterPokemon(string name, string type, int level, int stage, int maxHP, int experience, vector<Move> moveSet)
    : PokemonEntity(name, type, level, stage, maxHP, experience, moveSet) {}

// Attack target Pokemon with a given move, applying type advantages/disadvantages
void WaterPokemon::attack(PokemonEntity* target, Move move) {
    int damage = move.getDamage();
    // Water is strong against Fire, weak against Grass
    if (move.getType() == "Water" && target->getType() == "Fire") {
        target->takeDamage(damage * 1.2); // Deal extra damage
    } else if (move.getType() == "Water" && target->getType() == "Grass") {
        target->takeDamage(damage * 0.8); // Deal reduced damage
    } else {
        target->takeDamage(damage); // Normal damage
    }
}

// Reduce HP by damage amount; clamp to 0 if needed
void WaterPokemon::takeDamage(int damage) {
    currentHP -= damage;
    clampHP();
}

// Make a deep copy (clone) of this WaterPokemon
WaterPokemon* WaterPokemon::clone() {
    return new WaterPokemon(*this);
}

// Destructor: clean up if needed (empty since no dynamic memory inside class itself)
WaterPokemon::~WaterPokemon() {}