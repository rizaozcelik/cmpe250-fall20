#ifndef PERSON_H
#define PERSON_H

class Person{

private:
    int id;
    int retrieved_gifts;
    int total_valid_commit;
    float sticker_waiting_time;
    float hoodie_waiting_time;
    float queue_enter_time;
    float hqueue_enter_time;
    int desk_id;

public:
    void increment_valid_commits();
    void increment_retrieved_gifts();
    int get_id();
    int get_retrieved_gifts();
    int get_total_valid_commits();
    float get_sticker_waiting_time();
    float get_hoodie_waiting_time();
    float get_queue_enter_time();
    float get_hqueue_enter_time();
    int get_desk_id();
    void set_id(int pid);
    void set_retrieved_gifts(int pretrieved_gifts);
    void set_total_valid_commits(int ptotal_valid_commit);
    void increase_sticker_waiting_time(float psticker_time);
    void increase_hoodie_waiting_time(float phoodie_time);
    void set_queue_enter_time(float pqueue_time);
    void set_hqueue_enter_time(float phqueue_time);
    void set_desk_id(int id);
    bool operator<(Person& another_person);
    Person();
    Person(int pid, int pretrieved_gifts, int ptotal_valid_commit);
};
#endif
