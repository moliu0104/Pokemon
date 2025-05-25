#ifndef STORESYSTEM_H
#define STORESYSTEM_H

#include"Player.h"
#include"Bag.h"

class StoreSystem{
private:
    int highlight;
public:
    StoreSystem();
    void run();
    int drawStore();
    void drawPurchseFailed(int choice);
    ~StoreSystem();
};

#endif