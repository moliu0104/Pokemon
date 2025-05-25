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

WaterPokemon::WaterPokemon(std::string name,std::string type,int level,int stage,int maxHP,std::vector<Move> moveSet):PokemonEntity(name,type,level,stage,maxHP,0,moveSet){}

WaterPokemon::WaterPokemon(string name, string type, int level,int stage, int maxHP, int experience,vector<Move> moveSet):PokemonEntity(name,type,level,stage,maxHP,experience,moveSet){}

PokemonEntity* WaterPokemon::evolve(){
    vector<Pokemon> db = allPokemon.findPokemonByType("Water");
    int index;

    for(int i =0; i < db.size(); i++){
        if(name == db.at(i).getName()){
            index = i;
            break;
        }
    }

    return new WaterPokemon(db[index+1].getName(),db[index+1].getType(),db[index+1].getStage()*10,db[index+1].getStage(),0,db[index+1].getMoveSet());
}

void WaterPokemon::attack(PokemonEntity* target,Move move){
    int damage = move.getDamage();
    if(move.getType() == "Water" && target->getType() == "Fire"){
        target->takeDamage(move.getDamage()*1.2);
    }else if(move.getType() == "Water" && target->getType() == "Grass"){
        target->takeDamage(move.getDamage()*0.8);
    }else{
        target->takeDamage(move.getDamage());
    }
}

void WaterPokemon::takeDamage(int damage){
    currentHP -= damage;
    clampHP();
}

WaterPokemon* WaterPokemon::clone(){
    return new WaterPokemon(*this);
}

WaterPokemon::~WaterPokemon(){}