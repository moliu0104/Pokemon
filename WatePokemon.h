#ifndef WATERPOKEMON_H
#define WATERPOKEMON_H

#include"PokemonEntity.h"

class WaterPokemon : public PokemonEntity{
    public:
    WaterPokemon(std::string name,
                int level,
                int stage,
                int maxHP,
                std::vector<Move> moveSet);

    void attack(PokemonEntity* target) override;
    void displayStatus() const override;
};


#endif