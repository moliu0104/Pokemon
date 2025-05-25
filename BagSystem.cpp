#include"BagSystem.h"
#include "Bag.h"      // Must include Bag for player.getBag()
#include "Player.h"

BagSystem::BagSystem(){} // Constructor

// Main run loop for BagSystem
void BagSystem::run(){
    bool running = true; // Flag to control the main loop
    while(running){
        clear(); // Clear the ncurses screen
        // Show main bag menu: Pokemon, Items, Exit
        int choice = Menu::drawMenu({"Pokemon","Items","Exit"},{"========= Bag ========="});        

        switch(choice){
            case BagOptions::Pokemon:
                // Pokemon submenu loop
                while(1){
                    int choice = drawPokeInfo(); // Show Pokemon info and actions
                    if(choice == 0){
                        drawSwitchBag(); // Option to switch active Pokemon
                    }else{
                        break; // Exit Pokemon submenu
                    }
                }
                break;

            case BagOptions::Items:
                drawItemInfo(); // Show items (Potions, Balls)
                break;

            case BagOptions::Exit:
                running = false; // Exit Bag menu
        }
    }
}

// Draw info for each Pokemon in the bag
int BagSystem::drawPokeInfo(){
    clear(); // Clear the screen
    Menu::initColors(); // Setup color pairs
    int h_win, w_win;
    getmaxyx(stdscr, h_win, w_win); // Get window size

    PokemonEntity* pokemon = nullptr;
    int colNum = 6; // Number of bag slots

    vector<string> bagInfo; // Temporary info for display
    string info;

    for(int i = 0; i < colNum; i++){
        pokemon = player.getBag().getPokemonAt(i); // Get Pokemon at slot i

        info = string("    Bag") + to_string(i+1); // Bag index label

        if(i == player.getBag().getAcitiveIndex()){
            info = info + " (Active)"; // Mark as active if needed
        }
        bagInfo.push_back(info);

        info = string("-------------------");
        bagInfo.push_back(info);

        if(pokemon != nullptr){
            // Fill in Pokemon stats if exists
            info = string("Name: ") + pokemon->getName() + string("   Lv.") + to_string(pokemon->getLevel());
            bagInfo.push_back(info);

            info = string("Stage: ") + to_string(pokemon->getStage());
            bagInfo.push_back(info);

            info = string("Type: ") + pokemon->getType();
            bagInfo.push_back(info);

            info = string("HP: ") + to_string(pokemon->getCurrentHP()) + "/" + to_string(pokemon->getMaxHP());
            bagInfo.push_back(info);

            info = string("EXP: ") + to_string(pokemon->getExp());
            bagInfo.push_back(info);
        }else{
            // Show empty slot
            info = string("Empty Bag");
            bagInfo.push_back(info);
        }
        
        // Print bag info for this slot in a column
        for(int j = 0; j < bagInfo.size(); j++){
            attron(COLOR_PAIR(2));
            mvprintw(3+j,i*(w_win/colNum),bagInfo[j].c_str());
            attroff(COLOR_PAIR(2));
        }
        bagInfo.clear(); // Reset for next column
    }

    int highlight = 0; // Menu selection index
    int input;

    vector<string> options = {"Switch Active Bag","Exit"}; // Actions for user

    while(1){
        // Draw menu options at the bottom
        for(int i = 0; i< options.size();i++){
            if(i == highlight){
                attron(COLOR_PAIR(1));
                mvprintw(13+i,0,"> %s",options[i].c_str());
                attroff(COLOR_PAIR(1));
            }else{
                attron(COLOR_PAIR(2));
                mvprintw(13+i,0,"  %s",options[i].c_str());
                attroff(COLOR_PAIR(2));
            }
        }

        input = getch(); // Wait for user input

        switch (input)
        {
        case KEY_UP:
            highlight = (highlight - 1 + options.size()) % options.size();
            if(options[highlight] == "\n"){
                highlight--;
            }
            break;
        
        case KEY_DOWN:
            highlight = (highlight + 1) % options.size();
            if(options[highlight] == "\n"){
                highlight++;
            }
            break;
        
        case '\n':
            return highlight; // Return selection
        }
    }
}

// Draw menu for switching active Pokemon
bool BagSystem::drawSwitchBag(){
    vector<string> title = {"=== Switch Pokemon ==="};
    vector<string> options;
    string text;

    // Fill in all available Pokemon as menu options
    for(int i = 0; i < player.getBag().getPokemonAmount(); i++){
        text = player.getBag().getPokemonAt(i)->getName() +" | "+ player.getBag().getPokemonAt(i)->getType() + " | Lv." + to_string(player.getBag().getPokemonAt(i)->getLevel());
        options.push_back(text);
    }

    text = "\n"; // Add blank line
    options.push_back(text);

    text = "Exit";
    options.push_back(text); // Add exit option

    int choice = Menu::drawMenu(options,title); // Show menu and get choice

    if(choice == options.size()-1){
        return false; // If Exit selected, return false
    }

    player.getBag().switchActive(choice); // Switch active Pokemon
    return true;
}

// Draw info for items in the bag
void BagSystem::drawItemInfo(){
    clear();
    // Draw item info and amount, with exit option
    Menu::drawMenu(
        {"Exit"},
        {
            "========= Bag =========",
            "\n",
            "Potion\t\tx" + to_string(player.getBag().getPotionAmount()),
            "Pokémon Ball\tx" + to_string(player.getBag().getBallAmount())
        },
        10
    );
}