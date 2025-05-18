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

class PokemonDataBase{
private:
    vector<Pokemon> pokemonDB;
public:
    PokemonDataBase();

    void addPokemon(const Pokemon& p);
    Pokemon* findPokemonByName(string name) ;
    vector<Pokemon> findPokemonByType(string type) ;


    vector<Pokemon> getAllPokemon();
    vector<Pokemon> getRandomPokemonByType(string type);

    bool isEmpty() const;

    ~PokemonDataBase();
};

extern PokemonDataBase allPokemon;

#endif