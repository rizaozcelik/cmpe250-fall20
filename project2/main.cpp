Bunlar da dersi takip eden arkadaşlar#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Person.h"
#include "Event.h"
#include "BinaryMinHeap.h"
#include <queue>
#include <cmath>
#include <iomanip> 
#include <set>

using namespace std;

const int CODE_LENGTH_THRESHOLD = 20;
const int GIFT_THRESHOLD = 3;
const int QUEUE_ENTRANCE_THRESHOLD =3;

int sticker_counter,hoodie_counter;
queue<Person> sticker_queue;
BinaryMinHeap<Person> hoodie_queue;

struct statistics {
  float total_code_commits = 0;
  float total_length_commits = 0;
  int total_invalid_queue = 0;
  int total_invalid_gift = 0;
  float total_turnaround_time = 0;
  int max_sticker_queue = 0;
  int max_hoodie_queue = 0;
} stats;

FILE* fp;
BinaryMinHeap<Event> event_heap;
vector<Person> persons;

int find(bool* arr,int size){
    for(int i=0;i<size;i++){
        if (arr[i]) return i;
    }
    return -1;
}

void code_commit(int code_length,Person& p){
    stats.total_code_commits++;
    stats.total_length_commits += code_length;
    
    if  (code_length >= CODE_LENGTH_THRESHOLD) p.increment_valid_commits();
}

void enter_sticker(bool* sticker_available, float* sticker_times, float current_tick, Person& p){
    if(p.get_total_valid_commits() < QUEUE_ENTRANCE_THRESHOLD){
        stats.total_invalid_queue++;
        return;
    }

    if(p.get_retrieved_gifts() == GIFT_THRESHOLD){
        stats.total_invalid_gift++;
        return;
    }

    p.set_queue_enter_time(current_tick);
    
    int available_desk = find(sticker_available, sticker_counter);
    if(available_desk == -1){// there is no available desk
        sticker_queue.push(move(p)); 

        if (sticker_queue.size() > stats.max_sticker_queue) stats.max_sticker_queue = sticker_queue.size();
    }
    else{
        sticker_available[available_desk] = false;
        p.set_desk_id(available_desk);
       
        Event event("leave_sticker",p.get_id(),current_tick + sticker_times[available_desk]);
        event_heap.push(move(event));
        }
}

void leave_sticker(bool* sticker_available, float* sticker_times, float current_tick, Person& p){
    int sticker_desk = p.get_desk_id();
    Event event("hoodie",p.get_id(),current_tick);
    event_heap.push(move(event));
    
    if (!sticker_queue.empty()){// there are some people waiting
        Person temp;
        temp = sticker_queue.front();
        sticker_queue.pop();

        Person& p1 = persons[temp.get_id()-1];
        p1.increase_sticker_waiting_time(current_tick - p1.get_queue_enter_time());
        p1.set_desk_id(sticker_desk);
        
        Event event("leave_sticker",p1.get_id(),current_tick + sticker_times[sticker_desk]);
        event_heap.push(move(event));
    }
    else sticker_available[sticker_desk] = true;
}

void enter_hoodie(bool* hoodie_available, float* hoodie_times, float current_tick, Person& p){
    p.set_hqueue_enter_time(current_tick);
   
    int available_desk = find(hoodie_available, hoodie_counter);
    if(available_desk == -1){// there is no available desk
        hoodie_queue.push(move(p));

        if (hoodie_queue.getSize() > stats.max_hoodie_queue) stats.max_hoodie_queue = hoodie_queue.getSize();
    }
    else{
        hoodie_available[available_desk] = false;
        p.set_desk_id(available_desk);
        
        Event event("leave_hoodie",p.get_id(),current_tick + hoodie_times[available_desk]);
        event_heap.push(move(event));
        }
}

void leave_hoodie(bool* hoodie_available, float* hoodie_times, float current_tick, Person& p){
    p.increment_retrieved_gifts();
    stats.total_turnaround_time+= current_tick - p.get_queue_enter_time();
    
    int hoodie_desk = p.get_desk_id();
    // get hacker for hoodie desk
    if (!hoodie_queue.isEmpty()){
        Person temp;
        hoodie_queue.deleteMin(temp);
        Person& p1 = persons[temp.get_id()-1];
        
        p1.increase_hoodie_waiting_time(current_tick - p1.get_hqueue_enter_time());
        p1.set_desk_id(hoodie_desk);
       
        Event event("leave_hoodie",p1.get_id(),current_tick + hoodie_times[hoodie_desk]);
       
        event_heap.push(move(event));
       }
    else hoodie_available[hoodie_desk] = true;
}

float total_gifts(){
    float total = 0;
    for(int i=0;i<persons.size();i++){
        total += persons[i].get_retrieved_gifts();
    }
    return total;
}

float average_gifts(){
    float total = total_gifts();
    return total/persons.size();
}

float average_waiting_sticker(){
    float total = 0;
    for(int i=0;i<persons.size();i++){
        total += persons[i].get_sticker_waiting_time();
    }
    return total/total_gifts();
}

float average_waiting_hoodie(){
    float total = 0;
    for(int i=0;i<persons.size();i++){
        total += persons[i].get_hoodie_waiting_time();
    }
    return total/total_gifts();
}

int max_wait_person(float* pwaiting_time){
    int id = persons[0].get_id();
    *pwaiting_time = persons[0].get_sticker_waiting_time() + persons[0].get_hoodie_waiting_time();;
    
    for(int i=1;i<persons.size();i++){
        float wait = persons[i].get_sticker_waiting_time() + persons[i].get_hoodie_waiting_time();
        if (wait - *pwaiting_time > 0.00001){
            id = persons[i].get_id();
            *pwaiting_time = wait;
        }
    }
    return id;
}

int min_wait_among_3_gifts(float* pwaiting_time){
    int id = -1;
    *pwaiting_time = -1;
    
    for(int i=0;i<persons.size();i++){
        if(persons[i].get_retrieved_gifts() == 3){
            float wait = persons[i].get_sticker_waiting_time() + persons[i].get_hoodie_waiting_time();
            if ((*pwaiting_time - wait > 0.00001) || id == -1){
                id = persons[i].get_id();
                *pwaiting_time = wait;
            }
        }
    }
    return id;
}

void simulator(float* sticker_times, float* hoodie_times,int total_commits){
     bool sticker_available[sticker_counter];
     for(int i=0;i<sticker_counter;i++) sticker_available[i] = true;

     bool hoodie_available[hoodie_counter];
     for(int i=0;i<hoodie_counter;i++) hoodie_available[i] = true;

     float current_tick;
 
     while (!event_heap.isEmpty()) {// run untill all events are done.
            Event currentEvent;
            event_heap.deleteMin(currentEvent);
            
            string event_type = currentEvent.get_event_type();
            current_tick = currentEvent.get_current_tick();

            if (event_type.compare("sticker") == 0) enter_sticker(sticker_available,sticker_times,currentEvent.get_current_tick(),persons[currentEvent.get_person_id()-1]);
            else if (event_type.compare("hoodie") == 0) enter_hoodie(hoodie_available,hoodie_times,currentEvent.get_current_tick(),persons[currentEvent.get_person_id()-1]);
            else if (event_type.compare("code_commit") == 0) code_commit(currentEvent.get_code_length(),persons[currentEvent.get_person_id()-1]); 
            else if (event_type.compare("leave_sticker") == 0) leave_sticker(sticker_available,sticker_times,currentEvent.get_current_tick(),persons[currentEvent.get_person_id()-1]);
            else if (event_type.compare("leave_hoodie") == 0) leave_hoodie(hoodie_available,hoodie_times,currentEvent.get_current_tick(),persons[currentEvent.get_person_id()-1]);


     }
     fprintf(fp,"%d\n",stats.max_sticker_queue);
     fprintf(fp,"%d\n",stats.max_hoodie_queue);
     fprintf(fp,"%.3f\n",average_gifts());
     fprintf(fp,"%.3f\n",average_waiting_sticker());
     fprintf(fp,"%.3f\n",average_waiting_hoodie());
     fprintf(fp,"%.3f\n",stats.total_code_commits/persons.size());
     fprintf(fp,"%.3f\n",stats.total_length_commits/total_commits);
     fprintf(fp,"%.3f\n",stats.total_turnaround_time/total_gifts());
     fprintf(fp,"%d\n",stats.total_invalid_queue);
     fprintf(fp,"%d\n",stats.total_invalid_gift);
     float max_waiting, min_waiting;
     int id = max_wait_person(&max_waiting);
     fprintf(fp,"%d %.3f\n",id,max_waiting);
     id = min_wait_among_3_gifts(&min_waiting);
     fprintf(fp,"%d %.3f\n",id,min_waiting);
     fprintf(fp,"%.3f",current_tick);
}

int main(int argc, char* argv[]){
    ifstream infile(argv[1]);
    fp = fopen(argv[2],"w");

    int total_contestants,total_commits;
    float arrival_tick;
    infile>>total_contestants;
    for(int i=0;i<total_contestants;i++){
        infile>>arrival_tick;
        Person p1(i+1,0,0);
        persons.push_back(p1);
    }
    
    infile>>total_commits;
    int id,code_length;
    float tick;
    for(int i=0;i<total_commits;i++){
        infile>>id>>code_length>>tick;
        Event event("code_commit",id,tick,code_length);
        event_heap.push(move(event));
    }

    int total_queue;
    infile>>total_queue;
    for(int i=0;i<total_queue;i++){
        infile >> id>> tick;
        Event event("sticker",id,tick);
        event_heap.push(move(event));
    }

    infile>>sticker_counter;
    float sticker_times[sticker_counter];
    for(int i=0;i<sticker_counter;i++){
        infile>>sticker_times[i];
    }

    infile>>hoodie_counter;
    float hoodie_times[hoodie_counter];
    for(int i=0;i<hoodie_counter;i++){
        infile>>hoodie_times[i];
    }

    simulator(sticker_times,hoodie_times,total_commits);
    
    infile.close();
    fclose(fp);
}