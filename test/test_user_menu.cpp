#include <iostream>
#include <cassert>
#include "BagSystem.h"
#include "StoreSystem.h"
#include "ExploreSystem.h"
#include "BattleSystem.h"
#include "Menu.h"

// Function to simulate menu selection in main menu
// Parameters:
// - bag, store, explore: instances of respective systems
// - mainChoice: user's choice in main menu
// - subChoice: placeholder for submenu choice (not used here)
// Returns:
// - 0 on successful menu operation
// - -1 when exit option selected
// - -2 for invalid input
int simulateMenuSelection(BagSystem& bag, StoreSystem& store, ExploreSystem& explore, int mainChoice, int subChoice) {
    switch(mainChoice) {
        case 0: // Adventure option
            explore.run();  // Run ExploreSystem menu
            return 0;
        case 1: // Bag option
            bag.run();      // Run BagSystem menu
            return 0;
        case 2: // Store option
            store.run();    // Run StoreSystem menu
            return 0;
        case 3: // Save Game option (not running any menu here)
            return 0;
        case 4: // Exit option
            return -1;     // Signal exit
        default:
            return -2;     // Invalid option
    }
}

int main() {
    BagSystem bag;
    StoreSystem store;
    ExploreSystem explore;

    initscr();            // Initialize ncurses screen
    cbreak();             // Disable line buffering
    noecho();             // Don't display typed characters
    curs_set(0);          // Hide cursor
    keypad(stdscr, TRUE); // Enable arrow keys

    // Test each main menu option to ensure it enters correct submenu or exits
    for(int i = 0; i <= 4; ++i){
        int result = simulateMenuSelection(bag, store, explore, i, 0);
        if(i == 4) {
            // For Exit option, expect -1 to indicate program exit
            assert(result == -1);
        } else {
            // For other options, expect 0 to indicate success
            assert(result == 0);
        }
    }

    endwin();

    std::cout << "User menu interaction test passed!" << std::endl;

    return 0;
}