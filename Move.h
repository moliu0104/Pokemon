#ifndef MOVE_H
#define MOVE_H

#include <string>
using namespace std;

// The Move class represents a Pokémon move (attack or skill).
class Move {
private:
    string name;    // The name of the move (e.g., "Tackle", "Ember")
    string type;    // The elemental type of the move (e.g., "Fire", "Water")
    int damage;     // The damage value this move can inflict

public:
    // Constructor: Initializes a move with a name, type, and damage value
    Move(string name, string type, int damage);

    // Getter for the move's name
    string getName();

    // Getter for the move's type
    string getType();

    // Getter for the move's damage
    int getDamage();

    // Setter for the move's name
    void setName(string name);

    // Setter for the move's type
    void setType(string type);
};

#endif // MOVE_H