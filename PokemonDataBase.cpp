#include "PokemonDataBase.h"

PokemonDataBase::PokemonDataBase(){
    addPokemon(Pokemon(
        "Bulbasur",
        "Grass",
        1,
        100,
        {
            Move("Tackle", "Physical", 10),
            Move("Vine Whip", "Grass", 20)
        }
    ));
    
    addPokemon(Pokemon(
        "Charmander",
        "Fire",
        1,
        100,
        {
            Move("Scratch","Physical",10),
            Move("Ember","Fire",20)
        }
    ));

   addPokemon(Pokemon(
        "Squirtle",
        "Water",
        1,
        100,
        {
            Move("Tackle","Physical",10),
            Move("Water Gun","Water",20)

        }
    ));
    
}

void PokemonDataBase::addPokemon(const Pokemon& p){
    allPokemon.push_back(p);

}

const Pokemon* PokemonDataBase::findPokemonByName(string name){
    for(int i = 0; i < allPokemon.size(); i++){
        if(allPokemon[i].getName() == name){
            return &allPokemon[i];
        }
    }

    return nullptr;
}

const vector<Pokemon> PokemonDataBase::findPokemonByType(string type){
    vector<Pokemon> result;
    for(int i = 0; i < allPokemon.size(); i ++){
        if(allPokemon[i].getType() == type){
            result.push_back(allPokemon[i]);
        }
    }

    return result;
}

const vector<Pokemon>& PokemonDataBase::getAllPokemon(){
    return allPokemon;
}

bool PokemonDataBase::isEmpty() const{
    return allPokemon.size() == 0;
}

const Pokemon PokemonDataBase::getRandomPokemon(){
    srand(time(0));
    int index = rand() % allPokemon.size();

    return allPokemon[index];
}


PokemonDataBase::~PokemonDataBase(){}
