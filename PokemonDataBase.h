#ifndef POKEMONDATABASE_H
#define POKEMONDATABASE_H

#include<cstdlib>
#include<ctime>
#include"Pokemon.h"
#include"WildPokemon.h"

class PokemonDataBase{
private:
    vector<Pokemon> allPokemon;
public:
    PokemonDataBase();

    void addPokemon(const Pokemon& p);
    const Pokemon* findPokemonByName(string name) ;
    const vector<Pokemon> findPokemonByType(string type) ;


    const vector<Pokemon>& getAllPokemon();
    const Pokemon getRandomPokemon();

    bool isEmpty() const;

    ~PokemonDataBase();
};

#endif