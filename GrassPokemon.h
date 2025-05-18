#ifndef GRASSPOKEMON_H
#define GRASSPOKEMON_H

#include"PokemonEntity.h"

class GrassPokemon : public PokemonEntity{
    public:
    GrassPokemon();
    GrassPokemon(std::string name,
                std::string type,
                int level,
                int stage,
                int maxHP,
                std::vector<Move> moveSet);

    void attack(PokemonEntity* target) override;
    GrassPokemon* clone() override;

    ~GrassPokemon();
};

#endif