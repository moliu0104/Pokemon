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


    ExploreSystem explore;
    Bag bag;
    explore.encounterWildPokemon("Grass");
    bag.addPokemon(explore.getWildPokemon());

    BattleSystem battle(bag, explore.getWildPokemon());

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
                choice = explore.run(choice);;
                if(choice == 0){
                    battle.run();
                }else{
                    index = 1;
                    continue;
                }
                
            }
        }
        else if(index == 4){

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


Game::~Game(){}