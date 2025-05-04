#include"Menu.h"

int Menu::drawMenu(const vector<string> options, const vector<string> title, int options_y, int options_x, int title_y, int title_x, int title_color){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);



    // Set backgroud and character color
    if (has_colors()) {
        start_color();
        switch(title_color){
            case 1:
                init_pair(1, COLOR_YELLOW, COLOR_BLACK);
                break;
            case 2:
                init_pair(1, COLOR_WHITE, COLOR_BLACK);
                break;
        }
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
    }

    int highlight = 0;
    int input;

    while(1){
        clear();
        attron(COLOR_PAIR(1));
        for(int i = 0; i < title.size(); i++){
            mvprintw(title_y + i,title_x,title[i].c_str());
        }
        attroff(COLOR_PAIR(1));

        for(int i = 0; i < options.size(); i++){
            if(options[i] == "\n"){
                i++;
            }

            if(highlight == i){
                attron(A_REVERSE | COLOR_PAIR(2));
            }
            mvprintw(i + options_y, options_x, options[i].c_str());
            if(highlight == i){
                attroff(A_REVERSE | COLOR_PAIR(2));
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