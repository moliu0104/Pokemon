#include"Bag.h"

Bag::Bag(){
    team = new PokemonEntity*[2];
    team[1] = nullptr;
}

void Bag::addPokemonToParty(OwnedPokemon* pokemon){
    
}

void Bag::switchPokemon(int index1, int index2){
    
}
Bag::~Bag(){
    for(int i = 0; i < 2; i++){
        delete team[i];
    }
    
    delete[] team;
}
