#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "PokemonEntity.h"

using namespace std;

class Bag;

class Player{
private:
    int moneyAmount;
    Bag* bag;
public:
    Player();

    Bag& getBag();
    int getMoneyAmount();
    PokemonEntity* getActivePokemon();

    void setMoneyAmount(int amount);
    void addMoney(int amount);
    void addPokemonToBag(PokemonEntity* pokemon);
    void spendMoney(int amount);

    ~Player();
};

extern Player player;

#endif