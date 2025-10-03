#include "Menu.h"

// Initialize color pairs and custom colors for ncurses interface.
void Menu::initColors(){
    // If terminal does not support color or color changing, exit.
    if (!has_colors() || !can_change_color())
        return;     

    start_color(); // Enable color functionality in ncurses.

    // Define custom RGB values for special colors.
    init_color(COLOR_CYAN,  494, 716, 886);     // Custom cyan
    init_color(COLOR_YELLOW, 977, 976, 444);    // Custom yellow
    init_color(COLOR_RED,    600, 100, 50);     // Custom red
   
    // Create color pairs (foreground, background) for different UI elements.
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // Highlighted option
    init_pair(2, COLOR_WHITE, COLOR_BLACK);  // Normal text
    init_pair(3, COLOR_RED,   COLOR_BLACK);  // Enemy HP bar
    init_pair(4, COLOR_CYAN,  COLOR_BLACK);  // Player HP bar
    init_pair(5, COLOR_YELLOW, COLOR_BLACK); // Log messages
}

// Draw an interactive menu with options and title, return the selected index.
int Menu::drawMenu(
    const vector<string> options,  // List of selectable options.
    const vector<string> title,    // Menu title, possibly multi-line.
    int options_y, int options_x,  // Options display coordinates.
    int title_y, int title_x       // Title display coordinates.
){
    initColors(); // Ensure colors are set.

    int highlight = 0; // Index of currently highlighted option.
    int input;         // Variable to capture user input key.

    // Main menu loop: Draw and handle user navigation.
    while(1){
        bkgd(COLOR_PAIR(2)); // Set background color for the whole window.
        clear();             // Clear the screen.
        refresh();           // Refresh the screen to apply changes.

        // Draw the menu title with normal text color.
        attron(COLOR_PAIR(2));
        for(int i = 0; i < title.size(); i++){
            mvprintw(title_y + i, title_x, "%s", title[i].c_str());
        }
        attroff(COLOR_PAIR(2));

        // Draw each menu option, highlighting the current selection.
        for(int i = 0; i < options.size(); i++){
            if(i == highlight){
                attron(COLOR_PAIR(1)); // Highlighted option.
                mvprintw(options_y + i, options_x, "> %s", options[i].c_str());
                attroff(COLOR_PAIR(1));
            }else{
                attron(COLOR_PAIR(2)); // Normal option.
                mvprintw(options_y + i, options_x, "  %s", options[i].c_str());
                attroff(COLOR_PAIR(2));
            }
        }

        // Capture user keyboard input (arrow keys or enter).
        input = getch();

        // Navigation logic for menu selection.
        switch (input)
        {
        case KEY_UP:
            // Move highlight up, wrap around if needed.
            highlight = (highlight - 1 + options.size()) % options.size();
            // Skip newline placeholder (if any).
            if(options[highlight] == "\n"){
                highlight--;
            }
            break;
        
        case KEY_DOWN:
            // Move highlight down, wrap around if needed.
            highlight = (highlight + 1) % options.size();
            // Skip newline placeholder (if any).
            if(options[highlight] == "\n"){
                highlight++;
            }
            break;
        
        case '\n':
            // User pressed Enter: return the currently selected index.
            return highlight;
        }
    }
}