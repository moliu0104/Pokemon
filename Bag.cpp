#include "Bag.h"

Bag::Bag() {
    bagSize = 6;
    count = 0;
    pokemons = new PokemonEntity*[bagSize];
    for (int i = 0; i < bagSize; ++i)
        pokemons[i] = nullptr;
}

bool Bag::addPokemon(PokemonEntity* p) {
    if (count < 0 || count >= bagSize || !p) return false;
    pokemons[count++] = p->clone();
    return true;
}

bool Bag::switchActive(int index) {
    if (index < 0 || index >= count) return false;
    std::swap(pokemons[0], pokemons[index]);
    return true;
}

PokemonEntity* Bag::getActive() {
    return (count > 0 ? pokemons[0] : nullptr);
}

Bag::~Bag() {
    for (int i = 0; i < count; ++i)
        delete pokemons[i];
    delete[] pokemons;
}