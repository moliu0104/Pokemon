#include "PokemonEntity.h"
#include <iostream>
#include <cstdlib>

// Constructor for new PokemonEntity (player or wild), sets level, maxHP, starts with 0 experience and full HP
PokemonEntity::PokemonEntity(string name, string type, int level, int stage, int maxHP, vector<Move> moveSet)
    : Pokemon(name, type, stage, maxHP, moveSet), currentHP(maxHP), level(level), experience(0) {}

// Constructor for loading a PokemonEntity with a specified experience value (e.g., from a save file)
PokemonEntity::PokemonEntity(string name, string type, int level, int stage, int maxHP, int experience, vector<Move> moveSet)
    : Pokemon(name, type, stage, maxHP, moveSet), currentHP(maxHP), level(level), experience(experience) {}

// Check if this Pokemon can evolve (e.g., Stage 1 evolves at level >= 10, Stage 2 at level >= 20)
bool PokemonEntity::canEvolve() {
    if (stage == 1 && level >= 10) {
        return true;
    } else if (stage == 2 && level >= 20) {
        return true;
    } else {
        return false;
    }
}

// Check if this Pokemon can level up (if experience >= 100)
bool PokemonEntity::canLevelUp() {
    return experience >= 100;
}

// Level up this Pokemon: increase level by 1 for every 100 experience points, deduct used exp
void PokemonEntity::levelUp() {
    int loop = experience / 100;
    for (int i = 0; i < loop; i++) {
        level++;
        experience -= 100;
    }
}

// Returns true if Pokemon's HP <= 0 (fainted), false otherwise
bool PokemonEntity::isFainted() {
    return currentHP <= 0;
}

// Ensure currentHP stays within [0, maxHP]
void PokemonEntity::clampHP() {
    if (currentHP < 0) currentHP = 0;
    if (currentHP > maxHP) currentHP = maxHP;
}

// Heal the Pokemon by a specified amount, up to maxHP
void PokemonEntity::heal(int amount) {
    currentHP += amount;
    clampHP();
}

// Add experience points (for battle rewards, etc.)
void PokemonEntity::addExp(int exp) {
    experience += exp;
}

// Getter: return current HP
int PokemonEntity::getCurrentHP() { return currentHP; }

// Getter: return current level
int PokemonEntity::getLevel() { return level; }

// Getter: return current experience points
int PokemonEntity::getExp() { return experience; }

// Reset current HP to a specified value (for healing, or full restore after fainting)
void PokemonEntity::resetHP(int HP) { currentHP = HP; }

// Destructor (nothing special to clean up, but needed for virtual base class)
PokemonEntity::~PokemonEntity() {}