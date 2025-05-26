#include <iostream>            // For cout/cin
#include "PokemonDataBase.h"   // For PokemonDataBase, Pokemon, Move

int main() {
    // Create a PokemonDataBase object (loads data from file)
    PokemonDataBase pokemonDataBase;

    // Get all Pokemon in the database
    vector<Pokemon> allPokemon = pokemonDataBase.getAllPokemon();

    // Loop through each Pokemon and print their information
    for (int i = 0; i < allPokemon.size(); i++) {
        // Print basic info
        std::cout << "name: " << allPokemon[i].getName() << " | ";
        std::cout << "type: " << allPokemon[i].getType() << " | ";
        std::cout << "stage: " << allPokemon[i].getStage() << " | ";
        std::cout << "maxHP: " << allPokemon[i].getMaxHP() << " | ";
        std::cout << std::endl;

        // Print move set
        std::cout << "Move: " << std::endl;
        vector<Move> moveSet = allPokemon[i].getMoveSet();
        for (int j = 0; j < moveSet.size(); j++) {
            std::cout << moveSet[j].getName() << " | ";
            std::cout << moveSet[j].getType() << " | ";
            std::cout << moveSet[j].getDamage() << std::endl;
        }

        // Separator line for readability
        std::cout << "--------------------------------------------------------------------" << std::endl;
    }

    return 0;
}