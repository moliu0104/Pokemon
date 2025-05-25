#include"PokemonEntity.h"
#include<iostream>
#include<cstdlib>


PokemonEntity::PokemonEntity(string name, string type, int level,int stage, int maxHP, vector<Move> moveSet):Pokemon(name,type,stage,maxHP,moveSet), currentHP(maxHP),level(level),experience(0){}

PokemonEntity::PokemonEntity(string name, string type, int level,int stage, int maxHP, int experience, vector<Move> moveSet):Pokemon(name,type,stage,maxHP,moveSet), currentHP(maxHP),level(level),experience(experience){}

bool PokemonEntity::canEvolve(){
    if(stage == 1 && level >= 10){
        return true;
    }else if(stage == 2 && level >=20){
        return true;
    }else{
        return false;
    }
}

bool PokemonEntity::canLevelUp(){
    if(experience >= 100){
        return true;
    }else{
        return false;
    }
}

void PokemonEntity::levelUp(){
    int loop = experience % 100;
    for(int i = 0; i < loop; i++){
        level++;
        experience -= 100;
    }
}

bool PokemonEntity::isFainted() {
    bool isFainted;
    if(currentHP > 0){
        isFainted = false;
    }else{
        isFainted = true;
    }

    return isFainted;
}

void PokemonEntity::clampHP(){
    if (currentHP < 0) currentHP = 0;
    if (currentHP >= maxHP) currentHP = maxHP;
}

void PokemonEntity::heal(int amount){
    currentHP += amount;
    clampHP();
}

void PokemonEntity::addExp(int exp){
    experience += exp;
}

int PokemonEntity::getCurrentHP() { return currentHP; }

int PokemonEntity::getLevel() { return level; }

int PokemonEntity::getExp() { return experience; }

void PokemonEntity::resetHP(int HP) { currentHP = HP; }

PokemonEntity::~PokemonEntity(){}