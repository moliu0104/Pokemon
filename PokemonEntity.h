#ifndef POKEMONENTITY_H
#define POKEMONENTITY_H

#include"Pokemon.h"
#include"PokemonDataBase.h"
#include"Move.h"
#include<vector>

using namespace std;

class PokemonEntity : public Pokemon{
protected:
    int level;
    int currentHP;
    int experience;

public:
    PokemonEntity() = default;
    PokemonEntity(string name, string type, int level,int stage, int maxHP, vector<Move> moveSet);
    PokemonEntity(string name, string type, int level,int stage, int maxHP, int experience, vector<Move> moveSet);

    virtual void attack(PokemonEntity* target,Move move) = 0;
    virtual void takeDamage(int damage) = 0;
    virtual PokemonEntity* clone() = 0;
    virtual PokemonEntity* evolve() = 0;
    
    bool canEvolve();
    void levelUp();
    bool canLevelUp();
    void clampHP();
    void heal(int amount);
    void addExp(int exp);
    bool isFainted()  ;
    int getCurrentHP() ;
    int getExp();
    int getLevel();


    void resetHP(int HP);

    virtual ~PokemonEntity();
};

#endif