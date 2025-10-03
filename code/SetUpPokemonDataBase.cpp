#include"PokemonDataBase.h"

//  Pokemon(string name, string type, int stage, int maxHP, vector<Move> moveSet);

void SetUpPokemonDataBase(PokemonDataBase& allPokemon){
    allPokemon.addPokemon(Pokemon(
        "Bulbasur",
        "Grass",
        1,
        100,
        {
            Move("Tackle", "Physical", 10),
            Move("Vine Whip", "Grass", 20)
        }
    ));
    
    allPokemon.addPokemon(Pokemon(
        "Charmander",
        "Fire",
        1,
        100,
        {
            Move("Scratch","Physical",10),
            Move("Ember","Fire",20)
        }
    ));

    allPokemon.addPokemon(Pokemon(
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