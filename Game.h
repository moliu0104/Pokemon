#ifndef GAME_H
#define GAME_H

#include<ncurses.h>
#include<iostream>
#include<vector>
#include<chrono>
#include<thread>
#include<cstdlib>
#include<ctime>
#include"Menu.h"
#include"WildPokemon.h"
#include"PokemonDataBase.h"

using namespace std;

class Game{
private:

    PokemonDataBase allPokemon;

    int highlight;

    // Main Menu
    vector<string> mainMenuOptions;

    // Adventure Menu
    vector<string> adventureOptions;

    // Main Menu
    int showMainMenu();

    // Adventure Menu
    void showAdventure();

    void exploreMap(int choice);

public:
    Game();
    
    void run();

    ~Game();
};

#endif