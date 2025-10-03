#include "GrassPokemon.h"

// Default constructor for GrassPokemon
// Initializes all member variables to default (empty or zero) values
GrassPokemon::GrassPokemon() {
    name = "";           // Name of the Pokémon (empty string)
    type = "";           // Type of the Pokémon (empty string)
    level = 0;           // Level of the Pokémon
    stage = 0;           // Evolution stage
    maxHP = 0;           // Maximum health points
    currentHP = maxHP;   // Current health points, set to maxHP
    experience = 0;      // Experience points
    moveSet = {};        // List of moves (empty vector)
}

// Constructor to create a GrassPokemon with specific parameters, with experience defaulted to 0
GrassPokemon::GrassPokemon(std::string name, std::string type, int level, int stage, int maxHP, std::vector<Move> moveSet)
    : PokemonEntity(name, type, level, stage, maxHP, 0, moveSet) {}

// Constructor to create a GrassPokemon with specific parameters, including experience
GrassPokemon::GrassPokemon(std::string name, std::string type, int level, int stage, int maxHP, int experience, std::vector<Move> moveSet)
    : PokemonEntity(name, type, level, stage, maxHP, experience, moveSet) {}

// Implements the attack logic for GrassPokemon
// Applies type effectiveness: Grass is strong against Water, weak against Fire
void GrassPokemon::attack(PokemonEntity* target, Move move) {
    int damage = move.getDamage();
    // Super effective: Grass vs. Water (1.2x damage)
    if (move.getType() == "Grass" && target->getType() == "Water") {
        target->takeDamage(damage * 1.2);
    }
    // Not very effective: Grass vs. Fire (0.8x damage)
    else if (move.getType() == "Grass" && target->getType() == "Fire") {
        target->takeDamage(damage * 0.8);
    }
    // Normal effectiveness for other types
    else {
        target->takeDamage(damage);
    }
}

// Handles receiving damage for GrassPokemon
// Subtracts damage from currentHP and clamps HP to [0, maxHP]
void GrassPokemon::takeDamage(int damage) {
    currentHP -= damage;  // Decrease HP by damage amount
    clampHP();            // Ensure HP is not less than 0 or more than maxHP
}

// Returns a new copy (clone) of this GrassPokemon object
GrassPokemon* GrassPokemon::clone() {
    return new GrassPokemon(*this); // Copy constructor is used
}

// Destructor - nothing special to clean up, but included for completeness
GrassPokemon::~GrassPokemon() {}