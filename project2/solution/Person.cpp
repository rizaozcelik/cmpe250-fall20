#include "Person.h"
#include <iostream>
using namespace std;

Person::Person(){}
Person::Person(int pid, int pretrieved_gifts, int ptotal_valid_commit){
    id = pid;
    retrieved_gifts = pretrieved_gifts;
    total_valid_commit = ptotal_valid_commit;
    sticker_waiting_time = 0;
    hoodie_waiting_time = 0;
    queue_enter_time = 0;
    desk_id = 0;
    hqueue_enter_time = 0;
}

void Person::increment_valid_commits(){
    Person::total_valid_commit +=1;
}
void Person::increment_retrieved_gifts(){
    retrieved_gifts++;
}
int Person::get_id(){
    return id;
}
int Person::get_retrieved_gifts(){
    return retrieved_gifts;
}
int Person::get_total_valid_commits(){
    return total_valid_commit;
}
float Person::get_hoodie_waiting_time(){
    return hoodie_waiting_time;
}
float Person::get_sticker_waiting_time(){
    return sticker_waiting_time;
}
float Person::get_queue_enter_time(){
    return queue_enter_time;
}
float Person::get_hqueue_enter_time(){
    return hqueue_enter_time;
}
int Person::get_desk_id(){
    return desk_id;
}
void Person::set_id(int pid){
    id = pid;
}
void Person::set_retrieved_gifts(int pretrieved_gifts){
    retrieved_gifts = pretrieved_gifts;
}
void Person::set_total_valid_commits(int ptotal_valid_commit){
    total_valid_commit = ptotal_valid_commit;
}
void Person::increase_hoodie_waiting_time(float phoodie_time){
    hoodie_waiting_time += phoodie_time;
}
void Person::increase_sticker_waiting_time(float psticker_time){
    sticker_waiting_time += psticker_time;
}
void Person::set_queue_enter_time(float pqueue_time){
    queue_enter_time = pqueue_time;
}
void Person::set_hqueue_enter_time(float phqueue_time){
    hqueue_enter_time = phqueue_time;
}
void Person::set_desk_id(int id){
    desk_id = id;
}
bool Person::operator<(Person& another_person) {
    if (total_valid_commit != another_person.get_total_valid_commits()){
        return total_valid_commit > another_person.get_total_valid_commits();
    }
    
    if (abs(hqueue_enter_time - another_person.get_hqueue_enter_time())>0.0001){
        
        return hqueue_enter_time < another_person.get_hqueue_enter_time();
    }
    
    return id < another_person.get_id();
}