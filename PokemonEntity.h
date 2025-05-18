#ifndef POKEMONENTITY_H
#define POKEMONENTITY_H

#include"Pokemon.h"
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

    virtual void attack(PokemonEntity* target) = 0;
    virtual PokemonEntity* clone() = 0;

    bool isFainted()  ;
    int getCurrentHP() ;
    int getLevel();

    virtual ~PokemonEntity();
};

#endif