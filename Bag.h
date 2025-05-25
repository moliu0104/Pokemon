#ifndef BAG_H
#define BAG_H

#include<iostream>
#include<ncurses.h>
#include<vector>
#include"Move.h"
#include"Menu.h"
#include"FirePokemon.h"
#include"GrassPokemon.h"
#include"WaterPokemon.h"
#include"Potion.h"
#include"PokemonBall.h"


using namespace std;

class Bag {
private:
    int bagSizePokemon;
    int countPokemon;
    int countItems;
    int activeIndex;
    PokemonEntity** pokemons;  // 活跃宝可梦
    int potionsAmount;
    int ballsAmount;
    Potion potions;
    PokemonBall balls;

public:
    Bag();
    bool addPokemon(PokemonEntity* p);
    bool switchActive(int index); 

    // 获取当前出战 Pokémon
    PokemonEntity* getActive();
    PokemonEntity* getPokemonAt(int i);
    int getAcitiveIndex();
    int getPokemonAmount();
    int getPokemonCapacity();

    void healAllPokemon();
    bool evolve(int i);

    void addPotion(int amount);
    bool usePotion();
    int getPotionAmount();
    void setPotionsAmount(int amount);

    void addBalls(int amount);
    bool useBalls(PokemonEntity* target);
    int getBallAmount();
    void setBallAmount(int amount);

    ~Bag();
};

#endif