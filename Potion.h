// Potion.h
#ifndef POTION_H
#define POTION_H

#include"FirePokemon.h"
#include"WaterPokemon.h"
#include"GrassPokemon.h"

class Potion{
    int healAmount;
    int price;
public:
    Potion(int heal = 100);
    bool use(PokemonEntity* pokemon);
    int getPrice();

    ~Potion();
};

#endif // POTION_H