#include "Potion.h"

// Constructor: initializes the healing amount and sets a default price
Potion::Potion(int heal) {
    healAmount = heal; // Set the amount this potion heals
    price = 50;        // Default price for a potion
}

// Use the potion on the given PokemonEntity
// Calls the heal method on the Pokemon and returns true (indicates success)
bool Potion::use(PokemonEntity* pokemon) {
    pokemon->heal(healAmount); // Restore health to the Pokemon
    return true;               // Assume usage is always successful
}

// Returns the price of the potion
int Potion::getPrice() {
    return price;
}

// Destructor: no special cleanup needed
Potion::~Potion() {}