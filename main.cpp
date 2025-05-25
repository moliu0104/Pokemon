#include<ncurses.h>
#include<iostream>
#include<vector>
#include"Menu.h"
#include"PokemonDataBase.h"
#include"ExploreSystem.h"
#include"BattleSystem.h"
#include"BagSystem.h"
#include"StoreSystem.h"
#include"Bag.h"
#include"Game.h"

enum class MainOptions{
    Adventure,
    Bag,
    Store,
    SaveGame,
    Exit,
};

extern Player player;

int main(){
    initscr();    
    cbreak();     
    noecho();     
    curs_set(0);
    keypad(stdscr, TRUE);  

    vector<string> mainMenuTitle = {"========= Pokémon ========"};
    vector<string> mainMenuOptions = {
        "Adventure",
        "Bag",
        "Store",
        "Save Game",
        "Exit"
    };

    
    if(!Game::loadGame("SaveGame.txt")){
        Game::initGame();
    }
    ExploreSystem exploreSystem;
    BagSystem bagSystem;
    StoreSystem store;

    bool running = true;
    int highlight = 0;

    while(running){
        highlight = Menu::drawMenu(mainMenuOptions,mainMenuTitle);

        switch(MainOptions(highlight)){
            case MainOptions::Adventure:
            exploreSystem.run();
            break;

            case MainOptions::Bag:
            bagSystem.run();
            break;

            case MainOptions::Store:
            store.run();
            break;

            case MainOptions::SaveGame:
            Game::saveGame("SaveGame.txt");
            break;

            case MainOptions::Exit:
            running = false;
        }
    }

    endwin();

    return 0;
}