#ifndef GRASSPOKEMON_H
#define GRASSPOKEMON_H

#include "PokemonEntity.h"

// GrassPokemon class inherits from PokemonEntity.
// This class represents a specific type of Pokemon (Grass-type) and implements
// required virtual methods for actions such as attack, taking damage, cloning, and evolving.
class GrassPokemon : public PokemonEntity {
public:
    // Default constructor
    GrassPokemon();

    // Constructor for creating a new GrassPokemon (no experience specified, e.g. wild Pokemon)
    GrassPokemon(std::string name,
                 std::string type,
                 int level,
                 int stage,
                 int maxHP,
                 std::vector<Move> moveSet);

    // Constructor for creating a new GrassPokemon with experience (e.g. loaded from save file)
    GrassPokemon(std::string name,
                 std::string type,
                 int level,
                 int stage,
                 int maxHP,
                 int experience,
                 std::vector<Move> moveSet);

    // Override attack logic for GrassPokemon
    void attack(PokemonEntity* target, Move move) override;

    // Override damage logic for GrassPokemon
    void takeDamage(int damage) override;

    // Creates a copy of this GrassPokemon object
    GrassPokemon* clone() override;

    // Destructor
    ~GrassPokemon();
};

#endif