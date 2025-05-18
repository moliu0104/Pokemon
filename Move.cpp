#include"Move.h"

Move::Move(string name, string type, int damage): name(name), type(type), damage(damage){}

string Move::getName(){
    return name;
}

string Move::getType(){
    return type;
}

int Move::getDamage(){
    return damage;
}