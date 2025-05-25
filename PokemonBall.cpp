#include"PokemonBall.h"
#include "Bag.h"      // 必须有这句
#include "Player.h"

PokemonBall::PokemonBall(){
    baseRate = 0.8;
    price = 100;
}

bool PokemonBall::use(PokemonEntity* target){
    double hpRatio = double(target->getCurrentHP()) / target->getMaxHP();
        if (hpRatio < 0) hpRatio = 0;

    double catchChance = baseRate * (1.0 - hpRatio);

    double roll = double(std::rand() % 1000) / 1000.0; 
    bool success = (roll < catchChance);

    if (success) {
        player.getBag().addPokemon(target);
    }

    return success;
}

int PokemonBall::getPrice(){
    return price;
}
