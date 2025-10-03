#ifndef POKEMONENTITY_H
#define POKEMONENTITY_H

#include "Pokemon.h"
#include "PokemonDataBase.h"
#include "Move.h"
#include <vector>

using namespace std;

// Abstract class representing a Pokemon owned by a player or appearing in the game world
class PokemonEntity : public Pokemon {
protected:
    int level;          // The current level of the Pokemon
    int currentHP;      // The current HP (hit points) of the Pokemon
    int experience;     // The experience points of the Pokemon

public:
    // Default constructor
    PokemonEntity() = default;

    // Constructor for new Pokemon with starting experience = 0
    PokemonEntity(string name, string type, int level, int stage, int maxHP, vector<Move> moveSet);

    // Constructor for Pokemon with specific experience value (used when loading saved data)
    PokemonEntity(string name, string type, int level, int stage, int maxHP, int experience, vector<Move> moveSet);

    // Pure virtual method: Pokemon attacks a target with a move
    virtual void attack(PokemonEntity* target, Move move) = 0;

    // Pure virtual method: Pokemon receives damage
    virtual void takeDamage(int damage) = 0;

    // Pure virtual method: Returns a clone (deep copy) of the PokemonEntity
    virtual PokemonEntity* clone() = 0;

    // Returns true if the Pokemon can evolve based on its current level/stage
    bool canEvolve();

    // Level up the Pokemon (increase level, reset experience, etc.)
    void levelUp();

    // Returns true if the Pokemon can level up (based on experience threshold)
    bool canLevelUp();

    // Ensures currentHP does not exceed maxHP or fall below 0
    void clampHP();

    // Heal the Pokemon by a given amount (not exceeding maxHP)
    void heal(int amount);

    // Add experience points to the Pokemon
    void addExp(int exp);

    // Returns true if the Pokemon has fainted (HP <= 0)
    bool isFainted();

    // Get the current HP of the Pokemon
    int getCurrentHP();

    // Get the current experience points
    int getExp();

    // Get the current level
    int getLevel();

    // Set the current HP to a given value (used for healing or resets)
    void resetHP(int HP);

    // Virtual destructor
    virtual ~PokemonEntity();
};

#endif