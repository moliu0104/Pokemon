#include"Pokemon.h"

Pokemon::Pokemon(string name, string type, int stage, int maxHP, vector<Move> moveSet): name(name),type(type),stage(stage),maxHP(maxHP),moveSet(moveSet){}

string Pokemon::getName() const{ 
    return name;
}

string Pokemon::getType() const{
    return type;
}

int Pokemon::getStage() const{
    return stage;
}

int Pokemon::getMaxHP() const{
    return maxHP;
}

void Pokemon::setStage(int stage){
    this -> stage = stage;
}

void Pokemon::setType(string type){
    this -> type = type;
}

void Pokemon::setName(string name){
    this -> name = name;
}

void Pokemon::setMaxHP(int maxHP){
    this -> maxHP = maxHP;
}

Pokemon::~Pokemon(){}