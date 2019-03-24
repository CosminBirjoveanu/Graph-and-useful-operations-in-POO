#include <iostream>
#include "nod.h"
using namespace std;

Nod::Nod() {
	dest = 0;
	next = NULL;
}

Nod::Nod(int i, Nod* n) {
	dest = i;
	next = n;
}

void Nod::setInfo(int i) {
    dest = i;
}

void Nod::setNext(Nod* n) {
	next = n;
}

int Nod::getInfo() {
	return dest;
}

Nod* Nod::getNext() {
	return next;
}
