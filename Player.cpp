#include"Player.h"
#include"Bag.h"

Player::Player(){
    moneyAmount = 0;
    bag = new Bag;
}

Bag& Player::getBag(){
    return *bag;
}

int Player::getMoneyAmount(){
    return moneyAmount;
}

void Player::setMoneyAmount(int amount){
    moneyAmount = amount;
}

void Player::addMoney(int amount){
    moneyAmount += amount;
}

void Player::spendMoney(int amount){
    moneyAmount -= amount;
}

void Player::addPokemonToBag(PokemonEntity* pokemon){
    bag->addPokemon(pokemon);
}

PokemonEntity* Player::getActivePokemon(){
    return bag->getActive();
}

Player::~Player(){
    delete bag;
}

Player player;