#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "PokemonEntity.h"

using namespace std;

// Forward declaration for Bag class, since Bag is referenced as a pointer
class Bag;

// The Player class represents the game player, holding money and a bag of Pokémon/items.
class Player{
private:
    int moneyAmount; // The current amount of money the player has.
    Bag* bag;        // Pointer to the player's bag (stores Pokémon and items).
public:
    Player(); // Default constructor

    // Returns a reference to the player's bag.
    Bag& getBag();

    // Returns the current amount of money.
    int getMoneyAmount();

    // Returns a pointer to the player's active (currently selected) Pokémon.
    PokemonEntity* getActivePokemon();

    // Sets the player's money to a specific value.
    void setMoneyAmount(int amount);

    // Increases the player's money by a given amount.
    void addMoney(int amount);

    // Adds a Pokémon to the player's bag.
    void addPokemonToBag(PokemonEntity* pokemon);

    // Reduces the player's money by a given amount.
    void spendMoney(int amount);

    // Destructor to clean up resources (like deleting the bag).
    ~Player();
};

// Global player instance declaration (defined elsewhere, usually in Player.cpp)
extern Player player;

#endif