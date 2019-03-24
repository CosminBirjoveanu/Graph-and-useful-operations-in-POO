#include "nod.h"

class Lista {
	Nod *start, *end;
	unsigned int size;
public:
	Lista();
	Lista(int);
	Lista(Lista&);
	Nod* getStart();                        //returneaza primul nod din listsa
	void insert(int);                       //insereaza la finalul listei
	void insertAt(int, unsigned int);       //insereaza la pozitia data
	void insertInOrder(int);                //insereaza elemente in ordine crescatoare
	void print();
	int get(unsigned int);
	unsigned length();
	void remove(unsigned int);
	void removeFirst();
	bool isEmpty();
	~Lista();
};

