#include "PokemonDataBase.h"

// Constructor: Reads Pokemon data from "PokemonDataBase.txt" and fills the database
PokemonDataBase::PokemonDataBase(){
    ifstream file("PokemonDataBase.txt");

    // Check if file opened successfully
    if (!file.is_open()) {
        cerr << "Error: could not open PokemonDataBase.txt\n";
    }
    
    string line;
    // Read each line from the file
    while (std::getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines

        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> parts;

        // Split the line by comma
        while (std::getline(ss, field, ',')) {
            parts.push_back(field);
        }

        // Parse basic Pokemon attributes
        std::string name   = parts[0];
        std::string type   = parts[1];
        int stage          = std::stoi(parts[2]);
        int maxHP          = std::stoi(parts[3]);

        // Parse moves (every 3 fields: name, type, damage)
        vector<Move> moves;
        for (int i = 4; i + 2 < parts.size(); i += 3) {
            std::string mName = parts[i];
            std::string mType = parts[i+1];
            int mDmg          = std::stoi(parts[i+2]);

            Move move(mName, mType, mDmg);
            moves.push_back(move);
        }

        // Create Pokemon object and add to the database
        Pokemon pokemon(name, type, stage, maxHP, moves);
        pokemonDB.push_back(pokemon);
    }
}

// Add a Pokemon to the database
void PokemonDataBase::addPokemon(const Pokemon& p){
    pokemonDB.push_back(p);
}

// Find a Pokemon by name; return pointer or nullptr if not found
Pokemon* PokemonDataBase::findPokemonByName(string name){
    for(int i = 0; i < pokemonDB.size(); i++){
        if(pokemonDB[i].getName() == name){
            return &pokemonDB[i];
        }
    }
    return nullptr;
}

// Find all Pokemon of a specific type
vector<Pokemon> PokemonDataBase::findPokemonByType(string type){
    vector<Pokemon> result;
    for(int i = 0; i < pokemonDB.size(); i++){
        if(pokemonDB[i].getType() == type){
            result.push_back(pokemonDB[i]);
        }
    }
    return result;
}

// Get the entire list of Pokemon
vector<Pokemon> PokemonDataBase::getAllPokemon(){
    return pokemonDB;
}

// Check if the database is empty
bool PokemonDataBase::isEmpty() const{
    return pokemonDB.size() == 0;
}

// Get a random chain (evolution line) of 3 Pokemon by type
vector<Pokemon> PokemonDataBase::getRandomPokemonByType(string type){
    vector<Pokemon> pokemonByType = findPokemonByType(type);
    int index = util::randInRange(1, pokemonByType.size() / 3); // Random evolution line index

    vector<Pokemon> pokemonChain;
    for(int i = 0; i < 3; i++){
        // Each evolution chain occupies 3 consecutive positions
        pokemonChain.push_back(pokemonByType[((index-1)*3)+i]);
    }
    return pokemonChain;
}

// Global instance (definition)
PokemonDataBase allPokemon;

// Destructor (empty, nothing to release since vector handles its own memory)
PokemonDataBase::~PokemonDataBase(){}