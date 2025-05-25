#include"BattleSystem.h"

    BattleSystem::BattleSystem(PokemonEntity* wildPokemon){
        playerPokemon = player.getActivePokemon();
        this -> wildPokemon = wildPokemon;
        options = {"Fight","Items","Switch","Run"};
        highlight = 0;

        haveballs = player.getBag().getBallAmount();
        havePotions = player.getBag().getPotionAmount();

        getmaxyx(stdscr, height, width);
    }

    void BattleSystem::run(){
        // Get the terminal window size
        int input;
        int choice;
        bool isFull_bag = false;

        if(player.getBag().getPokemonAmount() >= player.getBag().getPokemonCapacity()){
            isFull_bag = true;
        }

        bool running = true;
        while(running){
            clear();

            playerPokemon = player.getActivePokemon();

            // Print the status of player's Pokemon and wild Pokemon
            drawStatus(height/8, 3, playerPokemon,1); //Player
            drawStatus(height/8, width*2/3, wildPokemon,0); // Wild Pokemon     

            choice = drawMainMenu(height*2/3,3);

            bool isHealed = false;
            bool isCaptured = false;
            bool rolledBalls = false;

            switch(choice){
                case BattleOptions::Fight:
                    if(!fight()){
                        continue;
                    }
                    break;

                case BattleOptions::Items:{
                    int choice = drawItemsMenu(height*2/3,0);
                    if(choice == 0){
                        isHealed = usePotion();
                        if(!havePotions){
                            continue;
                        }
                    }else if(choice == 1){
                        if(isFull_bag){
                            Menu::drawMenu({"Return"},{"Your bag is full! You can not capture any more Pokémon!"},2*height/3,3,height/4,3);
                            continue;
                        }else{
                            isCaptured = useBall();
                            rolledBalls = true;
                            if(!haveballs){
                                continue;
                            }
                        }
                    }else{
                        continue;
                    }
                    break;
                }

                case BattleOptions::Switch:
                    switchPokemon();
                    continue;
                    break;
                
                case BattleOptions::Run:
                    running = false;
                    runAway();
                    player.getBag().healAllPokemon();
                    continue;
            }

            if(rolledBalls){
                if(isCaptured){
                    drawCaptureScreen();
                    running = false;
                    player.getBag().healAllPokemon();
                    continue;
                }else{
                    clear();
                    drawStatus(height/8, 3, playerPokemon,1); //Player
                    drawStatus(height/8, width*2/3, wildPokemon,0); // Wild Pokemon 
                    string log = "The Pokémon broke free!";
                    drawLog(height/3,width/3 - 5,log);
                    refresh();
                    this_thread::sleep_for(std::chrono::seconds(2));
                }
            }

            if(wildPokemon->isFainted()){
                running = false;
                playerWin();
                player.getBag().healAllPokemon();
                continue;
            }

            wildPokemonTure();

            if(playerPokemon->isFainted()){

                bool canFight = false;
                bool isKeepFighting = false;
                for(int i = 0; i < player.getBag().getPokemonAmount() ; i++){
                    if(!player.getBag().getPokemonAt(i)->isFainted()){
                        canFight = true;
                    }
                }
                if(canFight){
                    isKeepFighting = switchAlivePokemon();

                    if(!isKeepFighting){
                        running = false;
                        player.getBag().healAllPokemon();
                        continue;
                    }
                }else{
                    drawDefeatScreen();
                    player.getBag().healAllPokemon();
                    running = false;
                    continue;
                
            }
        }
    }

    if(player.getBag().getActive()->canLevelUp()){
        player.getBag().getActive()->levelUp();
    }

    if(player.getBag().getActive()->canEvolve()){
        player.getBag().evolve(player.getBag().getAcitiveIndex());
    }
}

    bool BattleSystem::fight(){
        int choice = drawMoveMenu(height*2/3,0,playerPokemon->getMoveSet());

        int hp_before = wildPokemon->getCurrentHP();

        if(choice < 4){
            playerPokemon->attack(wildPokemon,playerPokemon->getMoveSet().at(choice));
        }else{
            return false;
        }

        int hp_after = wildPokemon->getCurrentHP();
       
        clear();
            // Print the status of player's Pokemon and wild Pokemon
        drawStatus(height/8, 3, playerPokemon,1); //Player
        drawStatus(height/8, width*2/3, wildPokemon,0); // Wild Pokemon  

        drawLog(height/3,width/3 - 5,playerPokemon->getName() + " used " + playerPokemon->getMoveSet().at(choice).getName()+ " and dealt " + to_string(hp_before - hp_after) + " to " + wildPokemon->getName() + "!");
        refresh();
        this_thread::sleep_for(std::chrono::seconds(2));

        return true;

    }

    void BattleSystem::wildPokemonTure(){
        int moveChoice = util::randInRange(0,3);

        int hp_before = playerPokemon->getCurrentHP();
        
        wildPokemon->attack(playerPokemon,wildPokemon->getMoveSet().at(moveChoice));

        int hp_after = playerPokemon->getCurrentHP();

        clear();
            // Print the status of player's Pokemon and wild Pokemon
        drawStatus(height/8, 3, playerPokemon,1); //Player
        drawStatus(height/8, width*2/3, wildPokemon,0); // Wild Pokemon  
        
        drawLog(height/3,width/3 - 5,wildPokemon->getName() + " used " + wildPokemon->getMoveSet().at(moveChoice).getName()+" and dealt " + to_string(hp_before - hp_after) + " to " + playerPokemon->getName());
        refresh();
        this_thread::sleep_for(std::chrono::seconds(2));
    }

    bool BattleSystem::usePotion(){
        string log;
        bool isHealed = false;

        if(player.getBag().getPotionAmount() > 0){
            int healed_before = playerPokemon->getCurrentHP();
            isHealed = player.getBag().usePotion();
            int healed_after = playerPokemon->getCurrentHP();
            log = string("You healed ") + playerPokemon->getName() + " by " + to_string(healed_after - healed_before);
        }else{
            log = string("You don't have enough Potions!");
            havePotions = false;
        }

        clear();
        drawStatus(height/8, 3, playerPokemon,1);
        drawStatus(height/8, width*2/3, wildPokemon,0);
        
        drawLog(height/3,width/3 - 5, log);
        refresh();
        this_thread::sleep_for(std::chrono::seconds(2));

        return isHealed;
    }

    bool BattleSystem::useBall(){
        string log;
        bool isCaptured = false;

        if(player.getBag().getBallAmount()){
            isCaptured = player.getBag().useBalls(wildPokemon);
            log = string("You rooled a Pokemon Ball!");
        }else{
            log = string("You don't have enough Pokemon Balls!");
            haveballs = false;
        }
        
        clear();
        drawStatus(height/8, 3, playerPokemon,1);
        drawStatus(height/8, width*2/3, wildPokemon,0);
        
        drawLog(height/3,width/3 - 5, log);
        refresh();
        this_thread::sleep_for(std::chrono::seconds(2));

        return isCaptured;
    }

    bool BattleSystem::switchPokemon(){
        vector<string> title = {"=== Switch Alive Pokemon ==="};
        vector<string> options;
        string text;

        int faintedIndex;

        while(1){
            for(int i = 0; i < player.getBag().getPokemonAmount(); i++){
                if(!player.getBag().getPokemonAt(i)->isFainted()){
                    text = player.getBag().getPokemonAt(i)->getName() +" | "+ player.getBag().getPokemonAt(i)->getType() + " | Lv." + to_string(player.getBag().getPokemonAt(i)->getLevel());
                    options.push_back(text);
                }else{
                    text = player.getBag().getPokemonAt(i)->getName() + " (Fainted)";
                    options.push_back(text);
                    faintedIndex = i;
                }
            }

            text = "\n";
            options.push_back(text);

            text = "Exit";
            options.push_back(text);

            int choice = Menu::drawMenu(options,title);

            if(choice == options.size()-1){
                return false;
            }

            if(choice == faintedIndex && player.getBag().getPokemonAt(faintedIndex)->isFainted()){
                Menu::drawMenu({"Return"},{"You can not select a Pokémon that has fainted. Please choose another one"},2*height/3,3,5,3);
                text.clear();
                options.clear();
                continue;
            }

            player.getBag().switchActive(choice);
            clear();
            // Print the status of player's Pokemon and wild Pokemon
            drawStatus(height/8, 3, playerPokemon,1); //Player
            drawStatus(height/8, width*2/3, wildPokemon,0); // Wild Pokemon

            drawLog(height/3,width/3 - 5, "You switched to " + player.getActivePokemon()->getName() + "!");
            refresh();
            this_thread::sleep_for(std::chrono::seconds(2));

            return true;
        }
    }

    bool BattleSystem::switchAlivePokemon(){
        vector<string> title = {"=== Switch Alive Pokemon ==="};
        vector<string> options;
        string text;

        int faintedIndex;

        while(1){
            for(int i = 0; i < player.getBag().getPokemonAmount(); i++){
                if(!player.getBag().getPokemonAt(i)->isFainted()){
                    text = player.getBag().getPokemonAt(i)->getName() +" | "+ player.getBag().getPokemonAt(i)->getType() + " | Lv." + to_string(player.getBag().getPokemonAt(i)->getLevel());
                    options.push_back(text);
                }else{
                    text = player.getBag().getPokemonAt(i)->getName() + " (Fainted)";
                    options.push_back(text);
                    faintedIndex = i;
                }
            }

            text = "\n";
            options.push_back(text);

            text = "Run Away";
            options.push_back(text);

            int choice = Menu::drawMenu(options,title);

            if(choice == options.size()-1){
                runAway();
                return false;
            }

            if(choice == faintedIndex){
                Menu::drawMenu({"Return"},{"You can not select a Pokémon that has fainted. Please choose another one"},2*height/3,3,5,3);
                text.clear();
                options.clear();
                continue;
            }

            player.getBag().switchActive(choice);
            return true;
        }
    }

    void BattleSystem::playerWin(){
        int gold = wildPokemon->getLevel()*50;
        int exp = wildPokemon->getLevel()*10;

        player.addMoney(gold);
        player.getActivePokemon()->addExp(exp);
        drawVictoryScreen(exp,gold);
    }    

    void BattleSystem::runAway(){
        clear();
        Menu::drawMenu({"Reture to Map Menu"},{"You run away safely!"},height*2/3,3,3,5);
    }

    void BattleSystem::drawStatus(int y, int x, PokemonEntity* pokemon, bool isPlayer){
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

        mvprintw(y, x ,"%s",name.c_str());
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
    }

    void BattleSystem::drawLog(int y, int x,string log) {
        attron(COLOR_PAIR(2));
        mvprintw(y, x, "%s",log.c_str());
        attroff(COLOR_PAIR(2));
    }

    int BattleSystem::drawMainMenu(int y, int x) {
        while(1){
            for(int i=0; i<options.size(); i++){
            if(i==highlight){
                attron(COLOR_PAIR(1));
                mvprintw(y+i, x, "> %s", options[i].c_str());
                attroff(COLOR_PAIR(1));
                } else {
                    attron(COLOR_PAIR(2));
                    mvprintw(y+i, x, "  %s", options[i].c_str());
                    attroff(COLOR_PAIR(2));
                }
            }

            int input = getch();

            switch (input){
            case KEY_UP:
                highlight = (highlight - 1 + options.size()) % options.size();
                break;
            
            case KEY_DOWN:
                highlight = (highlight + 1) % options.size();
                break;
            
            case '\n':
                return highlight;
            }
        }

    }

    int  BattleSystem::drawMoveMenu(int y, int x,vector<Move> moves) {
        int highlight = 0;
        vector<string> moveOptions;
        string text;
        for(int i = 0; i < moves.size();i++){
            text = moves[i].getName() + " (" +moves[i].getType() + "," +std::to_string(moves[i].getDamage()) +" dmg)";
            moveOptions.push_back(text);
        }

        text = "Exit";
        moveOptions.push_back(text);
        
        return Menu::drawMenu(moveOptions,{},height*2/3,3);
    }

    void BattleSystem::drawVictoryScreen(int exp, int gold){
        Menu::drawMenu({"Return to Map Menu"},{"  ** VICTORY **","You gained " + to_string(exp) + " EXP!","You obtained " + to_string(gold) + " Gold!"},height/3 + 4,width/3, height/3,width/3);
    }

    void BattleSystem::drawDefeatScreen(){
        Menu::drawMenu({"Return to Map Menu"},{"  ** DEFEAT **", "\n","All your Pokémon have fainted!"},height/3 + 4,width/3, height/3,width/3);
    }

    int BattleSystem::drawItemsMenu(int y, int x){
        vector<string> items = {"Potion\tx " + to_string(player.getBag().getPotionAmount()),"Pokémon Ball\t x " + to_string(player.getBag().getBallAmount()),"Exit"};
        int choice = Menu::drawMenu(items,{},y,x);
        return choice;
    }


    void BattleSystem::drawCaptureScreen(){
        Menu::drawMenu({"Return to Map Menu"},{"  ** CAUGHT SUCCESS! **","\n","Congratulations!","\n",string("You caught:") + wildPokemon->getName(),"Lv."+to_string(wildPokemon->getLevel()),"\n","It has been added to your Bag!"},height/3 + 8,width/3, 3,width/3);
    }

    BattleSystem::~BattleSystem(){}
