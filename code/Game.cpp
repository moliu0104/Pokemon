#include"Game.h"

// Initialize the game with starter Pokémon, items, and money
void Game::initGame(){
    // Get a random chain of Grass-type Pokémon
    vector<Pokemon> grassPokemon = allPokemon.getRandomPokemonByType("Grass");
    // If there are Grass Pokémon available
    if(grassPokemon.size() > 0){
        // Create a new GrassPokemonEntity at level 1 (starter)
        PokemonEntity* grassPokemonEntity = new GrassPokemon(
            grassPokemon[0].getName(),
            grassPokemon[0].getType(),
            1,
            grassPokemon[0].getStage(),
            grassPokemon[0].getMaxHP(),
            grassPokemon[0].getMoveSet()
        );
        // Add starter Pokémon to player's bag
        player.addPokemonToBag(grassPokemonEntity);
    }

    // Give player 3 potions
    player.getBag().addPotion(3);
    // Give player 3 Pokémon Balls
    player.getBag().addBalls(3);
    // Give player 200 gold
    player.addMoney(200);
}

// Save the game to a file
void Game::saveGame(const string& filename) {
    ofstream fout(filename); // Open file to write
    fout << "MONEY " << player.getMoneyAmount() << endl; // Save money
    fout << "POTION " << player.getBag().getPotionAmount() << endl; // Save potions
    fout << "BALL " << player.getBag().getBallAmount() << endl; // Save balls
    // Save all Pokémon in player's bag
    for(int i = 0; i < player.getBag().getPokemonAmount(); ++i) {
        PokemonEntity* p = player.getBag().getPokemonAt(i);
        fout << "POKEMON "
             << p->getName() << " "
             << p->getType() << " "
             << p->getLevel() << " "
             << p->getStage() << " "
             << p->getMaxHP() << " "
             << p->getExp() << " "
             << "\n";
    }
    fout.close(); // Close the file
    // Show a message for successful save
    Menu::drawMenu({"Exit"},{"Save Game Successfully!"},10,3,3,3);
}

// Load the game from a file
bool Game::loadGame(const string& filename) {
    ifstream fin(filename); // Open file to read
    if(!fin.is_open()) return false; // Fail if can't open

    string line;
    int pokemon_count = 0;

    // Read each line in the save file
    while(getline(fin, line)) {
        stringstream ss(line);
        string key;
        ss >> key;
        if(key == "MONEY") {
            int money;
            ss >> money;
            player.setMoneyAmount(money); // Set player's money
        }
        else if(key == "POTION") {
            int potions;
            ss >> potions;
            player.getBag().setPotionsAmount(potions); // Set potions
        }
        else if(key == "BALL") {
            int balls;
            ss >> balls;
            player.getBag().setBallAmount(balls); // Set balls
        }
        else if(key == "POKEMON") {
            string name, type;
            int level, exp, hp, maxhp, stage;
            // Read Pokémon data from file
            ss >> name >> type >> level >> stage >> maxhp >> exp;
            // Get moveset for the Pokémon from the database
            vector<Move> moves = allPokemon.findPokemonByName(name)->getMoveSet();
            
            // Create new PokémonEntity depending on its type and add to bag
            if(type == "Water"){
                PokemonEntity* poke = new WaterPokemon(name, type, level, stage, maxhp, exp, moves);
                player.getBag().addPokemon(poke);
            }else if(type == "Fire"){
                PokemonEntity* poke = new FirePokemon(name, type, level, stage, maxhp, exp, moves);
                player.getBag().addPokemon(poke);
            }else if(type == "Grass"){
                PokemonEntity* poke = new GrassPokemon(name, type, level, stage, maxhp, exp, moves);
                player.getBag().addPokemon(poke);
            }else{
                return false; // Unknown type, fail loading
            }
        }else{
            return false;
        }
    }
    fin.close(); // Close file
    return true; // Loaded successfully
}