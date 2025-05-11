#include"Menu.h"

void Menu::initColors(){
    if (!has_colors() || !can_change_color())
        return;     
    start_color();

    init_color(COLOR_CYAN,  494, 716, 886);
    init_color(COLOR_YELLOW, 977, 976, 444);
    init_color(COLOR_RED,    600, 100, 50);
   
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // 高亮
    init_pair(2, COLOR_WHITE, COLOR_BLACK);  // 普通文字
    init_pair(3, COLOR_RED,   COLOR_BLACK);  // 敌方HP条
    init_pair(4, COLOR_CYAN, COLOR_BLACK);  // 我方HP条
    init_pair(5, COLOR_YELLOW, COLOR_BLACK); // 日志文字
}


int Menu::drawMenu(const vector<string> options, const vector<string> title, int options_y, int options_x, int title_y, int title_x, int options_color,int title_color){
    initColors();
    // Set backgroud and character color

    int highlight = 0;
    int input;

    while(3){
        bkgd(COLOR_PAIR(2));
        clear();
        refresh();

        attron(COLOR_PAIR(title_color));
        for(int i = 0; i < title.size(); i++){
            mvprintw(title_y + i,title_x,title[i].c_str());
        }
        attroff(COLOR_PAIR(title_color));

        for(int i = 0; i < options.size(); i++){
            if(options[i] == "\n"){
                i++;
            }
            if(highlight == i){
                attron(A_REVERSE | COLOR_PAIR(options_color));
            }
            mvprintw(i + options_y, options_x, options[i].c_str());
            if(highlight == i){
                attroff(A_REVERSE | COLOR_PAIR(options_color));
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
            endwin();
            return highlight;
        }
    }
}

int Menu::drawExploreMenu(bool isEntry, string type, int stage, int level){
    clear();

    vector<Pokemon> wildPokemon;
    PokemonDataBase allPokemon;

    int highlight;
    if(!isEntry){
        highlight = Menu::drawMenu({"Keep Exploring","Return to Map Menu"},{"You didn't find any Pokémon"}, 5,7,3,7);

    }else{
        vector<Pokemon> pokemon_byType = allPokemon.findPokemonByType(type);

        for(int i = 0; i < pokemon_byType.size(); i++){
            if(stage == pokemon_byType[i].getStage()){
                wildPokemon.push_back(pokemon_byType[i]);
            }
        }
        int index = rand() % wildPokemon.size();
        vector<string> title = {"A Pokémon appeared!","-> Name: " + wildPokemon[index].getName() + " | " + "Level: " + to_string(level)};
        highlight = Menu::drawMenu({"Enter Battel","Run Away (Return to Map Menu)" },title,7,7,3,7);
        
    } 

    endwin();

    return highlight;
}

void Menu::drawStatus(int y, int x, string name, int lvl, int hp, int maxHp, bool isPlayer){
    clear();

    initColors();

    mvprintw(y, x ,name.c_str());
    mvprintw(y, x+name.length()+1, "Lv.%d",lvl);

    int barWidth = 20;
    float frac = float(hp) / maxHp;
    int filled = int(barWidth * frac + 0.5f);

    attron(COLOR_PAIR(4));

    // 用 ACS_CKBOARD （实心块）和空格
    for (int i = 0; i < barWidth; ++i) {
        move(y+1, x+i);
        if (i < filled) {
            addch(ACS_CKBOARD);  // ncurses 实心方块
        } else {
            addch(' ');
        }
    }

    attron(COLOR_PAIR(4));

    mvprintw(y+1, x+barWidth+1, "HP %d/%d", hp, maxHp);

    getch();
}
