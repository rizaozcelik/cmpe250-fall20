#ifndef ArrayList_H
#define ArrayList_H

class ArrayList {
private:
	int len;
	int* data;
public:
	int adjustSize;
	ArrayList(int adjustSize=10);
	ArrayList(const ArrayList& listToCopy);
	void insert(int val, int idx=0);
	int get(int idx=0);
	int getLength();
	void print();
	ArrayList operator=(const ArrayList& listToAssign);
	~ArrayList();
};

#endif

