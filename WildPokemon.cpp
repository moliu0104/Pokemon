#include "WildPokemon.h"
#include <iostream>

using namespace std;

WildPokemon::WildPokemon(string name, string type, int level,int stage, int maxHP, vector<Move> moveSet):PokemonEntity(name, type, level, stage, maxHP, moveSet){}
   
void WildPokemon::displayStatus() const{}
void WildPokemon::attack() const{}

WildPokemon::~WildPokemon(){}