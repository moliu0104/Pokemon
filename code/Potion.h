// Potion.h
#ifndef POTION_H
#define POTION_H

// Include the three Pokemon type headers so Potion can interact with all types
#include "FirePokemon.h"
#include "WaterPokemon.h"
#include "GrassPokemon.h"

// Potion class definition
class Potion {
    int healAmount; // The amount of HP this potion restores
    int price;      // The price of the potion

public:
    // Constructor: initializes the healing amount (default is 100)
    Potion(int heal = 100);

    // Use this potion on a PokemonEntity. Returns true if used successfully
    bool use(PokemonEntity* pokemon);

    // Get the price of this potion
    int getPrice();

    // Destructor
    ~Potion();
};

#endif // POTION_H