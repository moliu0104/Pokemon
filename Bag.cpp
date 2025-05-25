#include "Bag.h"

Bag::Bag() {
    bagSizePokemon = 6;
    countPokemon = 0;
    activeIndex = 0;
    pokemons = new PokemonEntity*[bagSizePokemon];
    for (int i = 0; i < bagSizePokemon; i++)
        pokemons[i] = nullptr;
}

bool Bag::addPokemon(PokemonEntity* p) {
    if (countPokemon > bagSizePokemon) return false;
    pokemons[countPokemon++] = p->clone();
    return true;
}

bool Bag::switchActive(int index) {
    if (index < 0 || index >= countPokemon) return false;
    activeIndex = index;
    return true;
}


PokemonEntity* Bag::getActive() {
    return (countPokemon > activeIndex ? pokemons[activeIndex] : nullptr);
}

PokemonEntity* Bag::getPokemonAt(int i){
    return (countPokemon > i ? pokemons[i] : nullptr);
}

int Bag::getAcitiveIndex(){
    return activeIndex;
}

int Bag::getPokemonAmount(){
    return countPokemon;
}

int Bag::getPokemonCapacity(){
    return bagSizePokemon;
}

void Bag::healAllPokemon(){
    for(int i =0; i < countPokemon; i++){
        pokemons[i]->resetHP(pokemons[i]->getMaxHP());
    }
}

bool Bag::evolve(int i){
    vector<string> evolutionName;
    vector<Pokemon> db = allPokemon.findPokemonByType(pokemons[i]->getType());
    int level = pokemons[i]->getLevel();
    int index;

    for(int j =0; j < db.size(); j++){
        if(pokemons[i]->getName() == db.at(j).getName()){
            index = j;
            break;
        }
    }

    evolutionName.push_back(pokemons[i]->getName());

    if(pokemons[i]->getType() == "Fire"){
        delete pokemons[i];
        pokemons[i] = new FirePokemon(db[index+1].getName(),db[index+1].getType(),level,db[index+1].getStage(),db[index+1].getMaxHP(),0,db[index+1].getMoveSet());
        evolutionName.push_back(pokemons[i]->getName());

        Menu::drawMenu({"Exit"},{"  ** CONGRATULATIONS! **", string("Your ") + evolutionName[0] + " evolved into " + evolutionName[1] + "!","View it in you bag" },10,20, 5,20);

        return true;
    }else if(pokemons[i]->getType() == "Water"){
        delete pokemons[i];
        pokemons[i] = new WaterPokemon(db[index+1].getName(),db[index+1].getType(),level,db[index+1].getStage(),db[index+1].getMaxHP(),0,db[index+1].getMoveSet());
        evolutionName.push_back(pokemons[i]->getName());

        Menu::drawMenu({"Exit"},{"  ** CONGRATULATIONS! **", string("Your ") + evolutionName[0] + " evolved into " + evolutionName[1] + "!","View it in you bag" },10,20, 5,20);

        return true;
    }else if(pokemons[i]->getType() == "Grass"){
        delete pokemons[i];
        pokemons[i] = new GrassPokemon(db[index+1].getName(),db[index+1].getType(),level,db[index+1].getStage(),db[index+1].getMaxHP(),0,db[index+1].getMoveSet());
        evolutionName.push_back(pokemons[i]->getName());

        Menu::drawMenu({"Exit"},{"  ** CONGRATULATIONS! **", string("Your ") + evolutionName[0] + " evolved into " + evolutionName[1] + "!","View it in you bag" },10,20, 5,20);

        return true;
    }else{
        return false;
    }
}

void Bag::addPotion(int amount){
    potionsAmount = potionsAmount + amount;
}

bool Bag::usePotion(){
    if(potionsAmount <= 0) return false;
    potions.use(pokemons[activeIndex]);
    potionsAmount --;
    return true;
}

int Bag::getPotionAmount(){
    return potionsAmount;
}

void Bag::setPotionsAmount(int amount){
    potionsAmount = amount;
}

void Bag::addBalls(int amount){
    ballsAmount = ballsAmount + amount;
}

bool Bag::useBalls(PokemonEntity* target){
    bool isCapture;
    isCapture = balls.use(target);
    ballsAmount --;
    return isCapture;
}

int Bag::getBallAmount(){
    return ballsAmount;
}

void Bag::setBallAmount(int amount){
    ballsAmount = amount;
}

Bag::~Bag() {
    for(int i=0; i<countPokemon; i++) {
        delete pokemons[i];
        pokemons[i] = nullptr;
    }
    delete[] pokemons;
    pokemons = nullptr;
}