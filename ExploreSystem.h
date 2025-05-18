#ifndef EXPLORESYSTEM
#define EXPLORESYSTEM

#include<chrono>
#include<thread>
#include<cstdlib>
#include<ctime>
#include<string>
#include<ncurses.h>
#include"Game.h"
#include"Menu.h"
#include"RandomUtil.h"
#include"PokemonDataBase.h"
#include"PokemonEntity.h"
#include"FirePokemon.h"
#include"GrassPokemon.h"
#include"WaterPokemon.h"

    class ExploreSystem{
    private:
        PokemonEntity* wildPokemon;
        int drawExploreMenu();
    public: 
        ExploreSystem();
        int run(int choice);
        void encounterWildPokemon(string type);
        PokemonEntity* getWildPokemon();
        ~ExploreSystem();
    };

#endif