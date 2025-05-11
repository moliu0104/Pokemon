#ifndef BAG_H
#define BAG_H

#include<iostream>
#include<ncurses.h>
#include<vector>
#include"Move.h"

#include"FirePokemon.h"

using namespace std;

class Bag{
private:
    PokemonEntity** team;
public:
    Bag();
    void addPokemonToParty(OwnedPokemon* pokemon);
    vector<OwnedPokemon>* getTeam();
    void switchPokemon(int index1, int index2);
    void displayParty();
    ~Bag();
};

#endif