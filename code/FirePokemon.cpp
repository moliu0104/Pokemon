#include "FirePokemon.h"

// Default constructor: initializes all attributes to default values.
FirePokemon::FirePokemon() {
    name = "";
    type = "";
    level = 0;
    stage = 0;
    maxHP = 0;
    currentHP = maxHP;
    experience = 0;
    moveSet = {};
}

// Constructor: create FirePokemon without experience (e.g., wild Pokemon)
FirePokemon::FirePokemon(std::string name, std::string type, int level, int stage, int maxHP, std::vector<Move> moveSet)
    : PokemonEntity(name, type, level, stage, maxHP, 0, moveSet) {}

// Constructor: create FirePokemon with experience (e.g., from save file)
FirePokemon::FirePokemon(std::string name, std::string type, int level, int stage, int maxHP, int experience, std::vector<Move> moveSet)
    : PokemonEntity(name, type, level, stage, maxHP, experience, moveSet) {}

// Attack logic: deals damage to target with type effectiveness
void FirePokemon::attack(PokemonEntity* target, Move move) {
    int damage = move.getDamage();
    // Fire is strong against Grass
    if (move.getType() == "Fire" && target->getType() == "Grass") {
        target->takeDamage(damage * 1.2);
    }
    // Fire is weak against Water
    else if (move.getType() == "Fire" && target->getType() == "Water") {
        target->takeDamage(damage * 0.8);
    }
    // No effectiveness multiplier
    else {
        target->takeDamage(damage);
    }
}

// Handle taking damage and clamp HP to valid range
void FirePokemon::takeDamage(int damage) {
    currentHP -= damage;
    clampHP();
}

// Clone this FirePokemon (deep copy)
FirePokemon* FirePokemon::clone() {
    return new FirePokemon(*this);
}

// Destructor
FirePokemon::~FirePokemon() {}