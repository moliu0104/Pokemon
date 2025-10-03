#include "PokemonBall.h"
#include "Bag.h"      // Required for interacting with the Bag system (e.g. adding a Pokémon)
#include "Player.h"   // Needed to access the global player and their bag

// Constructor: initializes base catch rate and price of the Poké Ball
PokemonBall::PokemonBall() {
    baseRate = 0.8;   // The base chance of catching a Pokémon (e.g. 80%)
    price = 100;      // The price of a Poké Ball in the shop
}

// Use a Poké Ball to try to capture a Pokémon
// Returns true if the Pokémon was successfully caught, false otherwise
bool PokemonBall::use(PokemonEntity* target) {
    // Calculate the current HP ratio (how healthy the target is)
    double hpRatio = double(target->getCurrentHP()) / target->getMaxHP();
    if (hpRatio < 0) hpRatio = 0; // Clamp to zero if for some reason HP < 0

    // The lower the HP, the higher the catch chance
    double catchChance = baseRate * (1.0 - hpRatio);

    // Generate a random number in [0, 1)
    double roll = double(std::rand() % 1000) / 1000.0;

    // Determine if the catch is successful
    bool success = (roll < catchChance);

    if (success) {
        // If caught, add the Pokémon to the player's bag
        player.getBag().addPokemon(target);
    }

    return success;
}

// Get the price of a Poké Ball
int PokemonBall::getPrice() {
    return price;
}