#include <iostream>
#include "lista.h"
using namespace std;

Lista::Lista() {
	start = end = NULL;
	size = 0;
}

Lista::Lista(int x) {
	start = end = new Nod(x, NULL);
	size = 1;
}

Lista::Lista(Lista& l) {
	start = end = NULL;
	size = 0;
	Nod* p = l.start;
	while (p != NULL) {
		insert(p->getInfo());
		p = p->getNext();
	}
}

Nod* Lista::getStart() {
    return start;
}

void Lista::insert(int x) {
	insertAt(x, size + 1);
}

void Lista::print() {
	Nod *p = start;
	while (p != NULL) {
		cout << p->getInfo() << " ";
		p = p->getNext();
	}
	cout << std::endl;
}

void Lista::insertInOrder(int x) {
    if (start == NULL) {
		start = end = new Nod(x, NULL);
		size = 1;
		return;
	}
    Nod* p = start;
    while (p != NULL && x > p->getInfo()) {
        p = p->getNext();
    }
    if (p == NULL) {
        Nod* o = new Nod(x, NULL);
        end->setNext(o);
        end = o;
        size++;
        return;
    }
    if (x == p->getInfo()) {
        return;
    }
    if (p == start) {
        Nod* o = new Nod(x, start);
        start = o;
        size++;
        return;
    }
    Nod *aux = start;
    while (aux->getNext() != p) {
        aux = aux->getNext();
    }
    Nod *o = new Nod(x, p);
    aux->setNext(o);
    end->setNext(NULL);
    size++;
}

void Lista::insertAt(int x, unsigned int i) {
	if (start == NULL) {
		start = end = new Nod(x, NULL);
		size = 1;
		return;
	}
	Nod* p = new Nod(x, NULL);
	if (i == 0) {
		p->setNext(start);
		start = p;
		size++;
		return;
	}
	if (i < 0 || i >= size) {
		end->setNext(p);
		end = p;
		size++;
		return;
	}
	Nod* o = start;
	for (int j = i; j > 1; j--) {
		o = o->getNext();
	}
	p->setNext(o->getNext());
	o->setNext(p);
	size++;
}

int Lista::get(unsigned int i) {
	if (i < 0 || i >= size) {
		return INT_MAX;
	}
	Nod* p = start;
	for (int j = i; j > 0; j--) {
		p = p->getNext();
	}
	return p->getInfo();
}

unsigned Lista::length() {
	return size;
}

void Lista::remove(unsigned int i) {
	if (i < 0 || i >= size) {
		return;
	}
	Nod* p = start;
	if (i == 0) {
		if (size == 1 || size == 0) {
			end = start = NULL;
		}
		else {
			start = start->getNext();
			delete p;
		}
	}
	else {
		for (int j = i; j > 1; j--) {
			p = p->getNext();
		}
		Nod* o = p->getNext();
		p->setNext(o->getNext());
		delete o;
	}
	size--;
}

Lista::~Lista()
{
	Nod *p = start, *o;
	while (p != NULL) {
		o = p;
		p = p->getNext();
		delete o;
	}
	start = end = NULL;
	size = 0;
}

void Lista::removeFirst() {
	remove(0);
}

bool Lista::isEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
}
