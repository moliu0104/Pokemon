#include"Game.h"

Game::Game(){

    mainMenuTitle = {"========= Pokémon ========"};
    mainMenuOptions = {
        "Adventure",
        "Challenge",
        "Train",
        "Bag",
        "Inventory",
        "Store",
        "Save Game",
        "Exit"
    };

    adventureTitle = {"========= Expedition Routes =========="};
    adventureOptions = {
        "Verdale Grove",
        "Abyria Reef",
        "Emberpeak Island",
        "\n",
        "Exit"
    };
 
}

vector<string> Game::getAdventureOptions(){
    return adventureOptions;
}

void Game::run(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int index = 0;
    int choice;

    while (1)
    {   
        
        if(index == 0){
            index  = showMainMenu() + 1;
        }
        else if(index == 1){
            choice = showAdventure();

            if(choice == 4){
                index = 0;
                continue;
            }else{
                choice = exploreMap(choice);
                if(choice == 0){
                    Menu::drawStatus(2, 10, "Myles", 10, 20, 20, true);
                }else{
                    index = 1;
                    continue;
                }
                
            }
        }
        else{
            break;
        }
    }
}


int Game::showMainMenu(){

   highlight = Menu::drawMenu(mainMenuOptions,mainMenuTitle);
   
   return highlight;

}

int Game::showAdventure(){

    highlight = Menu::drawMenu(adventureOptions,adventureTitle);

    return highlight;
}

int Game::exploreMap(int choice){
    
    highlight = gameSystem::ExploreSystem::exploreSystem(choice);
    return highlight;
}


Game::~Game(){}