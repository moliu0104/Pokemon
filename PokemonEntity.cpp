#include"PokemonEntity.h"
#include<iostream>
#include<cstdlib>


PokemonEntity::PokemonEntity(string name, string type, int level,int stage, int maxHP, vector<Move> moveSet):Pokemon(name,type,stage,maxHP,moveSet), currentHP(maxHP),level(level){}


int PokemonEntity::getCurrentHP() const { return currentHP; }

int PokemonEntity::getLevel() const { return level; }

string PokemonEntity::getPersonality() const { return personality;}

PokemonEntity::~PokemonEntity(){}