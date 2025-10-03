#ifndef POKEMONDATABASE_H
#define POKEMONDATABASE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>   
#include <sstream>  
#include <vector>
#include "Move.h"
#include "Pokemon.h"
#include "RandomUtil.h"

using namespace std;

// Class for handling the Pokemon database, including reading, searching, and generating Pokemon
class PokemonDataBase {
private:
    // Internal storage for all Pokemon loaded from file
    vector<Pokemon> pokemonDB;

public:
    // Constructor: Loads the Pokemon data from the file when the object is created
    PokemonDataBase();

    // Adds a new Pokemon to the database
    void addPokemon(const Pokemon& p);

    // Finds a Pokemon by its name, returns a pointer (nullptr if not found)
    Pokemon* findPokemonByName(string name);

    // Finds all Pokemon of a given type (e.g., "Fire", "Water")
    vector<Pokemon> findPokemonByType(string type);

    // Returns all Pokemon in the database
    vector<Pokemon> getAllPokemon();

    // Returns a chain (evolution line) of 3 random Pokemon of the given type
    vector<Pokemon> getRandomPokemonByType(string type);

    // Checks if the database is empty
    bool isEmpty() const;

    // Destructor
    ~PokemonDataBase();
};

// Declaration for a global Pokemon database instance
extern PokemonDataBase allPokemon;

#endif