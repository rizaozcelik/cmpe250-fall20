#include "Event.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip> 
using namespace std;

Event::Event() {}

Event::Event(string event, int pers_id, float tick,int pcode_length) {
    event_type = event;
    current_tick = tick;
    code_length = pcode_length;
    person_id = pers_id;
}

int Event::get_code_length(){
    return code_length;
}

string& Event::get_event_type() {
    return event_type;
}

int Event::get_person_id(){
    return person_id;
}

float Event::get_current_tick(){
    return current_tick;
}

bool Event::operator<(Event& another_event) {
    if (abs(current_tick - another_event.get_current_tick())>0.00001){
        return current_tick < another_event.get_current_tick();
    }

    return person_id < another_event.get_person_id();
}