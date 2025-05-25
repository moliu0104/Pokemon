#ifndef MENU_H
#define MENU_H

#include <vector>      // For std::vector, used to pass menu options and titles.
#include <iostream>    // For standard input/output (not always necessary in header, but commonly included).
#include <ncurses.h>   // For ncurses-based UI functions.
#include "Pokemon.h"   // To potentially reference Pokémon data in menus.
#include "PokemonDataBase.h" // Same, if database data is needed in menu rendering.

using namespace std;   // Use the standard namespace to avoid 'std::' prefix everywhere.

// Menu class handles all menu-related drawing and user input.
class Menu{
public:
    // Initialize all ncurses color pairs and custom colors.
    static void initColors();

    // Draw a menu on the screen.
    //   - options: List of menu options to display (one per line).
    //   - title: List of lines to use as the menu title/header.
    //   - options_y/options_x: Starting coordinates for options.
    //   - title_y/title_x: Starting coordinates for the title.
    // Returns: index (int) of the selected menu option.
    static int drawMenu(
        const vector<string> options,
        const vector<string> title,
        int options_y = 3,
        int options_x = 5,
        int title_y = 1,
        int title_x = 5
    );
};

#endif // MENU_H