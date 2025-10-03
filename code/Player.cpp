#include "Player.h"
#include "Bag.h"

// Constructor: Initializes the player with 0 money and allocates a new Bag.
Player::Player(){
    moneyAmount = 0;       // Player starts with zero money.
    bag = new Bag;         // Dynamically allocate a new Bag for the player.
}

// Returns a reference to the player's Bag.
// Allows access to Pokémon and items inside the bag.
Bag& Player::getBag(){
    return *bag;
}

// Returns the current amount of money the player has.
int Player::getMoneyAmount(){
    return moneyAmount;
}

// Sets the player's money amount to a specified value.
void Player::setMoneyAmount(int amount){
    moneyAmount = amount;
}

// Increases the player's money by the specified amount.
void Player::addMoney(int amount){
    moneyAmount += amount;
}

// Decreases the player's money by the specified amount.
void Player::spendMoney(int amount){
    moneyAmount -= amount;
}

// Adds a Pokémon to the player's bag.
// Uses the Bag class's addPokemon method.
void Player::addPokemonToBag(PokemonEntity* pokemon){
    bag->addPokemon(pokemon);
}

// Returns a pointer to the currently active Pokémon in the bag.
PokemonEntity* Player::getActivePokemon(){
    return bag->getActive();
}

// Destructor: Cleans up the dynamically allocated Bag object.
Player::~Player(){
    delete bag; // Free the memory to prevent leaks.
}

// Global Player object definition (declared as extern in Player.h).
Player player;