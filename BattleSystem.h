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

// BattleSystem class handles a full Pokémon battle logic (UI and flow)
class BattleSystem{
private:
    PokemonEntity* wildPokemon;     // Wild Pokémon pointer
    PokemonEntity* playerPokemon;   // Player's active Pokémon pointer
    vector<string> options;         // Main menu options (Fight, Items, Switch, Run)
    int highlight;                  // Currently highlighted menu option
    int height;                     // Screen height for layout
    int width;                      // Screen width for layout
    bool haveballs;                 // Whether player has Pokémon Balls
    bool havePotions;               // Whether player has Potions

    // Battle menu choices
    enum BattleOptions{
        Fight,                      // Attack
        Items,                      // Use item
        Switch,                     // Switch Pokémon
        Run                         // Run away
    };

    // Core battle flow functions
    bool fight();                       // Player attacks wild Pokémon
    void wildPokemonTure();             // Wild Pokémon attacks player
    bool usePotion();                   // Use a Potion
    bool useBall();                     // Use a Pokémon Ball
    bool switchPokemon();               // Switch to another Pokémon (from menu)
    bool switchAlivePokemon();          // Switch when current Pokémon faints
    void runAway();                     // Escape from battle
    void playerWin();                   // Handle win rewards

    // UI/Display helper functions
    void drawStatus(int y, int x, PokemonEntity* pokmeon, bool isPlayer); // Draw Pokémon info & HP bar
    void drawLog(int y, int x, string log);                               // Draw a log/message line
    int drawItemsMenu(int y, int x);                                      // Draw items (Potions/Balls) menu
    int drawMainMenu(int y, int x);                                       // Draw main battle menu
    int drawMoveMenu(int y, int x, vector<Move> moves);                   // Draw move selection menu
    void drawVictoryScreen(int exp, int gold);                            // Draw win screen
    void drawDefeatScreen();                                              // Draw lose screen
    void drawCaptureScreen();                                             // Draw catch success screen

public:
    BattleSystem (PokemonEntity* wildPokemon); // Constructor: needs a wild Pokémon

    void run();            // Main entry to start the battle

    ~BattleSystem();       // Destructor
};

#endif