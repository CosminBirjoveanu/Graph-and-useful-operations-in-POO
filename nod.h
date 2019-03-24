
class Nod {
	int dest;
	Nod *next;
public:
	Nod();
	Nod(int, Nod*);
	void setInfo(int);
	void setNext(Nod*);
	int getInfo();
	Nod* getNext();
};
