#ifndef GRASSPOKEMON_H
#define GRASSPOKEMON_H

#include"PokemonEntity.h"

class GrassPokemon : public PokemonEntity{
    public:
    GrassPokemon();
    GrassPokemon(std::string name,std::string type,int level,int stage,int maxHP,std::vector<Move> moveSet);
    GrassPokemon(std::string name,std::string type,int level,int stage,int maxHP,int experience,std::vector<Move> moveSet);

    void attack(PokemonEntity* target,Move move) override;
    void takeDamage(int damage) override;
    GrassPokemon* clone() override;
    PokemonEntity* evolve() override;

    ~GrassPokemon();
};

#endif