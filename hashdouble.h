#ifndef HASHDOUBLE_H_INCLUDED
#define HASHDOUBLE_H_INCLUDED
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iomanip>

using namespace std;

class hashd{
public:
    struct save{
        int key;
        char name[20];
        int age;
    };
    hashd(int a);
    int tam;
    save ler;
    string lixo;
    int funch1(int a,int b);
    int funch2(int a,int b);
    int mediaarqd(FILE *arq,int x,int z,int d);
    void openspace(FILE *arq);
    void consultahasd(FILE *arq,int x,int z,int d);
    bool verificakeyhasd(FILE *arq,int x,int z,int d);
    void removeregistrohashd(FILE *arq,int x,int z,int d);
    void insereregistrohashd(FILE *arq,int x,int z,int d);
    void imprimehashd(FILE *arq);
};

#endif // HASHDOUBLE_H_INCLUDED
