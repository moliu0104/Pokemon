#ifndef FIREPOKEMON_H
#define FIREPOKEMON_H

#include "PokemonEntity.h"

// FirePokemon class inherits from PokemonEntity.
// Represents a Fire-type Pokémon with additional behavior for attacks and evolution.
class FirePokemon : public PokemonEntity {
public:
    // Default constructor
    FirePokemon();

    // Constructor for creating a FirePokemon (no experience, e.g. for wild Pokémon or newly caught)
    FirePokemon(std::string name, std::string type, int level, int stage, int maxHP, std::vector<Move> moveSet);

    // Constructor for creating a FirePokemon with experience (e.g. when loading from a save file)
    FirePokemon(std::string name, std::string type, int level, int stage, int maxHP, int experience, std::vector<Move> moveSet);

    // Override the attack function for Fire-type logic
    void attack(PokemonEntity* target, Move move) override;

    // Override the takeDamage function (damage calculations or side effects if needed)
    void takeDamage(int damage) override;

    // Override the clone function: returns a deep copy of this FirePokemon
    FirePokemon* clone() override;

    // Destructor
    ~FirePokemon();
};

#endif