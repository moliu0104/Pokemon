#include"ExploreSystem.h"

// Constructor: set wildPokemon pointer to nullptr
ExploreSystem::ExploreSystem(){
    wildPokemon = nullptr;
}

// Main function to run the exploration system
void ExploreSystem::run(){
    ExploreSystem self; // Create an instance for internal use

    // Title for the exploration menu
    vector<string> adventureTitle = {"========= Expedition Routes =========="};
    // Options for different maps or exit
    vector<string> adventureOptions = {
        "Verdale Grove",
        "Abyria Reef",
        "Emberpeak Island",
        "Exit"
    };

    int choice;       // User menu selection
    bool running = true; // Control the main loop

    while(running){
        clear(); // Clear the ncurses window
        // Show the menu and get the user's choice
        choice = Menu::drawMenu(adventureOptions, adventureTitle);

        bool ifFight = false; // Track if a battle should start

        // Handle menu selection based on the user's choice
        switch(MapOptions(choice)){
            case MapOptions::GrassMap:
                self.encounterWildPokemon("Grass");      // Find a wild Grass-type Pokémon
                ifFight = self.tryExploring();           // Let user choose to battle or run
                break;
            case MapOptions::WaterMap:
                self.encounterWildPokemon("Water");      // Find a wild Water-type Pokémon
                ifFight = self.tryExploring();
                break;
            case MapOptions::FireMap:
                self.encounterWildPokemon("Fire");       // Find a wild Fire-type Pokémon
                ifFight = self.tryExploring();
                break;
            case MapOptions::Exit:
                running = false; // End the loop and exit
        }

        // If player chose to fight, start a battle
        if(ifFight){
            BattleSystem battleSystem(self.getWildPokemon());
            battleSystem.run();
        }
    }
}

// Simulate exploring and show wild Pokémon encounter
bool ExploreSystem::tryExploring(){
    clear();                        // Clear the window
    mvprintw(3, 5, "Exploring..."); // Show "Exploring..." text
    refresh();                      // Refresh the screen

    int times = util::randInRange(2,4); // Random delay time between 2 and 4 seconds

    // Wait for 'times' seconds to simulate searching
    this_thread::sleep_for(std::chrono::seconds(times));

    int highlight; // Store menu selection

    // Display the wild Pokémon's name and level in the menu title
    vector<string> title = {
        "A Pokémon appeared!",
        "-> Name: " + wildPokemon->getName() + " | Level: " + to_string(wildPokemon->getLevel())
    };

    // Show menu: "Enter Battle" or "Run Away"
    highlight = Menu::drawMenu(
        {"Enter Battel","Run Away (Return to Map Menu)" },
        title, 7, 7, 3, 7);

    // Return true if player chose to fight (option 0)
    return !highlight;
}

// Generate a wild Pokémon of the given type, with random stage and level
void ExploreSystem::encounterWildPokemon(string type){
    // Get a chain (evolution line) of Pokémon for this type
    vector<Pokemon> pokemonChain = allPokemon.getRandomPokemonByType(type);

    int stageChance = util::randInRange(0,99); // Random value for determining evolution stage
    int stage; // Evolution stage

    // Assign stage based on probability
    if (stageChance < 10)      stage = 3;
    else if (stageChance < 30) stage = 2;
    else                       stage = 1;

    // Calculate random level based on stage
    int level = stage * 10 - util::randInRange(1,10);
    if(level <= 0) level = 1; // Ensure level is at least 1

    // Pick the correct Pokémon for the chosen stage
    Pokemon wildSpecise = pokemonChain[stage-1];

    // Delete old wild Pokémon if exists
    if (wildPokemon) { delete wildPokemon; wildPokemon = nullptr; }

    // Create a new Pokémon entity based on its type
    if(type == "Fire"){
        wildPokemon = new FirePokemon(
            wildSpecise.getName(),
            wildSpecise.getType(),
            level,
            wildSpecise.getStage(),
            wildSpecise.getMaxHP(),
            wildSpecise.getMoveSet()
        );
    }else if (type == "Grass"){
        wildPokemon = new GrassPokemon(
            wildSpecise.getName(),
            wildSpecise.getType(),
            level,
            wildSpecise.getStage(),
            wildSpecise.getMaxHP(),
            wildSpecise.getMoveSet()
        );
    }else{
        wildPokemon = new WaterPokemon(
            wildSpecise.getName(),
            wildSpecise.getType(),
            level,
            wildSpecise.getStage(),
            wildSpecise.getMaxHP(),
            wildSpecise.getMoveSet()
        );
    }
}

// Return pointer to the current wild Pokémon
PokemonEntity* ExploreSystem::getWildPokemon(){
    return wildPokemon;
}

// Destructor: delete wildPokemon if it exists
ExploreSystem::~ExploreSystem(){
    delete wildPokemon;
}