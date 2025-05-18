#include"FirePokemon.h"

FirePokemon::FirePokemon(){
    name = "";
    type = "";
    level = 0;
    stage = 0;
    maxHP = 0;
    currentHP = maxHP;
    experience = 0;
    moveSet = {};
}

FirePokemon::FirePokemon(std::string name,std::string type,int level,int stage,int maxHP,std::vector<Move> moveSet):PokemonEntity(name,type,level,stage,maxHP,moveSet){}


void FirePokemon::attack(PokemonEntity* target){}

FirePokemon* FirePokemon::clone(){
    return new FirePokemon(*this);
}

FirePokemon::~FirePokemon(){}