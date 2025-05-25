#ifndef BAGSYSTEM_H
#define BAGSYSTEM_H

#include"Menu.h"

// Bag management system (handles bag UI and actions)
class BagSystem{
    // Menu options for the bag
    enum BagOptions{
        Pokemon,  // View Pokemon in bag
        Items,    // View items
        Exit      // Exit bag menu
    };
public:
    BagSystem();             // Constructor
    void run();              // Main loop to show bag menu
    int drawPokeInfo();      // Show Pokémon info
    void drawItemInfo();     // Show item info
    bool drawSwitchBag();    // Switch active Pokémon
};

#endif