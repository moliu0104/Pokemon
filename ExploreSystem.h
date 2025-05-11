#ifndef EXPLORESYSTEM
#define EXPLORESYSTEM

#include<chrono>
#include<thread>
#include<cstdlib>
#include<ctime>
#include<string>
#include<ncurses.h>
#include"Game.h"
#include"RandomUtil.h"

namespace gameSystem{
    class ExploreSystem{
    public:
        
        static int exploreSystem(int choice);
    };
}

#endif