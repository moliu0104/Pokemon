#include"BattleSystem.h"

// Constructor: initialize the battle system with the wild Pokemon
BattleSystem::BattleSystem(PokemonEntity* wildPokemon){
    playerPokemon = player.getActivePokemon();             // Set the player's active Pokemon
    this->wildPokemon = wildPokemon;                       // Set the wild Pokemon pointer
    options = {"Fight","Items","Switch","Run"};            // Main battle menu options
    highlight = 0;                                         // Current highlighted option

    haveballs = player.getBag().getBallAmount();           // Number of Pokeballs player has
    havePotions = player.getBag().getPotionAmount();       // Number of Potions player has

    getmaxyx(stdscr, height, width);                       // Get window size for drawing UI
}

// Main loop of the battle
void BattleSystem::run(){
    int input;                                             // Store keyboard input
    int choice;                                            // Store menu choice
    bool isFull_bag = false;                               // Bag full flag

    // If the bag is full, set the flag
    if(player.getBag().getPokemonAmount() >= player.getBag().getPokemonCapacity()){
        isFull_bag = true;
    }

    bool running = true;                                   // Main loop flag
    while(running){
        clear();                                           // Clear the screen

        playerPokemon = player.getActivePokemon();         // Get the current active Pokemon

        // Draw player's and wild Pokemon's status on the screen
        drawStatus(height/8, 3, playerPokemon,1);          // Draw player's Pokemon status
        drawStatus(height/8, width*2/3, wildPokemon,0);    // Draw wild Pokemon status

        choice = drawMainMenu(height*2/3,3);               // Show main menu and get choice

        bool isHealed = false;                             // Used potion flag
        bool isCaptured = false;                           // Captured flag
        bool rolledBalls = false;                          // Used Pokeball flag

        switch(choice){
            case BattleOptions::Fight:                     // "Fight" option
                if(!fight()){                              // If fight was cancelled, continue loop
                    continue;
                }
                break;

            case BattleOptions::Items:{                    // "Items" option
                int choice = drawItemsMenu(height*2/3,0);  // Draw item menu
                if(choice == 0){                           // Player chose potion
                    isHealed = usePotion();                // Try to use potion
                    if(!havePotions){                      // If no potions left, skip
                        continue;
                    }
                }else if(choice == 1){                     // Player chose Pokeball
                    if(isFull_bag){                        // If bag is full, can't catch Pokemon
                        Menu::drawMenu({"Return"},{"Your bag is full! You can not capture any more Pokémon!"},2*height/3,3,height/4,3);
                        continue;
                    }else{
                        isCaptured = useBall();            // Try to catch Pokemon
                        rolledBalls = true;                // Mark that a Pokeball was thrown
                        if(!haveballs){                    // If no balls left, skip
                            continue;
                        }
                    }
                }else{                                     // "Exit" or other option
                    continue;
                }
                break;
            }

            case BattleOptions::Switch:                    // "Switch Pokemon" option
                switchPokemon();                           // Show switch menu
                continue;                                  // Back to menu after switch
                break;
            
            case BattleOptions::Run:                       // "Run" option
                running = false;                           // End battle loop
                runAway();                                 // Show run away screen
                player.getBag().healAllPokemon();          // Heal all after running away
                continue;
        }

        // After using Pokeball, check if wild Pokemon was caught
        if(rolledBalls){
            if(isCaptured){                                // If caught, show success screen
                drawCaptureScreen();
                running = false;
                player.getBag().healAllPokemon();          // Heal all after battle
                continue;
            }else{                                         // If failed, show message
                clear();
                drawStatus(height/8, 3, playerPokemon,1);
                drawStatus(height/8, width*2/3, wildPokemon,0);
                string log = "The Pokémon broke free!";
                drawLog(height/3,width/3 - 5,log);
                refresh();
                this_thread::sleep_for(std::chrono::seconds(2)); // Wait for 2 seconds
            }
        }

        // If wild Pokemon fainted, player wins
        if(wildPokemon->isFainted()){
            running = false;
            playerWin();                                   // Reward player
            player.getBag().healAllPokemon();              // Heal all after battle
            continue;
        }

        wildPokemonTure();                                // Wild Pokemon's turn to attack

        // If player's Pokemon fainted
        if(playerPokemon->isFainted()){
            bool canFight = false;                         // If player has any alive Pokemon
            bool isKeepFighting = false;
            for(int i = 0; i < player.getBag().getPokemonAmount() ; i++){
                if(!player.getBag().getPokemonAt(i)->isFainted()){
                    canFight = true;
                }
            }
            if(canFight){
                isKeepFighting = switchAlivePokemon();     // Ask to switch Pokemon

                if(!isKeepFighting){                       // If player gives up, end battle
                    running = false;
                    player.getBag().healAllPokemon();
                    continue;
                }
            }else{                                         // If all Pokemon fainted, defeat
                drawDefeatScreen();
                player.getBag().healAllPokemon();
                running = false;
                continue;
            }
        }
    }

    // After the battle, check for level up
    if(player.getBag().getActive()->canLevelUp()){
        player.getBag().getActive()->levelUp();            // Level up if enough exp
    }

    // After level up, check for evolution
    if(player.getBag().getActive()->canEvolve()){
        player.getBag().evolve(player.getBag().getAcitiveIndex()); // Evolve if conditions met
    }
}

    // Handles player's attack turn
bool BattleSystem::fight(){
    int choice = drawMoveMenu(height*2/3,0,playerPokemon->getMoveSet());      // Show move menu and get player's move choice

    int hp_before = wildPokemon->getCurrentHP();                              // Store wild Pokemon's HP before attack

    if(choice < 4){                                                           // If a valid move is selected
        playerPokemon->attack(wildPokemon,playerPokemon->getMoveSet().at(choice)); // Player's Pokemon attacks wild Pokemon
    }else{
        return false;                                                         // Cancelled or chose exit
    }

    int hp_after = wildPokemon->getCurrentHP();                               // Wild Pokemon's HP after attack

    clear();                                                                  // Clear screen for update
    drawStatus(height/8, 3, playerPokemon,1);                                 // Redraw player's Pokemon status
    drawStatus(height/8, width*2/3, wildPokemon,0);                           // Redraw wild Pokemon status

    // Show damage message
    drawLog(height/3,width/3 - 5,playerPokemon->getName() + " used " + playerPokemon->getMoveSet().at(choice).getName()+ " and dealt " + to_string(hp_before - hp_after) + " to " + wildPokemon->getName() + "!");
    refresh();
    this_thread::sleep_for(std::chrono::seconds(2));                          // Pause for 2 seconds

    return true;                                                              // Attack completed
}

// Handles wild Pokemon's attack turn
void BattleSystem::wildPokemonTure(){
    int moveChoice = util::randInRange(0,3);                                  // Randomly select a move

    int hp_before = playerPokemon->getCurrentHP();                            // Player's Pokemon HP before attack
    
    wildPokemon->attack(playerPokemon,wildPokemon->getMoveSet().at(moveChoice)); // Wild Pokemon attacks

    int hp_after = playerPokemon->getCurrentHP();                             // Player's Pokemon HP after attack

    clear();                                                                  // Clear screen
    drawStatus(height/8, 3, playerPokemon,1);                                 // Redraw player's Pokemon status
    drawStatus(height/8, width*2/3, wildPokemon,0);                           // Redraw wild Pokemon status
    
    // Show damage message
    drawLog(height/3,width/3 - 5,wildPokemon->getName() + " used " + wildPokemon->getMoveSet().at(moveChoice).getName()+" and dealt " + to_string(hp_before - hp_after) + " to " + playerPokemon->getName());
    refresh();
    this_thread::sleep_for(std::chrono::seconds(2));                          // Pause for 2 seconds
}

// Try to use a potion on the player's active Pokemon
bool BattleSystem::usePotion(){
    string log;                                                               // Message to display
    bool isHealed = false;                                                    // Was healing successful

    if(player.getBag().getPotionAmount() > 0){                                // If player has potion
        int healed_before = playerPokemon->getCurrentHP();                    // HP before healing
        isHealed = player.getBag().usePotion();                               // Use potion
        int healed_after = playerPokemon->getCurrentHP();                     // HP after healing
        log = string("You healed ") + playerPokemon->getName() + " by " + to_string(healed_after - healed_before); // Show healing amount
    }else{
        log = string("You don't have enough Potions!");                       // Not enough potions
        havePotions = false;                                                  // Update status
    }

    clear();                                                                  // Clear screen
    drawStatus(height/8, 3, playerPokemon,1);                                 // Redraw player's Pokemon status
    drawStatus(height/8, width*2/3, wildPokemon,0);                           // Redraw wild Pokemon status
    
    drawLog(height/3,width/3 - 5, log);                                       // Show healing or error log
    refresh();
    this_thread::sleep_for(std::chrono::seconds(2));                          // Pause for 2 seconds

    return isHealed;                                                          // Return healing status
}

// Try to use a Pokeball to capture the wild Pokemon
bool BattleSystem::useBall(){
    string log;                                                               // Message to display
    bool isCaptured = false;                                                  // Was capture successful

    if(player.getBag().getBallAmount()){                                      // If player has Pokeballs
        isCaptured = player.getBag().useBalls(wildPokemon);                   // Try to capture wild Pokemon
        log = string("You rooled a Pokemon Ball!");                           // Roll Pokeball message
    }else{
        log = string("You don't have enough Pokemon Balls!");                 // Not enough balls
        haveballs = false;                                                    // Update status
    }
    
    clear();                                                                  // Clear screen
    drawStatus(height/8, 3, playerPokemon,1);                                 // Redraw player's Pokemon status
    drawStatus(height/8, width*2/3, wildPokemon,0);                           // Redraw wild Pokemon status
    
    drawLog(height/3,width/3 - 5, log);                                       // Show capture or error log
    refresh();
    this_thread::sleep_for(std::chrono::seconds(2));                          // Pause for 2 seconds

    return isCaptured;                                                        // Return capture status
}

// Switch the currently active Pokemon (from all Pokemon, including fainted)
bool BattleSystem::switchPokemon(){
    vector<string> title = {"=== Switch Alive Pokemon ==="};                  // Menu title
    vector<string> options;                                                   // List of options
    string text;                                                              // Option text

    int faintedIndex[6] = {0};                                                // Mark fainted Pokemon

    while(1){
        for(int i = 0; i < player.getBag().getPokemonAmount(); i++){
            if(!player.getBag().getPokemonAt(i)->isFainted()){                // If not fainted
                text = player.getBag().getPokemonAt(i)->getName() +" | "+ player.getBag().getPokemonAt(i)->getType() + " | Lv." + to_string(player.getBag().getPokemonAt(i)->getLevel());
                options.push_back(text);                                      // Add to menu
            }else{
                text = player.getBag().getPokemonAt(i)->getName() + " (Fainted)";
                options.push_back(text);                                      // Mark as fainted
                faintedIndex[i] = 1;
            }
        }

        text = "\n";                                                          // Menu separator
        options.push_back(text);

        text = "Exit";                                                        // Exit option
        options.push_back(text);

        int choice = Menu::drawMenu(options,title);                           // Draw menu and get choice

        if(choice == options.size()-1){                                       // If exit selected
            return false;
        }

        if(faintedIndex[choice]){                                             // Prevent choosing fainted Pokemon
            Menu::drawMenu({"Return"},{"You can not select a Pokémon that has fainted. Please choose another one"},2*height/3,3,5,3);
            text.clear();
            options.clear();
            continue;
        }

        player.getBag().switchActive(choice);                                 // Switch Pokemon
        clear();
        drawStatus(height/8, 3, playerPokemon,1);                             // Redraw player's Pokemon status
        drawStatus(height/8, width*2/3, wildPokemon,0);                       // Redraw wild Pokemon status

        drawLog(height/3,width/3 - 5, "You switched to " + player.getActivePokemon()->getName() + "!");
        refresh();
        this_thread::sleep_for(std::chrono::seconds(2));                      // Pause for 2 seconds

        return true;
    }
}

// Switch only to an alive Pokemon (used when active Pokemon faints)
bool BattleSystem::switchAlivePokemon(){
    vector<string> title = {"=== Switch Alive Pokemon ==="};
    vector<string> options;
    string text;

    int faintedIndex[6] = {0};

    while(1){
        for(int i = 0; i < player.getBag().getPokemonAmount(); i++){
            if(!player.getBag().getPokemonAt(i)->isFainted()){
                text = player.getBag().getPokemonAt(i)->getName() +" | "+ player.getBag().getPokemonAt(i)->getType() + " | Lv." + to_string(player.getBag().getPokemonAt(i)->getLevel());
                options.push_back(text);
            }else{
                text = player.getBag().getPokemonAt(i)->getName() + " (Fainted)";
                options.push_back(text);
                faintedIndex[i] = 1;
            }
        }

        text = "\n";
        options.push_back(text);

        text = "Run Away";                                                    // Option to flee battle
        options.push_back(text);

        int choice = Menu::drawMenu(options,title);                           // Draw menu

        if(choice == options.size()-1){                                       // If "Run Away" selected
            runAway();                                                        // Run from battle
            return false;
        }

        if(faintedIndex[choice]){                                             // Prevent choosing fainted
            Menu::drawMenu({"Return"},{"You can not select a Pokémon that has fainted. Please choose another one"},2*height/3,3,5,3);
            text.clear();
            options.clear();
            continue;
        }

        player.getBag().switchActive(choice);                                 // Switch to selected Pokemon
        return true;
    }
}

// Called when player wins a battle against a wild Pokemon
void BattleSystem::playerWin(){
    int gold = wildPokemon->getLevel()*50;                                    // Calculate gold reward
    int exp = wildPokemon->getLevel()*10;                                     // Calculate EXP reward

    player.addMoney(gold);                                                    // Give player gold
    player.getActivePokemon()->addExp(exp);                                   // Give active Pokemon EXP
    drawVictoryScreen(exp,gold);                                              // Show victory message
}

// Called when the player chooses to run away from battle
void BattleSystem::runAway(){
    clear();                                                                  // Clear screen
    Menu::drawMenu({"Return to Map Menu"},{"You run away safely!"},height*2/3,3,3,5); // Show message
}

   // Draw the status of a Pokémon (name, level, HP bar) at (y, x)
void BattleSystem::drawStatus(int y, int x, PokemonEntity* pokemon, bool isPlayer){
    string name = pokemon->getName();                  // Get Pokémon name
    int lvl = pokemon->getLevel();                     // Get Pokémon level
    int maxHp = pokemon->getMaxHP();                   // Get Pokémon max HP
    int hp = pokemon->getCurrentHP();                  // Get Pokémon current HP

    Menu::initColors();                               // Initialize color pairs for drawing

    // Choose color for player or wild Pokémon
    if(isPlayer){
        attron(COLOR_PAIR(4));                        // Use color pair 4 for player
    }else{
        attron(COLOR_PAIR(3));                        // Use color pair 3 for wild Pokémon
    }

    mvprintw(y, x ,"%s",name.c_str());                // Print Pokémon name
    mvprintw(y, x+name.length()+1, "Lv.%d",lvl);      // Print Pokémon level after name

    int barWidth = 20;                                // HP bar width
    float frac = float(hp) / maxHp;                   // Fraction of HP remaining
    int filled = int(barWidth * frac + 0.5f);         // Number of filled blocks

    // Draw HP bar: filled for current HP, empty for lost HP
    for (int i = 0; i < barWidth; ++i) {
        move(y+1, x+i);                               // Move cursor to correct spot
        if (i < filled) {
            addch(ACS_CKBOARD);                       // Filled block
        } else {
            addch(' ');                               // Empty space
        }
    }

    // Use correct color again for HP numbers
    if(isPlayer){
        attron(COLOR_PAIR(4));
    }else{
        attron(COLOR_PAIR(3));
    }

    mvprintw(y+1, x+barWidth+1, "HP %d/%d", hp, maxHp); // Show current/max HP as text
}

// Draw a log or info message at (y, x)
void BattleSystem::drawLog(int y, int x,string log) {
    attron(COLOR_PAIR(2));                            // Use color pair 2 for logs
    mvprintw(y, x, "%s",log.c_str());                 // Print the log text
    attroff(COLOR_PAIR(2));                           // Turn off color
}

// Draws the main battle menu ("Fight", "Items", "Switch", "Run")
int BattleSystem::drawMainMenu(int y, int x) {
    while(1){
        for(int i=0; i<options.size(); i++){
            if(i==highlight){
                attron(COLOR_PAIR(1));                // Highlight current option
                mvprintw(y+i, x, "> %s", options[i].c_str());
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));                // Normal color for others
                mvprintw(y+i, x, "  %s", options[i].c_str());
                attroff(COLOR_PAIR(2));
            }
        }

        int input = getch();                          // Wait for keyboard input

        switch (input){
        case KEY_UP:
            highlight = (highlight - 1 + options.size()) % options.size(); // Move up in menu
            break;
        
        case KEY_DOWN:
            highlight = (highlight + 1) % options.size();                  // Move down in menu
            break;
        
        case '\n':
            return highlight;                                             // Confirm selection
        }
    }
}

// Draw move selection menu with all available moves for current Pokémon
int BattleSystem::drawMoveMenu(int y, int x,vector<Move> moves) {
    int highlight = 0;                                   // Index of selected move
    vector<string> moveOptions;
    string text;
    for(int i = 0; i < moves.size();i++){
        // Build text like "Tackle (Normal,40 dmg)"
        text = moves[i].getName() + " (" +moves[i].getType() + "," +std::to_string(moves[i].getDamage()) +" dmg)";
        moveOptions.push_back(text);                     // Add to option list
    }

    text = "Exit";                                       // Add exit option at the end
    moveOptions.push_back(text);
    
    return Menu::drawMenu(moveOptions,{},height*2/3,3);  // Call generic menu drawer
}

// Draw the victory screen after winning a battle
void BattleSystem::drawVictoryScreen(int exp, int gold){
    // Show "Victory", EXP and Gold reward
    Menu::drawMenu({"Return to Map Menu"},
        {"  ** VICTORY **",
         "You gained " + to_string(exp) + " EXP!",
         "You obtained " + to_string(gold) + " Gold!"},
        height/3 + 4,width/3, height/3,width/3);
}

// Draw the defeat screen after losing a battle
void BattleSystem::drawDefeatScreen(){
    // Show "Defeat" message
    Menu::drawMenu({"Return to Map Menu"},
        {"  ** DEFEAT **", "\n","All your Pokémon have fainted!"},
        height/3 + 4,width/3, height/3,width/3);
}

// Draw the items menu (for potions/balls)
int BattleSystem::drawItemsMenu(int y, int x){
    // Build items option list with counts
    vector<string> items = {
        "Potion\tx " + to_string(player.getBag().getPotionAmount()),
        "Pokémon Ball\t x " + to_string(player.getBag().getBallAmount()),
        "Exit"};
    int choice = Menu::drawMenu(items,{},y,x);          // Call generic menu drawer
    return choice;                                      // Return player's choice
}

// Draw the capture success screen
void BattleSystem::drawCaptureScreen(){
    // Show "Caught" and info about the caught Pokemon
    Menu::drawMenu({"Return to Map Menu"},
        {"  ** CAUGHT SUCCESS! **",
         "\n",
         "Congratulations!",
         "\n",
         string("You caught:") + wildPokemon->getName(),
         "Lv."+to_string(wildPokemon->getLevel()),
         "\n",
         "It has been added to your Bag!"},
        height/3 + 8,width/3, 3,width/3);
}

// Destructor (currently does nothing special)
BattleSystem::~BattleSystem(){}