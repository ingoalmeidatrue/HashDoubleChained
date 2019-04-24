#ifndef HASHENCADEADO_H_INCLUDED
#define HASHENCADEADO_H_INCLUDED
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
using namespace std;
class hashe{
public:
    struct save2{
    int key;
    char name[20];
    int age;
    int pont;
};
    hashe(int a);
    int tam;
    string lixo;
    save2 ler;
    int funch1(int a,int b);
    int mediaarqe(FILE *arq,int x,int z);
    void openspace2(FILE *arq);
    void consultahase(FILE *arq,int x,int z);
    bool verificakeyhase(FILE *arq,int x,int z);
    void removeregistrohashe(FILE *arq,int x,int z);
    void insereregistrohashe(FILE *arq,int x,int z);
    void imprimehashe(FILE *arq);
};

#endif // HASHENCADEADO_H_INCLUDED
