#ifndef BAGSYSTEM_H
#define BAGSYSTEM_H

#include"Menu.h"

class BagSystem{
    enum BagOptions{
        Pokemon,
        Items,
        Exit
    };
public:
    BagSystem();
    void run();
    int drawPokeInfo();
    void drawItemInfo();
    bool drawSwitchBag();
};

#endif