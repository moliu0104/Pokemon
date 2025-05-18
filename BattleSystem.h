#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include<string>
#include<vector>
#include<iostream>
#include<ncurses.h>
#include"Pokemon.h"
#include"PokemonDataBase.h"
#include"Menu.h"
#include"Bag.h"

using namespace std;


    class BattleSystem{
    private:
        Bag bag;
        PokemonEntity* wildPokemon;
        PokemonEntity* player;
    public:
        BattleSystem(Bag bag, PokemonEntity* wildPokemon);

        int run();
        void drawStatus(int y, int x, PokemonEntity* pokmeon,bool isPlayer);
        void drawLog(int y, int x, vector<string>& logs); 
        int drawMainMenu(int y, int x, int selected);
        int drawMoveMenu(int y, int x,vector<Move> moves,int selected);

        ~BattleSystem();
    };


#endif