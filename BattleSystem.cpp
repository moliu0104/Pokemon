#include"BattleSystem.h"

    BattleSystem::BattleSystem(Bag bag, PokemonEntity* wildPokemon){
        this -> bag = bag;
        this -> wildPokemon = wildPokemon;
        player = bag.getActive();
    }

    int BattleSystem::run(){
        // Get the terminal window size
        int height, width;
        getmaxyx(stdscr, height, width);

            // Print the status of player's Pokemon and wild Pokemon
            drawStatus(height/4, width/4, player,1); //Player
            drawStatus(height/4, width/4, wildPokemon,0); // Wild Pokemon
        return 0;
    }

    void BattleSystem::drawStatus(int y, int x, PokemonEntity* pokemon, bool isPlayer){
        clear();
        string name = pokemon->getName();
        int lvl = pokemon->getLevel();
        int maxHp = pokemon->getMaxHP();
        int hp = pokemon->getCurrentHP();

        Menu::initColors();

         if(isPlayer){
            attron(COLOR_PAIR(4));
        }else{
            attron(COLOR_PAIR(3));
        }

        mvprintw(y, x ,name.c_str());
        mvprintw(y, x+name.length()+1, "Lv.%d",lvl);

        int barWidth = 20;
        float frac = float(hp) / maxHp;
        int filled = int(barWidth * frac + 0.5f);

        for (int i = 0; i < barWidth; ++i) {
            move(y+1, x+i);
            if (i < filled) {
                addch(ACS_CKBOARD);
            } else {
                addch(' ');
            }
        }

        if(isPlayer){
            attron(COLOR_PAIR(4));
        }else{
            attron(COLOR_PAIR(3));
        }

        mvprintw(y+1, x+barWidth+1, "HP %d/%d", hp, maxHp);

        getch();
    }

    void BattleSystem::drawLog(int y, int x,vector<string>& logs) {
        attron(COLOR_PAIR(2));
        for(int i=0; i<logs.size(); i++){
            mvprintw(y+i, x, logs[i].c_str());
        }
        attroff(COLOR_PAIR(2));
    }

    int BattleSystem::drawMainMenu(int y, int x, int selected) {
        static const vector<string> opts = {"Fight","Bag","Switch","Run"};
        for(int i=0; i<opts.size(); i++){
            if(i==selected){
                attron(COLOR_PAIR(1));
                mvprintw(y+i, x, "> %s", opts[i].c_str());
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                mvprintw(y+i, x, "  %s", opts[i].c_str());
                attroff(COLOR_PAIR(2));
            }
        }
        return opts.size();
    }

    int drawMoveMenu(int y, int x,vector<Move> moves,int selected) {
        for(int i=0; i<moves.size(); i++){
            string text = moves[i].getName() + " (" +moves[i].getType() + "," +std::to_string(moves[i].getDamage()) +" dmg)";
            if(i==selected){
                attron(COLOR_PAIR(1));
                mvprintw(y+i, x, "> %s", text.c_str());
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                mvprintw(y+i, x, "  %s", text.c_str());
                attroff(COLOR_PAIR(2));
            }
        }
        return moves.size();
    }

    BattleSystem::~BattleSystem(){}
