#ifndef GAME_H
#define GAME_H

#include<ncurses.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include"Menu.h"
#include"PokemonDataBase.h"
#include"PokemonEntity.h"
#include"ExploreSystem.h"
#include"BattleSystem.h"
#include"Bag.h"
#include"Player.h"

using namespace std;

class Game{
public:
static void initGame();
static void saveGame(const string& filename);
static bool loadGame(const string& filename);
};

#endif