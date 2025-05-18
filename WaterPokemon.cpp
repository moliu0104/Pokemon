#include"WaterPokemon.h"

WaterPokemon::WaterPokemon(){
    name = "";
    type = "";
    level = 0;
    stage = 0;
    maxHP = 0;
    currentHP = maxHP;
    experience = 0;
    moveSet = {};
}

WaterPokemon::WaterPokemon(std::string name,std::string type,int level,int stage,int maxHP,std::vector<Move> moveSet):PokemonEntity(name,type,level,stage,maxHP,moveSet){}

WaterPokemon::WaterPokemon(string name, string type, int level,int stage, int maxHP, int experience,vector<Move> moveSet):PokemonEntity(name,type,level,stage,maxHP,experience,moveSet){}

void WaterPokemon::attack(PokemonEntity* target){}

WaterPokemon* WaterPokemon::clone(){
    return new WaterPokemon(*this);
}

WaterPokemon::~WaterPokemon(){}