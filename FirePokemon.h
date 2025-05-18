#ifndef FIREPOKEMON_H
#define FIREPOKEMON_H

#include"PokemonEntity.h"

class FirePokemon : public PokemonEntity{
    public:
    FirePokemon();
    FirePokemon(std::string name,
                std::string type,
                int level,
                int stage,
                int maxHP,
                std::vector<Move> moveSet);
    FirePokemon(std::string name,
                std::string type,
                int level,
                int stage,
                int maxHP,
                int experience,
                std::vector<Move> moveSet);

    void attack(PokemonEntity* target) override;
    FirePokemon* clone() override;

    ~FirePokemon();
};


#endif