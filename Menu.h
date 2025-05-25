#ifndef MENU_H
#define MENU_H

#include<vector>
#include<iostream>
#include<ncurses.h>
#include"Pokemon.h"
#include"PokemonDataBase.h"

using namespace std;

class Menu{
public:
    static void initColors();
    static int drawMenu(const vector<string> options, const vector<string> title, int options_y = 3, int options_x = 5, int title_y = 1, int title_x = 5);
};

#endif