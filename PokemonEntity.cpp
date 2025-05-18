#include"PokemonEntity.h"
#include<iostream>
#include<cstdlib>


PokemonEntity::PokemonEntity(string name, string type, int level,int stage, int maxHP, vector<Move> moveSet):Pokemon(name,type,stage,maxHP,moveSet), currentHP(maxHP),level(level),experience(0){}

PokemonEntity::PokemonEntity(string name, string type, int level,int stage, int maxHP, int experience, vector<Move> moveSet):Pokemon(name,type,stage,maxHP,moveSet), currentHP(maxHP),level(level),experience(experience){}

bool PokemonEntity::isFainted() {
    bool isFainted;
    if(currentHP > 0){
        isFainted = false;
    }{
        isFainted = true;
    }

    return isFainted;
}

int PokemonEntity::getCurrentHP() { return currentHP; }

int PokemonEntity::getLevel() { return level; }

PokemonEntity::~PokemonEntity(){}