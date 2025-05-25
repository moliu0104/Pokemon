#include"StoreSystem.h"
StoreSystem::StoreSystem(){
    highlight = 0;
}

void StoreSystem::run(){
    Potion potion;
    PokemonBall ball;
    bool running = true;
    while(running){
        int choice = drawStore();

        switch(choice){
            case 0:
                if(player.getMoneyAmount() < potion.getPrice()){
                    drawPurchseFailed(choice);
                }else{
                    player.spendMoney(potion.getPrice());
                    player.getBag().addPotion(1);
                }
                
                break;
            
            case 1:
                if(player.getMoneyAmount() < ball.getPrice()){
                    drawPurchseFailed(choice);
                }else{
                    player.getBag().addBalls(1);
                    player.spendMoney(ball.getPrice());
                }
                break;
            
            default:
                running = false;
                break;
        }
    }
}

int StoreSystem::drawStore(){
    int input;
    Potion potion;
    PokemonBall ball;

    vector<string> playerOwned;
    vector<string> options = {string("Potion:\t\t")+"Price: "+ to_string(potion.getPrice()) + " G",
                                string("Pokémon Ball:\t")+"Price: " + to_string(ball.getPrice()) + " G",
                                string("\n"),
                                string("Exit")};
    string text;

    while(1){
        clear();
        text = string("You have:\tGold: ") + to_string(player.getMoneyAmount());
        playerOwned.push_back(text);

        text = string("You Owned:\tPotion: x") + to_string(player.getBag().getPotionAmount()) + "\tPokémon Ball: x" + to_string(player.getBag().getBallAmount());
        playerOwned.push_back(text);

        attron(COLOR_PAIR(2));
        mvprintw(1,3,"%s","================= POKEMON STORE =================");
        for(int i = 0; i < playerOwned.size(); i++){
            mvprintw(2 + i,5,"%s",playerOwned[i].c_str());
        }
        mvprintw(4,3,"%s","-------------------------------------------------");
        attroff(COLOR_PAIR(2));

        playerOwned.clear();

        for(int i = 0; i < options.size(); i++){
            if(i == highlight){
                attron(COLOR_PAIR(1));
                mvprintw(5+i, 5, "> %s", options[i].c_str());
                attroff(COLOR_PAIR(1));
            }else{
                attron(COLOR_PAIR(2));
                mvprintw(5+i, 5, "  %s", options[i].c_str());
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

void StoreSystem::drawPurchseFailed(int choice){
    clear();
    string text;
    attron(COLOR_PAIR(2));
    mvprintw(2,3,"%s","!!! NOT ENOUGH GOLD !!!");

    text = string("You only have ") + to_string(player.getMoneyAmount()) + " G,";
    mvprintw(4,5,"%s", text.c_str());

    if(choice == 0){
        Potion p;

        text = string("But that costs ") +to_string(p.getPrice()) + "G.";
        mvprintw(5,5,"%s",text.c_str());
    }else if(choice == 1){
        PokemonBall b;

        text = string("But that costs ") + to_string(b.getPrice()) + "G.";
        mvprintw(5,5,"%s",text.c_str());
    }

    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(7, 5, "> %s", "Continue");
    attroff(COLOR_PAIR(1));

    getch();
}

StoreSystem::~StoreSystem(){}