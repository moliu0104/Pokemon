#include "StoreSystem.h"

// Constructor for StoreSystem. Initializes the menu highlight to 0.
StoreSystem::StoreSystem() {
    highlight = 0;
}

// Main loop to run the store interaction.
void StoreSystem::run() {
    Potion potion;                 // Create a default Potion instance for price checking.
    PokemonBall ball;              // Create a default PokemonBall instance for price checking.
    bool running = true;           // Control flag for the store loop.

    while (running) {
        int choice = drawStore();  // Draws the store UI and gets the user's choice.

        switch (choice) {
            case 0: // User chooses to buy a Potion.
                if (player.getMoneyAmount() < potion.getPrice()) {
                    // Not enough money to buy Potion.
                    drawPurchaseFailed(choice);
                } else {
                    // Deduct money and add a Potion to player's bag.
                    player.spendMoney(potion.getPrice());
                    player.getBag().addPotion(1);
                }
                break;

            case 1: // User chooses to buy a Pokemon Ball.
                if (player.getMoneyAmount() < ball.getPrice()) {
                    // Not enough money to buy Pokemon Ball.
                    drawPurchaseFailed(choice);
                } else {
                    // Deduct money and add a Ball to player's bag.
                    player.getBag().addBalls(1);
                    player.spendMoney(ball.getPrice());
                }
                break;

            default:
                // Exit the store.
                running = false;
                break;
        }
    }
}

// Draws the store menu, displays player's inventory and gold, returns user's choice.
int StoreSystem::drawStore() {
    int input;                      // Stores user keyboard input.
    Potion potion;                  // Potion item for displaying price.
    PokemonBall ball;               // Ball item for displaying price.
    vector<string> playerOwned;     // List to hold player's status info.
    // Store options for the menu.
    vector<string> options = {string("Potion:\t\t")+"Price: "+ to_string(potion.getPrice()) + " G",
                             string("Pokémon Ball:\t")+"Price: " + to_string(ball.getPrice()) + " G",
                             string("\n"),
                             string("Exit")};
    string text;                    // Temporary string for UI text.

    while (1) {
        clear();   // Clear the ncurses screen for fresh redraw.

        // Show player's current gold.
        text = string("You have:\tGold: ") + to_string(player.getMoneyAmount());
        playerOwned.push_back(text);

        // Show player's inventory of potions and Poké Balls.
        text = string("You Owned:\tPotion: x") + to_string(player.getBag().getPotionAmount()) +
               "\tPokémon Ball: x" + to_string(player.getBag().getBallAmount());
        playerOwned.push_back(text);

        // Draw store title and player status lines.
        attron(COLOR_PAIR(2));
        mvprintw(1, 3, "%s", "================= POKEMON STORE =================");
        for (int i = 0; i < playerOwned.size(); i++) {
            mvprintw(2 + i, 5, "%s", playerOwned[i].c_str());
        }
        mvprintw(4, 3, "%s", "-------------------------------------------------");
        attroff(COLOR_PAIR(2));

        playerOwned.clear(); // Reset status info for next redraw.

        // Draw menu options, highlight the selected option.
        for (int i = 0; i < options.size(); i++) {
            if (i == highlight) {
                attron(COLOR_PAIR(1));
                mvprintw(5 + i, 5, "> %s", options[i].c_str());
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                mvprintw(5 + i, 5, "  %s", options[i].c_str());
                attroff(COLOR_PAIR(2));
            }
        }

        input = getch();  // Wait for user input.

        switch (input) {
        case KEY_UP:
            // Move selection up, skipping empty options.
            highlight = (highlight - 1 + options.size()) % options.size();
            if (options[highlight] == "\n") {
                highlight--;
            }
            break;

        case KEY_DOWN:
            // Move selection down, skipping empty options.
            highlight = (highlight + 1) % options.size();
            if (options[highlight] == "\n") {
                highlight++;
            }
            break;

        case '\n':
            // User presses Enter, return current highlighted choice.
            return highlight;
        }
    }
}

// Draws a failure screen when the player can't afford an item.
void StoreSystem::drawPurchaseFailed(int choice) {
    clear(); // Clear the screen.

    string text;
    attron(COLOR_PAIR(2));
    mvprintw(2, 3, "%s", "!!! NOT ENOUGH GOLD !!!"); // Display error message.

    text = string("You only have ") + to_string(player.getMoneyAmount()) + " G,";
    mvprintw(4, 5, "%s", text.c_str());

    // Show the cost of the item that failed to be purchased.
    if (choice == 0) {
        Potion p;
        text = string("But that costs ") + to_string(p.getPrice()) + "G.";
        mvprintw(5, 5, "%s", text.c_str());
    } else if (choice == 1) {
        PokemonBall b;
        text = string("But that costs ") + to_string(b.getPrice()) + "G.";
        mvprintw(5, 5, "%s", text.c_str());
    }

    attroff(COLOR_PAIR(2));

    // Prompt the user to continue.
    attron(COLOR_PAIR(1));
    mvprintw(7, 5, "> %s", "Continue");
    attroff(COLOR_PAIR(1));

    getch(); // Wait for user to press a key.
}

// Destructor for StoreSystem (does nothing in this implementation).
StoreSystem::~StoreSystem() {}