#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include<string>
#include<chrono>
#include<thread>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<iostream>
#include<ncurses.h>
#include"Pokemon.h"
#include"PokemonDataBase.h"
#include"Menu.h"
#include"Move.h"
#include"Bag.h"
#include"Player.h"

using namespace std;


    class BattleSystem{
    private:
        PokemonEntity* wildPokemon;
        PokemonEntity* playerPokemon;
        vector<string> options;
        int highlight;
        int height;
        int width;
        bool haveballs;
        bool havePotions;

        enum BattleOptions{
            Fight,
            Items,
            Switch,
            Run
        };

        bool fight();
        void wildPokemonTure();
        bool usePotion();
        bool useBall();
        bool switchPokemon();
        bool switchAlivePokemon();
        void runAway();
        void playerWin();

        void drawStatus(int y, int x, PokemonEntity* pokmeon,bool isPlayer);
        void drawLog(int y, int x, string log); 
        int drawItemsMenu(int y, int x);
        int drawMainMenu(int y, int x);
        int drawMoveMenu(int y, int x,vector<Move> moves);
        void drawVictoryScreen(int exp, int gold);
        void drawDefeatScreen();
        void drawCaptureScreen();

    public:
        BattleSystem (PokemonEntity* wildPokemon);

        void run();
    
        ~BattleSystem();
    };


#endif