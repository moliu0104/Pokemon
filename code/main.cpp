#include <ncurses.h>          // Terminal graphics library
#include <iostream>           // Standard I/O
#include <vector>             // Vector container
#include "Menu.h"             // Menu display
#include "PokemonDataBase.h"  // Pokemon database
#include "ExploreSystem.h"    // Adventure system
#include "BattleSystem.h"     // Battle system
#include "BagSystem.h"        // Bag system/menu
#include "StoreSystem.h"      // Store system
#include "Bag.h"              // Bag management
#include "Game.h"             // Game save/load/init

// Enum for main menu options
enum class MainOptions{
    Adventure,
    Bag,
    Store,
    SaveGame,
    Exit,
};

extern Player player;  // Externally declared player object

int main(){
    initscr();            // Initialize ncurses screen
    cbreak();             // Disable line buffering
    noecho();             // Don't display typed characters
    curs_set(0);          // Hide cursor
    keypad(stdscr, TRUE); // Enable arrow keys

    // Define the main menu title and options
    vector<string> mainMenuTitle = {"========= Pokémon ========"};
    vector<string> mainMenuOptions = {
        "Adventure",
        "Bag",
        "Store",
        "Save Game",
        "Exit"
    };

    // Try to load previous game; if not found, start new game
    if(!Game::loadGame("SaveGame.txt")){
        Game::initGame();
    }

    // Initialize system modules
    ExploreSystem exploreSystem;
    BagSystem bagSystem;
    StoreSystem store;

    bool running = true;   // Main loop flag
    int highlight = 0;     // Menu selection index

    // Main game loop
    while(running){
        // Show the main menu, get user's choice
        highlight = Menu::drawMenu(mainMenuOptions, mainMenuTitle);

        // Execute the selected menu option
        switch(MainOptions(highlight)){
            case MainOptions::Adventure:
                exploreSystem.run();    // Go adventure (battle wild Pokémon)
                break;

            case MainOptions::Bag:
                bagSystem.run();        // Open bag menu
                break;

            case MainOptions::Store:
                store.run();            // Open store menu
                break;

            case MainOptions::SaveGame:
                Game::saveGame("SaveGame.txt");   // Save current game state
                break;

            case MainOptions::Exit:
                running = false;        // Exit main loop, quit game
                break;
        }
    }

    endwin();   // Close ncurses window

    return 0;   // Exit program
}