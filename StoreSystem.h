#ifndef STORESYSTEM_H
#define STORESYSTEM_H

#include"Player.h"
#include"Bag.h"

// StoreSystem handles the in-game shop (Potions and Poké Balls)
class StoreSystem {
private:
    int highlight; // current menu highlight index

public:
    StoreSystem();
    void run();                     // main store loop
    int drawStore();                // display store menu, return selected option
    void drawPurchaseFailed(int choice); // show purchase failed message
    ~StoreSystem();
};

#endif