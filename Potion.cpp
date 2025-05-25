#include"Potion.h"
Potion::Potion(int heal){
    healAmount = heal;
    price = 50;
}

bool Potion::use(PokemonEntity* pokemon){
        pokemon->heal(healAmount);
        return true;
}

int Potion::getPrice(){
    return price;
}

Potion::~Potion(){}