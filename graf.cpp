#include <iostream>
#include <stdexcept>
#include "graf.h"
using namespace std;

Graf::Graf() {
    varf = 0;
    nr_muchii = 0;
    array = NULL;
}

Graf::Graf(int v){
    varf = v;
    nr_muchii = 0;
    array = new Lista[v+1];
}

Graf::Graf (const Graf& g) {
    array = new Lista[g.varf + 1];
    for (int i = 1; i <= g.varf; i++) {
        array[i] = g.array[i];
    }
    varf = g.varf;
    nr_muchii = g.nr_muchii;
}

Graf::~Graf() {
    varf = 0;
    nr_muchii = 0;
    delete array;
}

void Graf::setNrVarfuri(int v) {
    varf = v;
}

void Graf::setNrMuchii(int m) {
    nr_muchii = m;
}

int Graf::getNrVarfuri() {
    return varf;
}

int Graf::getNrMuchii() {
    return nr_muchii;
}

int Graf::getSize(int i) {
    if (i < 1 || i > varf) {
        return 0;
    }
    return array[i].length();
}

void Graf::adVarf() {
    varf++;
    array = new Lista[varf];
}

void Graf::adMuchie(int pornire, int dest){
    if (pornire == dest) {
        return;
    }
    array[pornire].insertInOrder(dest);
    array[dest].insertInOrder(pornire);
    nr_muchii++;
}

void Graf::BFS(int rad) {
    int *visited = new int[varf];
    Lista q;
    q.insert(rad);
    for (int i = 1; i <= varf; i++) {
            visited[i] = 0;
    }
    while (!q.isEmpty()) {
        rad = q.get(0);
        q.removeFirst();
        if (visited[rad] == 0) {
            cout << rad << " ";
            visited[rad] = 1;
            Nod* p = array[rad].getStart();
            for (unsigned int i = 1; i <= array[rad].length(); i++) {
                if (visited[p->getInfo()] == 0) {
                    q.insert(p->getInfo());
                }
                p = p->getNext();
            }
        }
        if (q.isEmpty()) {
            for (int i = 1; i <= varf; i++) {
                if (visited[i] == 0) {
                    cout << "\n";
                    q.insert(i);
                    break;
                }
            }
        }
    }
}

int Graf::dist(int v1, int v2) {
    int *visited = new int[varf];
    int *dist = new int[varf];
    Lista q;
    q.insert(v1);
    for (int i = 1; i <= varf; i++) {
            visited[i] = 0;
            dist[i] = 0;
    }
    visited[v1] = 1;
    while (!q.isEmpty()) {
        int x = q.get(0);
        q.removeFirst();
        for (unsigned int i = 0; i < array[x].length(); i++) {
            if (visited[array[x].get(i)] == 0) {
                dist[array[x].get(i)] = dist[x] + 1;
                q.insert(array[x].get(i));
                visited [array[x].get(i)] = 1;
            }
        }
    }
    return dist[v2];
}

void Graf::verifica(int rad, int visited[]) {
    if (visited[rad] == 0) {
        cout << rad << " ";
        visited[rad] = 1;
    }
    Nod *p = array[rad].getStart();
    for (unsigned int i = 1; i <= array[rad].length(); i++) {
        if (visited[p->getInfo()] == 0)
            verifica(p->getInfo(), visited);
        p = p->getNext();
    }
}

void Graf::DFS(int rad) {
    int *visited = new int[varf];
    for (int i = 1; i <= varf; i++) {
            visited[i] = 0;
    }
    verifica(rad, visited);
    for (int i = 1; i <= varf; i++) {
        if (visited[i] == 0) {
            cout << "\n";
            verifica(i, visited);
        }
    }
}

void Graf::compConexe() {
    int *visited = new int[varf];
    for (int i = 1; i <= varf; i++) {
            visited[i] = 0;
    }
    for (int i = 1; i <= varf; i++) {
        if (visited[i] == 0) {
            verifica(i, visited);
            cout << "\n";
        }
    }
}

int Graf::verifCiclic(int rad, int visited[], int tata) {
    visited[rad] = 1;
    Nod *p = array[rad].getStart();
    for (unsigned int i = 1; i <= array[rad].length(); i++) {
        if (visited[p->getInfo()] == 0) {
            if (verifCiclic(p->getInfo(), visited, rad) == 1) {
                return 1;
            }
        }
        else if (p->getInfo() != tata) {
            return 1;
        }
        p = p->getNext();
    }
    return 0;
}

int Graf::eArbore() {
    int *visited = new int[varf];
    for (int i = 1; i <= varf; i++) {
            visited[i] = 0;
    }
    if (verifCiclic(1, visited, -1) == 1) {
        return 0;
    }
    for (int i = 1; i <= varf; i++) {
        if (visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int* Graf::operator[](int i) {
    if (i < 1 || i > varf) {
        std::invalid_argument e("Index invalid");
        throw e;
    }
    static int* vector = new int[array[i].length()];
    Nod *p = array[i].getStart();
    for (unsigned int j = 0; j < array[i].length(); j++) {
        vector[j] = p->getInfo();
        p = p->getNext();
    }
    return vector;
}

int operator<(Graf g1, Graf g2) {
    if (g1.getNrVarfuri() < g2.getNrVarfuri()) {
        return 1;
    }
    if (g1.getNrVarfuri() == g2.getNrVarfuri()) {
        if (g1.getNrMuchii() < g2.getNrMuchii()) {
            return 1;
        }
    }
    return 0;
}

int operator>(Graf g1, Graf g2) {
    if (g1.getNrVarfuri() > g2.getNrVarfuri()) {
        return 1;
    }
    if (g1.getNrVarfuri() == g2.getNrVarfuri()) {
        if (g1.getNrMuchii() > g2.getNrMuchii()) {
            return 1;
        }
    }
    return 0;
}

istream& operator>>(istream &in, Graf &g) {
    int a, b;
    for (int i = 1; i <= g.varf; i++) {
        delete g[i];
    }
    cout << "Introdu nr de varfuri si de muchii:\n";
    in >> g.varf >> g.nr_muchii;
    g.array = new Lista[g.varf + 1];
    cout << "Introdu muchiile:\n";
    for (int i = 0; i < g.nr_muchii; i++) {
        in >> a >> b;
        g.adMuchie(a, b);
        g.nr_muchii--;
    }
    return in;
}


ostream& operator<<(ostream &out, Graf &g) {
    for (int i = 1; i <= g.varf; i++) {
        Nod* parcurgere = g.array[i].getStart();
        out << "\nLista de adiacenta cu varful " << i << ":\n" << i;
        while (parcurgere != NULL){
            out << "->" << parcurgere->getInfo();
            parcurgere = parcurgere->getNext();
        }
        out << "\n";
    }
    return out;
}

Graf& Graf::operator= (const Graf& g) {
    delete this->array;
    this->varf = g.varf;
    this->nr_muchii = g.nr_muchii;
    this->array = new Lista[this->varf + 1];
    for (int i = 1; i <= this->varf; i++) {
        array[i] = g.array[i];
    }
    return *this;


}
