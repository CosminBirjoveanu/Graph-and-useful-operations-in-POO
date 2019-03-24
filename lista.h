#include "nod.h"

class Lista {
	Nod *start, *end;
	unsigned int size;
public:
	Lista();
	Lista(int);
	Lista(Lista&);
	Nod* getStart();
	void insert(int);
	void insertAt(int, unsigned int);
	void insertInOrder(int);
	void print();
	int get(unsigned int);
	unsigned length();
	void remove(unsigned int);
	void removeFirst();
	bool isEmpty();
	~Lista();
};

