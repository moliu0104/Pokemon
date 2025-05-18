#ifndef MOVE_H
#define MOVE_H

#include<string>

using namespace std;

class Move{
private:
    string name;
    string type;
    int damage;

public:
    Move(string name, string type, int damage);

    // Getter
    string getName();
    string getType();
    int getDamage();
    // Setter
    void setName(string name);
    void setType(string type);
};

#endif