#include"GrassPokemon.h"

GrassPokemon::GrassPokemon(){
    name = "";
    type = "";
    level = 0;
    stage = 0;
    maxHP = 0;
    currentHP = maxHP;
    experience = 0;
    moveSet = {};
}

GrassPokemon::GrassPokemon(std::string name,std::string type,int level,int stage,int maxHP,std::vector<Move> moveSet):PokemonEntity(name,type,level,stage,maxHP,moveSet){}


void GrassPokemon::attack(PokemonEntity* target){}

GrassPokemon* GrassPokemon::clone(){
    return new GrassPokemon(*this);
}

GrassPokemon::~GrassPokemon(){}