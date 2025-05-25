#include "Pokemon.h"

// Constructor: Initializes a Pokemon with given properties
Pokemon::Pokemon(string name, string type, int stage, int maxHP, vector<Move> moveSet)
    : name(name), type(type), stage(stage), maxHP(maxHP), moveSet(moveSet) {}

// Returns the name of the Pokemon
string Pokemon::getName() { 
    return name;
}

// Returns the type (e.g., Fire, Water, Grass) of the Pokemon
string Pokemon::getType() {
    return type;
}

// Returns the evolution stage of the Pokemon
int Pokemon::getStage() {
    return stage;
}

// Returns the maximum HP value for the Pokemon
int Pokemon::getMaxHP() {
    return maxHP;
}

// Returns the list of moves available to the Pokemon
vector<Move> Pokemon::getMoveSet() {
    return moveSet;
}

// Sets the evolution stage of the Pokemon
void Pokemon::setStage(int stage) {
    this->stage = stage;
}

// Sets the type of the Pokemon
void Pokemon::setType(string type) {
    this->type = type;
}

// Sets the name of the Pokemon
void Pokemon::setName(string name) {
    this->name = name;
}

// Sets the maximum HP of the Pokemon
void Pokemon::setMaxHP(int maxHP) {
    this->maxHP = maxHP;
}

// Adds a new move to the Pokemon's move set
void Pokemon::addMove(Move move) {
    moveSet.push_back(move);
}

// Destructor: Used for cleanup if needed (currently does nothing)
Pokemon::~Pokemon() {}