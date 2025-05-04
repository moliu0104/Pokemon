#include"Game.h"

Game::Game(){

    // Main Menu
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

    // Adventure
    adventureOptions = {
        "Verdale Grove",
        "Abyria Reef",
        "Emberpeak Island",
        "\n",
        "Exit"
    };

}

void Game::run(){
    showMainMenu();
}


int Game::showMainMenu(){
    vector<string> title = {"========= Pokémon ========"};

   int choice = Menu::drawMenu(mainMenuOptions,title);
   
   switch (choice)
   {
   case 0:
    showAdventure();
    break;
   
   case 7:
    break;
   }

   return 0;

}

void Game::showAdventure(){
    vector<string> title = {"========= Expedition Routes =========="};

    int choice = Menu::drawMenu(adventureOptions,title);

    switch (choice)
    {
    case 0:
        exploreMap(0);
        break;
    case 1:
        exploreMap(1);
        break;
    case 2:
        exploreMap(2);
        break;
    case 4:
        showMainMenu();
        break;
    default:
        break;
    }
}

void Game::exploreMap(int choice){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    clear();

    mvprintw(3, 5, ("Exploring " + adventureOptions.at(choice) + "...").c_str());
    refresh();

    string type;

    switch (choice)
    {
    case 0:
        type = "Grass";
        break;
    
    case 1:
        type = "Water";
        break;
    case 2:
        type = "Fire";
        break;
    }

    srand(time(0));
    int times = rand()%2 + 2;

    std::this_thread::sleep_for(std::chrono::seconds(times));

    int enterChance = rand() % 100;
    int stageChance = 60;
    int stage;
    int level;

    level = stage * 10 - rand() % 9;

    if(stageChance < 15){
        stage = 3;
    }else if(stageChance < 40){
        stage = 2;
    }else{
        stage = 1;
    }

    vector<Pokemon> wildPokemon;

    if(enterChance < 20){
        highlight = Menu::drawMenu({"Return to Map Menu", "Keep Exploring"},{"You didn't find any Pokémon"}, 5,7,3,7,2);

    }else{
        vector<Pokemon> p = allPokemon.findPokemonByType(type);

        for(int i = 0; i < p.size(); i++){
            if(stage == p[i].getStage()){
                wildPokemon.push_back(p[i]);
            }
        }
        int index = rand() % wildPokemon.size();
        vector<string> title = {"You found a Pokémon!","-> Name: " + wildPokemon[index].getName() + " | " + "Leve: " + to_string(level)};
        highlight = Menu::drawMenu({"Run Away (Return to Map Menu)", "Enter Battel"},title,7,7,3,7,2);
        
    }

    if(highlight == 0){
        showAdventure();
    }else if(highlight == 1 && enterChance){
        exploreMap(choice);
    }else{}    
    
    getch();

    endwin();
}


Game::~Game(){}