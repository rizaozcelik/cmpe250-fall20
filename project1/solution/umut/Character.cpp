//
// Created by umutd on 28.09.2020.
//

#include "Character.h"

Character::Character(string _name, string _type, int _health, int _def, int _ad, int nof_round) {
    //cout<<"Constructor"<<endl;
    this->name = _name;
    this->type = _type;
    this->health = _health;
    this->def = _def;
    this->ad = _ad;
    this->is_alive = true;
    this->special_round = 0;
    this->nof_round = nof_round+1;
    this->health_history = new int[nof_round+1];
}

Character::Character(const Character &character) {
    //cout<<"Copy Constructor"<<endl;
    this->name = character.name;
    this->type = character.type;
    this->health = character.health;
    this->def = character.def;
    this->ad = character.ad;
    this->is_alive = character.is_alive;
    this->special_round = character.special_round;
    this->nof_round = character.nof_round;
    this->health_history = new int[character.nof_round];
    for(int i=0;i <nof_round; i++){
        this->health_history[i] = character.health_history[i];
    }

}

Character& Character::operator=(const Character &character) {
    //cout<<"Copy assignment"<<endl;
    this->name = character.name;
    this->type = character.type;
    this->health = character.health;
    this->def = character.def;
    this->ad = character.ad;
    this->is_alive = character.is_alive;
    this->special_round = character.special_round;
    this->nof_round = character.nof_round;
    delete[] health_history;
    this->health_history = new int[character.nof_round];
    for(int i=0;i <nof_round; i++){
        this->health_history[i] = character.health_history[i];
    }
    return *this;

}

Character::Character(Character &&character) {
    //cout<<"Move Constructor"<<endl;
    this->name = character.name;
    this->type = character.type;
    this->health = character.health;
    this->def = character.def;
    this->ad = character.ad;
    this->is_alive = character.is_alive;
    this->special_round = character.special_round;
    this->nof_round = character.nof_round;
    this->health_history = character.health_history;

    character.name = "";
    character.type = "";
    character.health = 0;
    character.def = 0;
    character.ad = 0;
    character.is_alive = false;
    character.special_round = 0;
    character.nof_round = 0;
    character.health_history = NULL;


}

Character& Character::operator=(Character &&character) {
    //cout<<"Move Assignment"<<endl;
    this->name = character.name;
    this->type = character.type;
    this->health = character.health;
    this->def = character.def;
    this->ad = character.ad;
    this->is_alive = character.is_alive;
    this->special_round = character.special_round;
    this->nof_round = character.nof_round;
    delete[] health_history;
    this->health_history = character.health_history;

    character.name = "";
    character.type = "";
    character.health = 0;
    character.def = 0;
    character.ad = 0;
    character.is_alive = false;
    character.special_round = 0;
    character.nof_round = 0;
    character.health_history = NULL;

    return *this;

}

Character::~Character() {

    //cout<<"Destructor"<<endl;
    delete[] health_history;
}