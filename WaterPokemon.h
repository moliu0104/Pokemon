#ifndef WATERPOKEMON_H
#define WATERPOKEMON_H

#include"PokemonEntity.h"

class WaterPokemon : public PokemonEntity{
    public:
    WaterPokemon();
    WaterPokemon(std::string name,
                std::string type,
                int level,
                int stage,
                int maxHP,
                std::vector<Move> moveSet);
    WaterPokemon(std::string name,
                std::string type,
                int level,
                int stage,
                int maxHP,
                int experience,
                std::vector<Move> moveSet);

    void attack(PokemonEntity* target) override;
    WaterPokemon* clone() override;

    ~WaterPokemon();
};


#endif