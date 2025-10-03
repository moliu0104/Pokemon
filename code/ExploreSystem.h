#ifndef EXPLORESYSTEM
#define EXPLORESYSTEM

#include<chrono>           // For sleep and time calculations
#include<thread>           // For std::this_thread::sleep_for
#include<cstdlib>          // For random numbers
#include<ctime>            // For random seed
#include<string>           // For string type
#include<ncurses.h>        // For UI display
#include"Game.h"           // For game context
#include"Menu.h"           // For drawing menus
#include"RandomUtil.h"     // For random utility functions
#include"PokemonDataBase.h"// For accessing Pokemon database
#include"PokemonEntity.h"  // For PokemonEntity base class
#include"FirePokemon.h"    // For FirePokemon class
#include"GrassPokemon.h"   // For GrassPokemon class
#include"WaterPokemon.h"   // For WaterPokemon class

class ExploreSystem{
private:
    // Enum for different map options
    enum MapOptions{
        GrassMap,   // Grass area
        WaterMap,   // Water area
        FireMap,    // Fire area
        Exit        // Exit exploration
    };
    PokemonEntity* wildPokemon;  // Pointer to the current wild Pokémon

    bool tryExploring();                // Handle encounter logic
    void encounterWildPokemon(string type); // Generate a wild Pokémon

public: 
    ExploreSystem();                    // Constructor

    void run();                         // Main loop for exploration
    PokemonEntity* getWildPokemon();    // Get current wild Pokémon

    ~ExploreSystem();                   // Destructor
};

#endif