#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Character.h"

using namespace std;

int finder(vector<Character> characters, int old_j){
    int new_j;
    string result_name;
    vector<string> names;
    names.push_back(characters[old_j].name);
    if(old_j<5){
        for(int i=0; i<5; i++){
            if(characters[i].is_alive){
                names.push_back(characters[i].name);
            }
        }
        sort(names.begin(), names.end());
        if(names[(int)names.size()-1]==characters[old_j].name){
            result_name = names[(int)names.size()-2];
        }
        else{
            for(int i=0; i<names.size(); i++){
                if(names[i]==characters[old_j].name){
                    result_name = names[i+1];
                }
            }
        }

        for(int i=0; i<5; i++){
            if(characters[i].name==result_name){
                new_j = i;
            }
        }

    }
    else{

        for(int i=5; i<10; i++){
            if(characters[i].is_alive){
                names.push_back(characters[i].name);
            }
        }
        sort(names.begin(), names.end());
        if(names[(int)names.size()-1]==characters[old_j].name){
            result_name = names[(int)names.size()-2];
        }
        else{
            for(int i=0; i<names.size(); i++){
                if(names[i]==characters[old_j].name){
                    result_name = names[i+1];
                }
            }
        }

        for(int i=5; i<10; i++){
            if(characters[i].name==result_name){
                new_j = i;
            }
        }

    }

    return new_j;
}

int main(int argc, char* argv[]) {

    ifstream infile;
    infile.open(argv[1]);

    ofstream outfile;
    outfile.open(argv[2]);

    int nof_games = 1;
    //infile>>nof_games;

    for(int game = 0; game<nof_games; game++) {

        string team1_previously_killed = "";
        string team2_previously_killed = "";


        int nof_round;
        infile >> nof_round;

        vector<Character> characters;

        for (int i = 0; i < 10; i++) {
            string name, type;
            int health, def, ad;
            infile >> name >> type >> ad >> def >> health;
            Character temp(name, type, health, def, ad, nof_round);
            characters.push_back(temp);


        }

        //infile >> nof_round;

        bool finish = false;
        int finish_round = nof_round;
        string winner = "Draw";
        int nof_alive = 0;


        for (int i = 0; i < nof_round; i++) {
            if (finish){
                cout<<"evet"<<endl;
                for(int j = 0; j<nof_round-finish_round-1;j++){
                    string temp1, temp2, temp3;
                    infile >> temp1 >> temp2 >> temp3;
                }

                break;
            }

            string attacker, defender, special;
            infile >> attacker >> defender >> special;

            for (int j = 0; j < characters.size(); j++) {
                characters[j].health_history[i] = characters[j].health;
            }

            for (int j = 0; j < characters.size(); j++) {
                if (characters[j].name == attacker) {
                    for (int k = 0; k < characters.size(); k++) {
                        if (characters[k].name == defender) {
                            int old_j = j, old_k = k;
                            if (characters[j].is_alive == false) {
                                j = finder(characters, j);
                            }
                            if (characters[k].is_alive == false) {
                                k = finder(characters, k);
                            }

                            if ((characters[j].type == "Elves") && (special == "SPECIAL") &&
                                (characters[j].special_round >= 10)) {
                                characters[j].special_round = 0;
                                if (j < 5) {
                                    characters[0].health += (characters[j].health / 2);
                                    characters[j].health -= (characters[j].health / 2);
                                } else {
                                    characters[5].health += (characters[j].health / 2);
                                    characters[j].health -= (characters[j].health / 2);
                                }
                            }

                            if ((characters[j].type == "Dwarfs") && (special == "SPECIAL") &&
                                (characters[j].special_round >=20)) {
                                characters[j].special_round = 0;
                                //cout << "Up" << endl;
                                Character temp_dwarf = characters[j];
                                //cout << "Down" << endl;
                                characters[k].health -= max(0, temp_dwarf.ad - characters[k].def);
                            }

                            if ((characters[j].type == "Wizards") && (special == "SPECIAL") &&
                                (characters[j].special_round >=50)) {

                                //cout << "Wizard Up" << endl;
                                if(j<5){
                                    for (int u = 0; u < characters.size(); u++) {
                                        if (characters[u].name == team1_previously_killed) {
                                            characters[j].special_round = 0;
                                            characters[u].is_alive = true;
                                            characters[u].health = characters[u].health_history[0];
                                        }

                                    }
                                }
                                else{
                                    for (int u = 0; u < characters.size(); u++) {
                                        if (characters[u].name == team2_previously_killed) {
                                            characters[j].special_round = 0;
                                            characters[u].is_alive = true;
                                            characters[u].health = characters[u].health_history[0];
                                        }

                                    }
                                }

                                //characters[j].type = "Men";
                                //cout << "Wizard Down" << endl;
                                //characters[k].health -= max(0, temp_dwarf.ad-characters[k].def);
                            }


                            characters[k].health -= max(0, characters[j].ad - characters[k].def);

                            if (characters[k].health <= 0) {
                                characters[k].health = 0;
                                characters[k].is_alive = false;
                                if(k<5){
                                    team1_previously_killed = characters[k].name;
                                }
                                else{
                                    team2_previously_killed = characters[k].name;
                                }
                            }

                            if ((characters[0].is_alive == false) ||
                                ((characters[1].is_alive == false) && (characters[2].is_alive == false) &&
                                 (characters[3].is_alive == false) && (characters[4].is_alive == false))) {
                                cout << "Team 1 lost" << endl;
                                finish = true;
                                finish_round = i+1;
                                winner = "Community-2";
                            }
                            if ((characters[5].is_alive == false) ||
                                ((characters[6].is_alive == false) && (characters[7].is_alive == false) &&
                                 (characters[8].is_alive == false) && (characters[9].is_alive == false))) {
                                cout << "Team 2 lost" << endl;
                                finish = true;
                                finish_round = i+1;
                                winner = "Community-1";
                            }
                            for (int m = 0; m < characters.size(); m++) {
                                characters[m].special_round += 1;
                            }

                            j = old_j;
                            k = old_k;

                        }
                    }
                }
            }

        }

        for (int j = 0; j < characters.size(); j++) {
            characters[j].health_history[finish_round] = characters[j].health;
        }

        for (int i = 0; i < 10; i++) {
            if(characters[i].is_alive)
                nof_alive++;

        }

        /*
        int nof_query;
        infile >> nof_query;


        for(int i=0; i<nof_query; i++){
            string temp_query;
            infile >> temp_query;


            if(temp_query == "Winner"){
                outfile<<winner<<endl;
            }
            else if(temp_query == "Number_of_Rounds"){
                outfile<<finish_round<<endl;
            }
            else if(temp_query == "Number_of_Alive"){
                outfile<<nof_alive<<endl;
            }
            else if(temp_query[temp_query.length()-1]=='h'){
                //outfile<<temp_query.substr(0, temp_query.find("_"))<<endl;
                for (int k = 0; k < 10; k++) {
                    if(characters[k].name==temp_query.substr(0, temp_query.find("_")))
                        outfile<<temp_query.substr(0, temp_query.find("_"))<<" "<<characters[k].health<<endl;

                }
            }
            else{
                //outfile<<temp_query.substr(0, temp_query.find("_"))<<endl;
                for (int k = 0; k < 10; k++) {
                    if(characters[k].name==temp_query.substr(0, temp_query.find("_"))) {

                        outfile << temp_query.substr(0, temp_query.find("_")) << " ";
                        for (int m = 0; m < finish_round+1; m++) {
                            outfile << characters[k].health_history[m] << " ";
                        }
                        outfile<<endl;
                    }
                }
            }
        }
         */
        outfile<<winner<<endl;
        outfile<<finish_round<<endl;
        outfile<<10-nof_alive<<endl;
        for (int k = 0; k < 10; k++) {
            outfile <<characters[k].name <<" ";
            for (int m = 0; m < finish_round+1; m++) {
                outfile << characters[k].health_history[m] << " ";
            }
            outfile<<endl;
        }


    }
    infile.close();
    return 0;
}
