#ifndef POKEMONBALL_H
#define POKEMONBALL_H

#include "FirePokemon.h"
#include "WaterPokemon.h"
#include "GrassPokemon.h"

// The PokemonBall class represents a Poké Ball item that can be used to catch Pokémon.
class PokemonBall {
private:
    double baseRate; // The base probability (0~1) of successfully capturing a Pokémon
    int price;       // The purchase price of the Poké Ball

public:
    // Default constructor. Initializes the Poké Ball with its base rate and price.
    PokemonBall();

    // Attempts to catch a Pokémon. Returns true if successful.
    // 'target' is the Pokémon you want to catch.
    bool use(PokemonEntity* target);

    // Returns the price of the Poké Ball.
    int getPrice();
};

#endif