#ifndef MOVE_H
#define MOVE_H

#include<string>

using namespace std;

class Move{
private:
    string name;
    string type;
    int power;
    int accuracy;
    int critRate;

public:
    Move(string name, string type, int power);

    // Getter
    string getName();
    string getType();
    int getPower();
    int getAccuracy();
    int getCritRate();
    // Setter
    void setName(string name);
    void setType(string type);
    void setPower(int power);
    void setAccuracy(int accuracy);
    void setCritRate(int critRate);

};

#endif