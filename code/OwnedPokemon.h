#ifndef OWNEDPOKEMON_H
#define OWNEDPOKEMON_H

#include "PokemonEntity.h"

class OwnedPokemon : public PokemonEntity{
protected:
    int experience;
    int level;
public:
    OwnedPokemon(string name, string type, int level, int maxHP, vector<Move> moveSet);

    void displayStatus() const override;
    void attack() const override;

    void gainExp(int amount);
    void levelUp();
    bool canEvolve() const;
    void evolve();

    ~OwnedPokemon();
};

#endif 