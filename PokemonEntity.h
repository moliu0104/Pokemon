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
    string personality;

public:
    PokemonEntity() = default;
    PokemonEntity(string name, string type, int level,int stage, int maxHP, vector<Move> moveSet);

    virtual void displayStatus() const = 0;
    virtual void attack() const = 0;

    int getCurrentHP() const;
    int getLevel() const;
    string getPersonality() const;

    virtual ~PokemonEntity();
};

#endif