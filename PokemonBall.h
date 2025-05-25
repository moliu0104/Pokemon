#ifndef POKEMONBALL_H
#define POKEMONBALL_H

#include"FirePokemon.h"
#include"WaterPokemon.h"
#include"GrassPokemon.h"


class PokemonBall{
private:
    double baseRate;
    int price;
public:
    PokemonBall();
    bool use(PokemonEntity* target);
    int getPrice();
};

#endif