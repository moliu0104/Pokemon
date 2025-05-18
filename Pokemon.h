#ifndef POKEMON_H
#define POKEMON_H

#include<vector>
#include<string>
#include"Move.h"

using namespace std;

class Pokemon{
protected:
    string name;
    string type;
    int stage;
    int maxHP;
    vector<Move> moveSet;

public:
    Pokemon() = default;
    Pokemon(string name, string type, int stage, int maxHP, vector<Move> moveSet);

    // Getters
    string getName() ;
    string getType() ;
    int getStage() ;
    int getMaxHP() ;
    vector<Move> getMoveSet() ;

    // Setters
    void setName(string name);
    void setStage(int stage);
    void setType(string type);
    void setMaxHP(int maxHP);
    void addMove(Move move);

    ~Pokemon();
    
};

#endif