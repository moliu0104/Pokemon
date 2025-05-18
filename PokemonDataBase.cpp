#include "PokemonDataBase.h"

PokemonDataBase::PokemonDataBase(){
    ifstream file("PokemonDataBase.txt");

    if (!file.is_open()) {
    cerr << "Error: could not open PokemonDataBase.txt\n";
    }
    
    string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> parts;

        while (std::getline(ss, field, ',')) {
            parts.push_back(field);
        }

        std::string name   = parts[0];
        std::string type   = parts[1];
        int stage          = std::stoi(parts[2]);
        int maxHP          = std::stoi(parts[3]);

        vector<Move> moves;

        for ( int i = 4; i + 2 < parts.size(); i += 3) {

            std::string mName = parts[i];
            std::string mType = parts[i+1];
            int mDmg          = std::stoi(parts[i+2]);

            Move move(mName,mType,mDmg);
            moves.push_back(move);
        }

        Pokemon pokemon(name,type,stage,maxHP,moves);

        pokemonDB.push_back(pokemon);
    }

}

void PokemonDataBase::addPokemon(const Pokemon& p){
    pokemonDB.push_back(p);

}

Pokemon* PokemonDataBase::findPokemonByName(string name){
    for(int i = 0; i < pokemonDB.size(); i++){
        if(pokemonDB[i].getName() == name){
            return &pokemonDB[i];
        }
    }

    return nullptr;
}

vector<Pokemon> PokemonDataBase::findPokemonByType(string type){
    vector<Pokemon> result;
    for(int i = 0; i < pokemonDB.size(); i ++){
        if(pokemonDB[i].getType() == type){
            result.push_back(pokemonDB[i]);
        }
    }

    return result;
}

vector<Pokemon> PokemonDataBase::getAllPokemon(){
    return pokemonDB;
}

bool PokemonDataBase::isEmpty() const{
    return pokemonDB.size() == 0;
}
vector<Pokemon> PokemonDataBase::getRandomPokemonByType(string type){
    vector<Pokemon> pokemonByType = findPokemonByType(type);
    int index = util::randInRange(1,pokemonByType.size()/3);

    vector<Pokemon> pokemonChain;

    for(int i = 0; i < 3; i++){
        pokemonChain.push_back(pokemonByType[((index-1)*3)+i]);
    }

    return pokemonChain;
}

PokemonDataBase allPokemon;

PokemonDataBase::~PokemonDataBase(){}
