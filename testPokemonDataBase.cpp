#include<iostream>
#include"PokemonDataBase.h"

int main(){
    
    PokemonDataBase pokemonDataBase;
    vector<Pokemon> allPokemon = pokemonDataBase.getAllPokemon();


    for(int i = 0; i < allPokemon.size() ; i++){
        cout << "name: " << allPokemon[i].getName() << " | " ;
        cout << "type: " << allPokemon[i].getType() << " | " ;
        cout << "stage: "<< allPokemon[i].getStage() << " | ";
        cout << "maxHP: " << allPokemon[i].getMaxHP() << " | ";
        cout << endl;
        cout << "Move: " << endl;

        vector<Move> moveSet = allPokemon[i].getMoveSet();
        for(int j = 0; j < moveSet.size(); j++){
            cout << moveSet[j].getName() << " | ";
            cout << moveSet[j].getType() << " | ";
            cout << moveSet[j].getDamage() << endl;
        }

        cout << "--------------------------------------------------------------------" << endl;
    }
    return 0;
}
