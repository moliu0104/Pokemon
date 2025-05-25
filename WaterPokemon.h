#ifndef WATERPOKEMON_H
#define WATERPOKEMON_H

#include "PokemonEntity.h"

// The WaterPokemon class represents a Pokemon of type "Water".
// Inherits all attributes and functions from PokemonEntity.
class WaterPokemon : public PokemonEntity {
public:
    // Default constructor
    WaterPokemon();

    // Constructor to create a WaterPokemon with no experience (fresh catch)
    WaterPokemon(std::string name,
                 std::string type,
                 int level,
                 int stage,
                 int maxHP,
                 std::vector<Move> moveSet);

    // Constructor to create a WaterPokemon with a given experience value (for save/load)
    WaterPokemon(std::string name,
                 std::string type,
                 int level,
                 int stage,
                 int maxHP,
                 int experience,
                 std::vector<Move> moveSet);

    // Attack another Pokemon using a selected move (must implement actual logic in cpp)
    void attack(PokemonEntity* target, Move move) override;

    // Take damage (decreases HP, with possible side effects)
    void takeDamage(int damage) override;

    // Clone this WaterPokemon (deep copy)
    WaterPokemon* clone() override;

    // Destructor
    ~WaterPokemon();
};

#endif