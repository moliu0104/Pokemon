#ifndef FIREPOKEMON_H
#define FIREPOKEMON_H

#include"PokemonEntity.h"

class FirePokemon : public PokemonEntity{
    public:
    FirePokemon(std::string name,
                int level,
                int stage,
                int maxHP,
                std::vector<Move> moveSet);

    void attack(PokemonEntity* target) override;
    void displayStatus() const override;
};


#endif