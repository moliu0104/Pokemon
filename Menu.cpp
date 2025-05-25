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


int Menu::drawMenu(const vector<string> options, const vector<string> title, int options_y, int options_x, int title_y, int title_x){
    initColors();
    // Set backgroud and character color

    int highlight = 0;
    int input;

    while(1){
        bkgd(COLOR_PAIR(2));
        clear();
        refresh();

        attron(COLOR_PAIR(2));
        for(int i = 0; i < title.size(); i++){
            mvprintw(title_y + i,title_x,"%s",title[i].c_str());
        }
        attroff(COLOR_PAIR(2));

        for(int i = 0; i < options.size(); i++){
            if(i == highlight){
                attron(COLOR_PAIR(1));
                mvprintw(options_y+i, options_x, "> %s", options[i].c_str());
                attroff(COLOR_PAIR(1));
            }else{
                attron(COLOR_PAIR(2));
                mvprintw(options_y+i, options_x, "  %s", options[i].c_str());
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



