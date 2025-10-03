#ifndef GAME_H
#define GAME_H

#include<ncurses.h>        // For terminal graphics
#include<iostream>         // For input/output streams
#include<vector>           // For vector container
#include<fstream>          // For file operations
#include<sstream>          // For string stream operations
#include"Menu.h"           // For menu display
#include"PokemonDataBase.h"// For Pokémon database management
#include"PokemonEntity.h"  // For Pokémon entity class
#include"ExploreSystem.h"  // For exploring/adventure system
#include"BattleSystem.h"   // For battle system
#include"Bag.h"            // For player's bag management
#include"Player.h"         // For player data

using namespace std;

// Main Game class to manage initialization, saving, and loading
class Game{
public:
    // Initialize the game with starter items and Pokémon
    static void initGame();

    // Save the current game state to a file
    static void saveGame(const string& filename);

    // Load game state from a file
    static bool loadGame(const string& filename);
};

#endif // GAME_H