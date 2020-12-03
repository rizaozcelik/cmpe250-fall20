#include <string>
using namespace std;

#ifndef CHARACTER_H
#define CHARACTER_H


class Character {

public:
    bool isAlive = true;
    string name, type;
    int attack, defense, remainingHealth, nMaxRounds, nRoundsSinceSpecial;
    int* healthHistory = NULL;

    Character(string _name, string _type, int _attack, int _defense, int _remainingHealth, int _nMaxRounds);
    Character(const Character& character);
    Character operator=(const Character& character);
    bool operator<(const Character& other);
    ~Character();
};


#endif //CHARACTER_H
