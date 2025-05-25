#include"BagSystem.h"
#include "Bag.h"      // 必须有这句
#include "Player.h"

BagSystem::BagSystem(){}


void BagSystem::run(){
    bool running = true;
    while(running){
        clear();
        int choice = Menu::drawMenu({"Pokemon","Items","Exit"},{"========= Bag ========="});        

        switch(choice){
            case BagOptions::Pokemon:
            while(1){
               int choice = drawPokeInfo();
               if(choice == 0){
                    drawSwitchBag();
               }else{
                    break;
               }
            }
            break;

            case BagOptions::Items:
            drawItemInfo();
            break;

            case BagOptions::Exit:
            running = false;
        }

    }
}
int BagSystem::drawPokeInfo(){
    clear();
    Menu::initColors();
    int h_win, w_win;
    getmaxyx(stdscr, h_win, w_win);

    PokemonEntity* pokemon = nullptr;
    int colNum = 6;

    vector<string> bagInfo;
    string info;

    for(int i = 0; i < colNum; i++){


        pokemon = player.getBag().getPokemonAt(i);

        info = string("    Bag") + to_string(i+1);

        if(i == player.getBag().getAcitiveIndex()){
            info = info + " (Active)";
        }
        bagInfo.push_back(info);

        info = string("-------------------");
        bagInfo.push_back(info);

        if(pokemon != nullptr){
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
            info = string("Empty Bag");
            bagInfo.push_back(info);
        }
        
        for(int j = 0; j < bagInfo.size(); j++){
            attron(COLOR_PAIR(2));
            mvprintw(3+j,i*(w_win/colNum),bagInfo[j].c_str());
            attroff(COLOR_PAIR(2));
        }

        bagInfo.clear();
    }

    int highlight = 0;
    int input;

    vector<string> options = {"Switch Active Bag","Exit"};

    while(1){
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

        input = getch();

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
            return highlight;
        }
    }

}

bool BagSystem::drawSwitchBag(){
    vector<string> title = {"=== Switch Pokemon ==="};
    vector<string> options;
    string text;

    for(int i = 0; i < player.getBag().getPokemonAmount(); i++){
        text = player.getBag().getPokemonAt(i)->getName() +" | "+ player.getBag().getPokemonAt(i)->getType() + " | Lv." + to_string(player.getBag().getPokemonAt(i)->getLevel());
        options.push_back(text);
    }

    text = "\n";
    options.push_back(text);

    text = "Exit";
    options.push_back(text);

    int choice = Menu::drawMenu(options,title);

    if(choice == options.size()-1){
        return false;
    }

    player.getBag().switchActive(choice);
    return true;
}

void BagSystem::drawItemInfo(){
    clear();
    Menu::drawMenu({"Exit"},{"========= Bag =========","\n","Potion\t\tx" + to_string(player.getBag().getPotionAmount()),"Pokémon Ball\tx" + to_string(player.getBag().getBallAmount())},10);
}