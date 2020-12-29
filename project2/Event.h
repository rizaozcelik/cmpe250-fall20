#ifndef EVENT_H
#define EVENT_H

#include "Person.h"
#include <string>

using namespace std;

class Event{
private:
    string event_type;
    int person_id;
    float current_tick;
    int code_length;

public:
    string& get_event_type();
    int get_person_id();
    int get_code_length();
    float get_current_tick();
    bool operator<(Event& another_event);
    Event();
    Event(string event, int pers_id, float tick,int pcode_length=0);
};
#endif
