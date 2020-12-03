#include "Character.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void printCommunity(ofstream& outfile, vector<Character> community, int round) {
	for (int i = 0; i < 5; i++) {
		Character c = community[i];
		outfile << c.name;
		for (int i = 0; i < round + 1; i++) {
			outfile << ' ' << c.healthHistory[i];
		}
		outfile << endl;
	}
}

bool warContinues(vector<Character> community) {
	bool isHobbitAlive, isAnyMemberAlive = false;
	for (int i = 0; i < 5; i++) {
		Character c = community[i];
		if (c.type == "Hobbit") {
			isHobbitAlive = c.isAlive;
		} else {
			isAnyMemberAlive = isAnyMemberAlive || c.isAlive;
		}
	}
	return isHobbitAlive && isAnyMemberAlive;
}

void updateNRoundsSinceSpecial(vector<Character>& community) {
	for (int i = 0; i < 5; i++) {
		Character* c = &community[i];
		c->nRoundsSinceSpecial = c->nRoundsSinceSpecial + 1;
	}
}

void updateHealthHistory(vector<Character>& community, int round) {
	for (int i = 0; i < 5; i++) {
		Character* c = &community[i];
		c->healthHistory[round] = c->remainingHealth;
	}
}

Character findActor(string actorName, vector<Character> community) {
	// Pass a copy; do not care if the vector is changed in the function.
	sort(community.begin(), community.end());

	int actorIdx = -1;
	for (int i = 0; i < 5; i++) {
		Character c = community[i];
		if (actorName == c.name) {
			actorIdx = i;
			if (c.isAlive) {
				return c;
			}
			break; // If the actor is dead, search the other actors.
		}
	}
	
	// Check alphabetically next actor
	for (int j = actorIdx + 1; j < 5; j++) {
		Character c = community[j];
		if (c.isAlive) {
			return c;
		}	
	}

	// Check alphabetically previous actor	
	for (int j = actorIdx-1; j >= 0; j--) {
		Character c = community[j];
		if (c.isAlive) {
			return c;
		}	
	}
}

Character readCharacter(ifstream& infile, int nMaxRounds) {
	string charName, charType;
	int attack, defense, initialHealth;
	infile >> charName >> charType >> attack >> defense >> initialHealth;
	return Character(charName, charType, attack, defense, initialHealth, nMaxRounds);
}

int main(int argc, char* argv[]) {

	ifstream infile;
	infile.open(argv[1]);

	int nMaxRounds;
	infile >> nMaxRounds;

	// Create an empty vector of characters. If you try to intialize it with 5 characters, you shall get an error!
	vector<Character> community1;
	for (int i = 0; i < 5; i++)	{
		community1.push_back(readCharacter(infile, nMaxRounds));
	}

	vector<Character> community2;
	for (int i = 0; i < 5; i++)	{
		community2.push_back(readCharacter(infile, nMaxRounds));
	}

	// Store one pointer for each of the attacker and defenders. Will swap them at each round.
	vector<Character>* attackerCommunity = &community1;
	vector<Character>* defenderCommunity = &community2;
	int idxLastDeadAttacker = -1, idxLastDeadDefender = -1; // Track the last dead character for Wizard's special skill.
	bool ifWarContinues = true;
	int round = 1;
	while (round <= nMaxRounds && ifWarContinues) {
		string attackerName, defenderName, isSpecialStr;
		infile >> attackerName >> defenderName >> isSpecialStr;
		bool isSpecial = isSpecialStr == "SPECIAL";
		Character attacker = findActor(attackerName, *attackerCommunity); // These will be used only for info read. Updates are useless.
		Character defender = findActor(defenderName, *defenderCommunity);

		int extraDamagePoint = 0; // Will be used for Dwarf's special skill.
		if (isSpecial) {
			if (attacker.type == "Elves" && attacker.nRoundsSinceSpecial >= 10) {
				int transferAmount = attacker.remainingHealth / 2;
				for (int i = 0; i < 5; i++) {
					// I will modify the character so I use alias operator.
					// I can also use address and pointers. See Dwarf's special skill for such example
					Character& c = attackerCommunity->at(i);
					if (c.type == "Hobbit") {
						c.remainingHealth += transferAmount;
						c.healthHistory[round] = c.remainingHealth;
					} else if (c.type == "Elves") {
						c.remainingHealth -= transferAmount;
						c.nRoundsSinceSpecial = 0;
					}
				}
			} else if (attacker.type == "Dwarfs" && attacker.nRoundsSinceSpecial >= 20) {
				extraDamagePoint = attacker.attack - defender.defense;
				for (int i = 0; i < 5; i++) {
					// I will modify c and obtain its pointer.
					Character* c = &(attackerCommunity->at(i));
					if (c->type == "Dwarfs") {
						c->nRoundsSinceSpecial = 0;
					}
				}
			} else if (attacker.type == "Wizards" && attacker.nRoundsSinceSpecial >= 50 && idxLastDeadAttacker != -1) {
				attackerCommunity->at(idxLastDeadAttacker).isAlive = true;
				attackerCommunity->at(idxLastDeadAttacker).remainingHealth = attackerCommunity->at(idxLastDeadAttacker).healthHistory[0];
				attackerCommunity->at(idxLastDeadAttacker).nRoundsSinceSpecial = 0;
				for (int i = 0; i < 5; i++) {
					Character* c = &((*attackerCommunity)[i]);
					if (c->type == "Wizards") {
						c->nRoundsSinceSpecial = 0;
					}
				}
			}
		}

		// Finally, do the attack!
		int damagePoint = max(attacker.attack - defender.defense + extraDamagePoint, 0);
		for (int i = 0; i < 5; i++) {
			Character& c = defenderCommunity->at(i);
			if (defender.name == c.name) {
				c.remainingHealth = max(c.remainingHealth - damagePoint, 0);
				c.isAlive = c.remainingHealth > 0;
				if (!c.isAlive) {
					idxLastDeadDefender = i;
				}
			}
		}

		// Bookkeeping
		updateHealthHistory(community1, round);
		updateHealthHistory(community2, round);
		// Move to next round.
		updateNRoundsSinceSpecial(community1);
		updateNRoundsSinceSpecial(community2);
		ifWarContinues = warContinues(*defenderCommunity); 
		swap(attackerCommunity, defenderCommunity);
		swap(idxLastDeadAttacker, idxLastDeadDefender);
		round++;
	}
	round--;
	infile.close();

	ofstream outfile;
	outfile.open(argv[2]);

	if (ifWarContinues) {
		outfile << "Draw" << endl;
	} else if (round % 2 == 1) {
		outfile << "Community-1" << endl;
	} else {
		outfile << "Community-2" << endl;		
	}

	outfile << round << endl;
	int nCasualties = 0;
	for (int i = 0; i < 5; i++) {
		Character c1 = community1[i];
		Character c2 = community2[i];
		if (!c1.isAlive) {
			nCasualties += 1;
		}
		if (!c2.isAlive) {
			nCasualties += 1;
		}
	}

	outfile << nCasualties << endl;

	printCommunity(outfile, community1, round);
	printCommunity(outfile, community2, round);

    return 0;
}