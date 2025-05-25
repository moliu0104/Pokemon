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
        enum MapOptions{
            GrassMap,
            WaterMap,
            FireMap,
            Exit
        };
        PokemonEntity* wildPokemon;

        bool tryExploring();
        void encounterWildPokemon(string type);

    public: 
        ExploreSystem();

        void run();
        PokemonEntity* getWildPokemon();

        ~ExploreSystem();
    };

#endif