#include"ExploreSystem.h"

namespace gameSystem{
    int ExploreSystem::exploreSystem(int choice){
        clear();
        vector<string> adventureOptions = {
        "Verdale Grove",
        "Abyria Reef",
        "Emberpeak Island",
        "\n",
        "Exit"
        };

        mvprintw(3, 5, ("Exploring " + adventureOptions.at(choice) + "...").c_str());
        refresh();

        string type;

        switch (choice)
        {
        case 0: type = "Grass"; break;
        case 1: type = "Water"; break;
        case 2: type = "Fire"; break;
        }

        int times = util::randInRange(2,4);

        this_thread::sleep_for(std::chrono::seconds(times));

        int stageChance = util::randInRange(0,99);
        int stage;

        if (stageChance < 15)      stage = 3;
        else if (stageChance < 40) stage = 2;
        else                        stage = 1;

        int level = stage * 10 - util::randInRange(0,9);

        int enterChance = util::randInRange(0,99);
        bool isEntry = (enterChance >= 20);

        choice = Menu::drawExploreMenu(isEntry,type,stage,level);
        
        endwin();

        return choice;
    }
}