#ifndef WILDPOKEMON_H
#define WILDPOKEMON_H

#include<cstdlib>
#include<ctime>
#include"PokemonEntity.h"
#include"PokemonDataBase.h"

class WildPokemon : public PokemonEntity{
public:
    WildPokemon() = default;
    WildPokemon(string name, string type, int level,int stage, int maxHP, vector<Move> moveSet);

    void displayStatus() const override;
    void attack() const override;
    


    ~WildPokemon();
};

#endif