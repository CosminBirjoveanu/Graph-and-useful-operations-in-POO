#include <iostream>
#include <stdexcept>
#include "graf.h"
using namespace std;

//constructor fara parametri
Graf::Graf() {
    varf = 0;
    nr_muchii = 0;
    array = NULL;
}
//constructor cu un parametru, numarul de varfuri
Graf::Graf(int v){
    varf = v;
    nr_muchii = 0;
    array = new Lista[v+1];
}
//constructor de copiere
Graf::Graf (const Graf& g) {
    array = new Lista[g.varf + 1];
    for (int i = 1; i <= g.varf; i++) {
        array[i] = g.array[i];
    }
    varf = g.varf;
    nr_muchii = g.nr_muchii;
}
//destructor
Graf::~Graf() {
    varf = 0;
    nr_muchii = 0;
    delete array;
}
//seter pt nr de varfuri
void Graf::setNrVarfuri(int v) {
    varf = v;
}
//seter pentru nr de muchii
void Graf::setNrMuchii(int m) {
    nr_muchii = m;
}
//getter pt nr de varfuri
int Graf::getNrVarfuri() {
    return varf;
}
//getter pt nr de muchii
int Graf::getNrMuchii() {
    return nr_muchii;
}
//getter pt dimensiunea unei liste de adiacenta i
int Graf::getSize(int i) {
    if (i < 1 || i > varf) {
        return 0;
    }
    return array[i].length();
}
//metoda de adaugare de varf la nod
void Graf::adVarf() {
    varf++;
    array = new Lista[varf];
}
/*daca pornirea si destinatia sunt aceleasi, functia
nu se incheie, altfel, aceasta adauga nodul dest
in lista de adiacenta a nodului pornire, si viceversa,
deoarece graful este neorientat
*/
void Graf::adMuchie(int pornire, int dest){
    if (pornire == dest) {
        return;
    }
    array[pornire].insertInOrder(dest);
    array[dest].insertInOrder(pornire);
    nr_muchii++;
}

void Graf::BFS(int rad) {
/*initializam un vector de zerouri pt a verifica ulterior
daca un nod a fost vizitat sau nu.
*/
    int *visited = new int[varf];
/*Declaram o coada in care vom retine vecinii nodului curent, o
initializam cu nodul radacina primit de functie.
*/
    Lista q;
    q.insert(rad);
    for (int i = 1; i <= varf; i++) {
            visited[i] = 0;
    }
    while (!q.isEmpty()) {
/*Cat timp coada nu este goala, nodul radacina devine
cel din varful cozii, si dam pop acelui element din coada.
*/
        rad = q.get(0);
        q.removeFirst();
/*Daca varful curent nu a fost vizitat, il afisam si il marcam
ca vizitat. In continuare declaram un p care sa retina primul element
din lista adiacenta a varfului curent, deoarece vrem sa parcurgem aceasta
lista in cautarea vecinilor nevizitati ai varfului curent.
*/
        if (visited[rad] == 0) {
            cout << rad << " ";
            visited[rad] = 1;
            Nod* p = array[rad].getStart();
            for (unsigned int i = 1; i <= array[rad].length(); i++) {
                if (visited[p->getInfo()] == 0) {
/*Daca vecinul curent nu a fost vizitat, il adaugam
in coada pentru a fi vizitat ulterior
*/
                    q.insert(p->getInfo());
                }
                p = p->getNext();
            }
        }
/*Daca coada e goala, dar mai sunt elemente nevizitate,
inseamna ca graful nu este conex, asa ca inseram primul element
nevizitat in coada si reluam procesul
*/
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
/*Metoda dist foloseste acelasi algoritm ca BFS pentru a
gasi cea mai scurta cale de la nodul dat v1 la nodul dat v2
*/
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
/*For-ul trece prin toti vecinii lui x, ultimul varf preluat din coada,
iar daca gaseste un vecin nevizitat, ii face distanta egala cu cea
de la varful actual + 1, il insereaza in coada pentru a fi vizitat
ulterior si marcheaza nodul curent ca vizitat
*/
        for (unsigned int i = 0; i < array[x].length(); i++) {
            if (visited[array[x].get(i)] == 0) {
                dist[array[x].get(i)] = dist[x] + 1;
                q.insert(array[x].get(i));
                visited [array[x].get(i)] = 1;
            }
        }
    }
/*Distanta minima va fi pana la varful original
de la varful-destinatie va fi dist[v2]
*/
    return dist[v2];
}
/*Metoda verifica este o metoda privata recursiva
folosita de DFS pentru a marca nodurile vizitate si a
se reapela, marcand astfel toti vecinii vecinilor, etc,
in adancime
*/
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
/*DFS initializeaza un vector de zerouri ce marcheaza
daca un nod a fost vizitat inca sau nu
*/
void Graf::DFS(int rad) {
    int *visited = new int[varf];
    for (int i = 1; i <= varf; i++) {
            visited[i] = 0;
    }
    verifica(rad, visited);
/*daca dupa o iteratie completa a metodei verifica
mai sunt noduri nevizitate, inseamna ca graful nu este
conex si DFS apeleaza metoda verifica pentru fiecare
dintre nodurile nevizitate
*/
    for (int i = 1; i <= varf; i++) {
        if (visited[i] == 0) {
            cout << "\n";
            verifica(i, visited);
        }
    }
}
/*Metoda verificaConex este identica cu metoda
verifica, singura diferenta fiind ca verificaConex
nu afiseaza radacina actuala, ci doar le parcurge
pe aceasta si pe vecinele sale
*/
void Graf::verificaConex(int rad, int visited[]) {
    if (visited[rad] == 0) {
        visited[rad] = 1;
    }
    Nod *p = array[rad].getStart();
    for (unsigned int i = 1; i <= array[rad].length(); i++) {
        if (visited[p->getInfo()] == 0)
            verifica(p->getInfo(), visited);
        p = p->getNext();
    }
}
/*Metoda compConexe afiseaza numarul de componente conexe
cu ajutorul metodei verificaConex, contorizand fiecare
iteratie a acesteia prin fiecare componenta conexa
*/
int Graf::compConexe() {
    int *visited = new int[varf];
    int k = 0;
    for (int i = 1; i <= varf; i++) {
            visited[i] = 0;
    }
    for (int i = 1; i <= varf; i++) {
        if (visited[i] == 0) {
            verificaConex(i, visited);
            k++;
        }
    }
    return k;
}
/*Metoda verifCiclio verifica daca un graf dat este ciclic.
Aceasta foloseste un algoritm asemanator cu verifica, incercand
sa marcheze toate nodurile prin care a trecut.
Daca acesta gaseste la vreun moment de parcurgere un nod
care nu este direct parinte, dar a fost vizitat, ajunge la concluzia
ca graful este ciclic si returneaza true
*/
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
/*Metoda eArbore utilizeaza metoda privata verifCiclic ca
sa verifice daca un graf este arbore. Un graf este arbore
doar daca nu contine cicluri si este graf conex.
Asa ca metoda cauta de asemenea alte componente conexe,
date de gol de noduri ce nu ar fi fost vizitate anterior.
Daca metoda nu gaseste astfel de varfuri, returneaza true.
*/
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
/*Metoda operator[] supraincarca operatorul [],
returnand un vector ce contine lista de adiacenta
a nodului i cand este apelat.
Daca nodul i nu exista metoda intoarce o exceptie.
Daca nodui i exista atunci metoda creeaza un vector
in care va pune lista de adiacenta a acestuia,
apoi il returneaza printr-un pointer la primul element
*/
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
/*Metoda aceasta supraincarca operatorul < ,
astfel incat daca primul graf primit ca parametru
are mai putine varfuri decat al doilea graf primit
ca parametru atunci returneaza true, daca cele doua
grafuri au numar egal de noduri se verifica daca
primul graf are mai putine muchii decat cel de-al
doilea graf, iar daca are mai putine muchii returneaza
true, altfel returneaza false;
*/
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
/*Viceversa ca la operator<*/
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
/*Metoda operator>> supraincarca operatia
de citire, facand posibila citirea "directa"
a grafurilor. Intai aceasta dezaloca ce era
inainte in graf, ca sa aloce noile muchii.
Se introduc de la tastatura nr de varfuri si
de muchii, apoi muchiile, intai in 2 variabile
auxiliare a si b, folosite apoi in metoda
adMuchie pentru a adauga muchia in graf.
La final se scade nr de muchii pentru ca adMuchie
adauga de la sine + 1 la nr de muchii si se intra
astfel intr-o ciclare infinita.
Se returneaza un flux de date de intrare in.
*/
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

/*Metoda operator<< parcurge fiecare lista de
adiacenta si le atribuie fluxului de date de iesire.
Apoi se returneaza fluxul respectiv de date.
*/
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

/*Metoda operator= dezaloca ce aveam anterior in
graful a carui membru este apoi atribuie
elementelor din acel graf elementele din graful
primit ca parametru. Apoi aloca si copie fiecare
lista de adiacenta din graful primit ca parametru
in graful curent si se returneaza valoarea acestuia.
*/
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
