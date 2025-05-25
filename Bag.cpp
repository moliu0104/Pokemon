#include "Bag.h"

// Constructor: Initializes variables and allocates space for Pokémon array.
Bag::Bag() {
    bagSizePokemon = 6;                  // The maximum number of Pokémon that can be stored in the bag is 6.
    countPokemon = 0;                    // Initialize the number of Pokémon currently in the bag to 0.
    activeIndex = 0;                     // By default, the first Pokémon in the bag will be the active one.
    pokemons = new PokemonEntity*[bagSizePokemon]; // Allocate memory for the Pokémon pointer array.

    // Initialize each slot in the Pokémon array to nullptr (empty).
    for (int i = 0; i < bagSizePokemon; i++)
        pokemons[i] = nullptr;
}

// Adds a Pokémon to the bag. Returns true if successful, false if the bag is full.
bool Bag::addPokemon(PokemonEntity* p) {
    if (countPokemon >= bagSizePokemon) return false; // If bag is already full, do not add.
    pokemons[countPokemon++] = p->clone();            // Clone the Pokémon and store the pointer, increment count.
    return true;                                      // Successfully added.
}

// Changes the active Pokémon to the Pokémon at the specified index.
// Returns true if the index is valid, otherwise returns false.
bool Bag::switchActive(int index) {
    if (index < 0 || index >= countPokemon) return false; // Check for invalid index.
    activeIndex = index;                                  // Set the new active Pokémon index.
    return true;
}

void Bag::clear() {
    // Delete each Pokemon pointer in the bag to avoid memory leaks
    for (int i = 0; i < countPokemon; ++i) {
        delete pokemons[i];
        pokemons[i] = nullptr;
    }
    countPokemon = 0;       // Reset count to zero
    activeIndex = 0; // Reset active Pokemon index
    potionsAmount = 0; // Reset Potion amount to zero
    ballsAmount = 0; // Reset Ball amount to zero
}

// Returns a pointer to the currently active Pokémon.
// If the bag is empty or index is invalid, returns nullptr.
PokemonEntity* Bag::getActive() {
    return (countPokemon > activeIndex ? pokemons[activeIndex] : nullptr);
}

// Returns a pointer to the Pokémon at index i.
// If the index is invalid, returns nullptr.
PokemonEntity* Bag::getPokemonAt(int i){
    return (countPokemon > i ? pokemons[i] : nullptr);
}

// Returns the index of the currently active Pokémon.
int Bag::getAcitiveIndex(){
    return activeIndex;
}

// Returns the current number of Pokémon in the bag.
int Bag::getPokemonAmount(){
    return countPokemon;
}

// Returns the maximum capacity of the bag for Pokémon.
int Bag::getPokemonCapacity(){
    return bagSizePokemon;
}

// Heals all Pokémon in the bag to their maximum HP.
void Bag::healAllPokemon(){
    for(int i =0; i < countPokemon; i++){
        pokemons[i]->resetHP(pokemons[i]->getMaxHP()); // Set current HP to max HP for each Pokémon.
    }
}

// Evolves the Pokémon at index i if possible.
// Replaces the old Pokémon object with the evolved version.
// Shows a congratulatory menu.
// Returns true if evolution happened, false otherwise.
bool Bag::evolve(int i){
    if (i < 0 || i >= countPokemon) return false; // Check for invalid index.

    if(pokemons[i]->getStage() >= 3) return false;

    vector<string> evolutionName; // Store old and new Pokémon names for display.
    vector<Pokemon> db = allPokemon.findPokemonByType(pokemons[i]->getType()); // Get Pokémon evolution chain from database.
    int level = pokemons[i]->getLevel(); // Store current Pokémon level.
    int exp = pokemons[i]->getExp();     // Store current Pokémon experience.
    int index = -1;                      // Will hold the position of the current Pokémon in the evolution chain.

    // Find the index of the current Pokémon in the evolution chain.
    for(int j =0; j < db.size(); j++){
        if(pokemons[i]->getName() == db.at(j).getName()){
            index = j;
            break;
        }
    }

    evolutionName.push_back(pokemons[i]->getName()); // Save original name.

    // If the Pokémon is Fire type, evolve to next Fire Pokémon.
    if(pokemons[i]->getType() == "Fire"){
        delete pokemons[i]; // Delete old object to avoid memory leak.
        pokemons[i] = new FirePokemon(
            db[index+1].getName(),
            db[index+1].getType(),
            level,
            db[index+1].getStage(),
            db[index+1].getMaxHP(),
            exp,
            db[index+1].getMoveSet()
        );
        evolutionName.push_back(pokemons[i]->getName()); // Save new name.
        // Show congratulation message.
        Menu::drawMenu(
            {"Exit"},
            {"  ** CONGRATULATIONS! **", 
             string("Your ") + evolutionName[0] + " evolved into " + evolutionName[1] + "!",
             "View it in your bag" }, 10,20,5,20
        );
        return true;
    }
    // If Water type, evolve to next Water Pokémon.
    else if(pokemons[i]->getType() == "Water"){
        delete pokemons[i];
        pokemons[i] = new WaterPokemon(
            db[index+1].getName(),
            db[index+1].getType(),
            level,
            db[index+1].getStage(),
            db[index+1].getMaxHP(),
            exp,
            db[index+1].getMoveSet()
        );
        evolutionName.push_back(pokemons[i]->getName());
        Menu::drawMenu(
            {"Exit"},
            {"  ** CONGRATULATIONS! **", 
             string("Your ") + evolutionName[0] + " evolved into " + evolutionName[1] + "!",
             "View it in your bag" }, 10,20,5,20
        );
        return true;
    }
    // If Grass type, evolve to next Grass Pokémon.
    else if(pokemons[i]->getType() == "Grass"){
        delete pokemons[i];
        pokemons[i] = new GrassPokemon(
            db[index+1].getName(),
            db[index+1].getType(),
            level,
            db[index+1].getStage(),
            db[index+1].getMaxHP(),
            exp,
            db[index+1].getMoveSet()
        );
        evolutionName.push_back(pokemons[i]->getName());
        Menu::drawMenu(
            {"Exit"},
            {"  ** CONGRATULATIONS! **", 
             string("Your ") + evolutionName[0] + " evolved into " + evolutionName[1] + "!",
             "View it in your bag" }, 10,20,5,20
        );
        return true;
    }
    // If not a recognized type or cannot evolve, do nothing.
    else{
        return false;
    }
}

// Adds potions to the bag.
void Bag::addPotion(int amount){
    potionsAmount = potionsAmount + amount;
}

// Uses a potion on the currently active Pokémon. Returns false if out of potions.
bool Bag::usePotion(){
    if(potionsAmount <= 0) return false;        // Not enough potions to use.
    potions.use(pokemons[activeIndex]);         // Heal the active Pokémon.
    potionsAmount --;                           // Reduce potion count.
    return true;
}

// Returns the number of potions in the bag.
int Bag::getPotionAmount(){
    return potionsAmount;
}

// Sets the potion amount directly (useful when loading from a saved file).
void Bag::setPotionsAmount(int amount){
    potionsAmount = amount;
}

// Adds Pokéballs to the bag.
void Bag::addBalls(int amount){
    ballsAmount = ballsAmount + amount;
}

// Uses a Pokéball to try and capture a Pokémon. Returns true if capture is successful.
bool Bag::useBalls(PokemonEntity* target){
    bool isCapture;
    isCapture = balls.use(target); // Use a Pokéball on the target Pokémon.
    ballsAmount --;                // Reduce ball count.
    return isCapture;
}

// Returns the number of Pokéballs in the bag.
int Bag::getBallAmount(){
    return ballsAmount;
}

// Sets the number of Pokéballs directly (for loading state).
void Bag::setBallAmount(int amount){
    ballsAmount = amount;
}

// Destructor: Clean up all allocated Pokémon objects and the array itself.
Bag::~Bag() {
    // Delete each Pokémon pointer in the array to prevent memory leaks.
    for(int i=0; i<countPokemon; i++) {
        delete pokemons[i];
        pokemons[i] = nullptr;
    }
    delete[] pokemons;      // Delete the array of pointers.
    pokemons = nullptr;
}