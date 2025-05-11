#ifndef GAME_H
#define GAME_H

#include<ncurses.h>
#include<iostream>
#include<vector>
#include"Menu.h"
#include"PokemonDataBase.h"
#include"ExploreSystem.h"

using namespace std;

class Game{
private:

    PokemonDataBase allPokemon;

    int highlight;

    vector<string> mainMenuOptions;
    vector<string> mainMenuTitle;

    vector<string> adventureOptions;
    vector<string> adventureTitle;

public:
    Game();
    //Methods
    void run();
    int showMainMenu();
    int showAdventure();
    int exploreMap(int choice);

    vector<string> getAdventureOptions();

    ~Game();
};

#endif