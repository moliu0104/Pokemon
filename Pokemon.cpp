#include"Pokemon.h"

Pokemon::Pokemon(string name, string type, int stage, int maxHP, vector<Move> moveSet): name(name),type(type),stage(stage),maxHP(maxHP),moveSet(moveSet){}

string Pokemon::getName(){ 
    return name;
}

string Pokemon::getType(){
    return type;
}

int Pokemon::getStage(){
    return stage;
}

int Pokemon::getMaxHP(){
    return maxHP;
}

 vector<Move> Pokemon::getMoveSet(){
    return moveSet;
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

void Pokemon::addMove(Move move){
    moveSet.push_back(move);
}

Pokemon::~Pokemon(){}