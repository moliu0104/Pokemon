#include "Move.h"

// Constructor: initializes the move's name, type, and damage
Move::Move(string name, string type, int damage)
    : name(name), type(type), damage(damage) {}

// Returns the name of the move
string Move::getName() {
    return name;
}

// Returns the type of the move (e.g., Fire, Water)
string Move::getType() {
    return type;
}

// Returns the damage value of the move
int Move::getDamage() {
    return damage;
}