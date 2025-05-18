#ifndef PLAYER_H
#define PLAYER_h

#include <vector>
#include "PokemonEntity.h"

using namespace std;

class Player{
private:
    int money;
    vector<PokemonEntity> bag;
    vector<PokemonEntity> InventoryPokemon;
}

#endif