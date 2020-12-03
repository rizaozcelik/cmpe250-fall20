//
// Created by umutd on 28.09.2020.
//
#include <string>
#include <iostream>
using namespace std;

#ifndef INC_250_PROJECT_1_CHARACTER_H
#define INC_250_PROJECT_1_CHARACTER_H


class Character {

public:
    bool is_alive;
    string name, type;
    int health, def, ad, special_round, nof_round;
    int* health_history = NULL;

    Character(string _name,string _type,int _health,int _def, int _ad, int nof_round);

    Character(const Character& character);
    Character& operator=(const Character& character);
    Character(Character&& character);
    Character& operator=(Character&& character);
    ~Character();
};


#endif //INC_250_PROJECT_1_CHARACTER_H
