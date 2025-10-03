#ifndef BAG_H
#define BAG_H

#include<iostream>
#include<ncurses.h>
#include<vector>
#include"Move.h"
#include"Menu.h"
#include"FirePokemon.h"
#include"GrassPokemon.h"
#include"WaterPokemon.h"
#include"Potion.h"
#include"PokemonBall.h"

using namespace std;

// The Bag class manages the player's collection of Pokémon and items.
class Bag {
private:
    int bagSizePokemon;       // Maximum number of Pokémon the bag can hold
    int countPokemon;         // Current number of Pokémon in the bag
    int countItems;           // Number of items (not currently used, but could be for extension)
    int activeIndex;          // Index of the currently active (battling) Pokémon
    PokemonEntity** pokemons; // Array of pointers to Pokémon owned by the player

    int potionsAmount;        // Number of potions the player owns
    int ballsAmount;          // Number of Pokéballs the player owns

    Potion potions;           // Potion item instance (for applying healing)
    PokemonBall balls;        // Pokéball item instance (for capturing Pokémon)

public:
    // Constructor: Initializes the bag and its contents
    Bag();

    // Add a new Pokémon to the bag (returns false if the bag is full)
    bool addPokemon(PokemonEntity* p);

    // Switch the active (battling) Pokémon by index
    bool switchActive(int index);

    // Clear bag
    void clear();

    // Get a pointer to the currently active Pokémon
    PokemonEntity* getActive();

    // Get a pointer to the Pokémon at position i in the bag
    PokemonEntity* getPokemonAt(int i);

    // Get the index of the currently active Pokémon
    int getAcitiveIndex();

    // Get the number of Pokémon currently in the bag
    int getPokemonAmount();

    // Get the maximum capacity of the Pokémon bag
    int getPokemonCapacity();

    // Fully heal all Pokémon in the bag
    void healAllPokemon();

    // Evolve the Pokémon at index i (if possible)
    bool evolve(int i);

    // Add potions to the bag (increase quantity)
    void addPotion(int amount);

    // Use a potion on the active Pokémon (returns true if successful)
    bool usePotion();

    // Get the number of potions in the bag
    int getPotionAmount();

    // Set the potion quantity directly (used for save/load)
    void setPotionsAmount(int amount);

    // Add Pokéballs to the bag
    void addBalls(int amount);

    // Use a Pokéball to try to capture a target Pokémon (returns true if captured)
    bool useBalls(PokemonEntity* target);

    // Get the number of Pokéballs in the bag
    int getBallAmount();

    // Set the Pokéball quantity directly (used for save/load)
    void setBallAmount(int amount);

    // Destructor: Frees memory and cleans up the bag contents
    ~Bag();
};

#endif