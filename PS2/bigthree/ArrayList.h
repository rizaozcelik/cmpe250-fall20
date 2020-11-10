#include <string>
using namespace std;

#ifndef ArrayList_H
#define ArrayList_H

class ArrayList {
private:
	static int nCreatedInstance;
	int len;
	int* data = NULL;
public:
	int id, adjustSize;
	ArrayList(int adjustSize=10);
	ArrayList(const ArrayList& listToCopy);
	void insert(int val, int idx=0);
	int get(int idx=0);
	int getLength();
	void print();
	ArrayList& operator=(const ArrayList& listToAssign);
	~ArrayList();
};

#endif

