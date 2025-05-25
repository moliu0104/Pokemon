#ifndef POKEMON_H
#define POKEMON_H

#include <vector>
#include <string>
#include "Move.h"

using namespace std;

// The Pokemon class defines a basic template for all Pokemon species data.
// It is NOT a player-owned or wild Pokemon instance, but rather a database entry
// containing basic properties like name, type, stage, max HP, and available moves.
class Pokemon {
protected:
    string name;              // Name of the Pokemon (e.g., Pikachu)
    string type;              // Type of the Pokemon (e.g., Fire, Water)
    int stage;                // Evolution stage (e.g., 1 = base, 2 = evolved)
    int maxHP;                // Maximum HP value for this Pokemon species
    vector<Move> moveSet;     // List of moves that this Pokemon can use

public:
    // Default constructor
    Pokemon() = default;
    
    // Parameterized constructor
    Pokemon(string name, string type, int stage, int maxHP, vector<Move> moveSet);

    // Getters for each attribute
    string getName();
    string getType();
    int getStage();
    int getMaxHP();
    vector<Move> getMoveSet();

    // Setters for attributes (allow modifications if needed)
    void setName(string name);
    void setStage(int stage);
    void setType(string type);
    void setMaxHP(int maxHP);

    // Adds a move to the Pokemon's move set
    void addMove(Move move);

    // Destructor
    ~Pokemon();
};

#endif