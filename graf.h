#include "lista.h"

class Graf{
    int varf, nr_muchii;
    Lista *array;
    void verifica(int rad, int visited[]);
public:
    Graf();
    Graf(int);
    Graf(const Graf&);
    ~Graf();
    void setNrVarfuri(int);
    void setNrMuchii(int);
    int getNrVarfuri();
    int getNrMuchii();
    int getSize(int);
    void adVarf();
    void adMuchie(int , int);
    void compConexe();
    void BFS(int);
    int dist(int, int);
    void DFS(int rad);
    int verifCiclic(int, int[], int);
    int eArbore();
    int* operator[](int);
    friend int operator< (Graf, Graf);
    friend int operator> (Graf, Graf);
    friend std::istream &operator>> (std::istream &, Graf &);
    friend std::ostream &operator<< (std::ostream &, Graf&);
    Graf& operator= (const Graf&);
};
