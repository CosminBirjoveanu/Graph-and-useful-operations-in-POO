#include "lista.h"

class Graf{
    int varf, nr_muchii;                    //varf = numarul de varfuri
    Lista *array;                           //vector de liste de adiacenta
    void verifica(int, int[]);              //functie recursiva folosita de DFS pt a verifica daca un varf a fost vizitat
    void verificaConex(int, int[]);
    int verifCiclic(int, int[], int);       //verifica daca graful este ciclic
public:
    Graf();
    Graf(int);
    Graf(const Graf&);                      //constructor de copiere
    ~Graf();
    void setNrVarfuri(int);
    void setNrMuchii(int);
    int getNrVarfuri();
    int getNrMuchii();
    int getSize(int);                       //in cazul in care graful a fost initializat prin constructorul
    void adVarf();                          //fara parametri aceasta functie ii adauga un varf
    void adMuchie(int , int);
    int compConexe();                      //afiseaza pe ecran numarul de componente conexe
    void BFS(int);
    int dist(int, int);                     //intoarce distanta minima dintre 2 varfuri date
    void DFS(int rad);
    int eArbore();
    int* operator[](int);
    friend int operator< (Graf, Graf);      //functiile prieten usureaza utilizarea parametrilor privati din clasa
    friend int operator> (Graf, Graf);
    friend std::istream &operator>> (std::istream &, Graf &);
    friend std::ostream &operator<< (std::ostream &, Graf&);
    Graf& operator= (const Graf&);
};
