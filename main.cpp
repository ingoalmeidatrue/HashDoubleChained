#include "hash.h"
#include "hashdouble.h"
#include "hashencadeado.h"


using namespace std;

int TAMANHO_ARQUIVO = 11;
float CONTA_ENTRADA_DE_ARQUIVO = 0;
float CONTA_CHAMADA_FUNCAO = 0;
//contador do hash douhle
int cont2 = 0;
//contador do hash encadeado
int cont3 = 0;

//funcao de hash "normal" (a primeira funcao de hash a ser feita pra toda e qualquer chave)
int Hash::funch1(int a,int b){
    int x;
    x = a%b;
    return x;
}

//funcao de hash secundária (utilizada somente em hash duplo)
int Hash::funch2(int a,int b){
    int x;
    x = floor(a/b);
    if(x == 0){
        return 1;
    }
    if(x%b == 0){
        return 1;
    }
return x%b;
}
int main(){
    FILE* arq;
    char entrada;
    cin >> entrada;
    if(entrada == 'l'){
        Hash h;
        hashe e(TAMANHO_ARQUIVO);
            char entradaesp;
            cin >> entradaesp;
            while(entradaesp != 'e'){
                if(entradaesp == 'i'){
                        arq = fopen("testehash.dat","rb+");
                        if(arq == NULL){
                        fclose(arq);
                        arq = fopen("testehash.dat","wb+");
                        e.openspace2(arq);
                        int num;
                        cin >> num;
                        int resto = h.funch1(num,TAMANHO_ARQUIVO);
                        e.insereregistrohashe(arq,num,resto);
                        fclose(arq);
                        }
                        else if(arq != NULL){
                        fclose(arq);
                        arq = fopen("testehash.dat","rb+");
                        int num;
                        cin >> num;
                        int resto = h.funch1(num,TAMANHO_ARQUIVO);
                        e.insereregistrohashe(arq,num,resto);
                        fclose(arq);
                        }
                }
                if(entradaesp == 'c'){
                    arq = fopen("testehash.dat","rb+");
                    int num;
                    cin >> num;
                    int resto = h.funch1(num,TAMANHO_ARQUIVO);
                    e.consultahase(arq,num,resto);
                    fclose(arq);
                }
                if(entradaesp == 'r'){
                    arq = fopen("testehash.dat","rb+");
                    int num;
                    cin >> num;
                    int resto = h.funch1(num,TAMANHO_ARQUIVO);
                    e.removeregistrohashe(arq,num,resto);
                    fclose(arq);
                }
                if(entradaesp == 'p'){
                    arq = fopen("testehash.dat","rb+");
                    e.imprimehashe(arq);
                    fclose(arq);
                }
                if(entradaesp == 'm'){
                    //save2 reg,ler;
                    float CONTA_CHAMADA_FUNCAO = 0;
                    arq = fopen("testehash.dat","rb+");
                    for(int i = 0;i<TAMANHO_ARQUIVO;i++){
                        fseek(arq,(i)*sizeof(hashe::save2),SEEK_SET);
                        fread(&e.ler,sizeof(hashe::save2),1,arq);
                        if(e.ler.key != -1){
                            cont3++;
                            int resto = h.funch1(e.ler.key,TAMANHO_ARQUIVO);
                            CONTA_CHAMADA_FUNCAO += e.mediaarqe(arq,e.ler.key,resto);
                            CONTA_ENTRADA_DE_ARQUIVO = 0;
                        }
                    }
                    cout << fixed << setprecision(1) << CONTA_CHAMADA_FUNCAO/cont3 << endl;
                    cont3 = 0;
                    fclose(arq);
                }
                cin >> entradaesp;
            }
    }
    if(entrada == 'd'){

        Hash h;
        hashd d(TAMANHO_ARQUIVO);

        char entradaesp;
        cin >> entradaesp;
        while(entradaesp != 'e'){
            if(entradaesp == 'i'){
                    arq = fopen("testehash2.dat","rb+");
                    if(arq == NULL){
                    fclose(arq);
                    arq = fopen("testehash2.dat","wb+");
                    d.openspace(arq);
                    int num;
                    cin >> num;
                    int resto = h.funch1(num,TAMANHO_ARQUIVO);
                    int deslocamento = h.funch2(num,TAMANHO_ARQUIVO);
                    d.insereregistrohashd(arq,num,resto,deslocamento);
                    fclose(arq);
                    }
                    else if(arq != NULL){
                    fclose(arq);
                    arq = fopen("testehash2.dat","rb+");
                    int num;
                    cin >> num;
                    int resto = h.funch1(num,TAMANHO_ARQUIVO);
                    int deslocamento = h.funch2(num,TAMANHO_ARQUIVO);
                    d.insereregistrohashd(arq,num,resto,deslocamento);
                    fclose(arq);
                    }
            }
            if(entradaesp == 'c'){
                arq = fopen("testehash2.dat","rb+");
                int num;
                cin >> num;
                int resto = h.funch1(num,TAMANHO_ARQUIVO);
                int deslocamento = h.funch2(num,TAMANHO_ARQUIVO);
                d.consultahasd(arq,num,resto,deslocamento);
                fclose(arq);
            }
            if(entradaesp == 'r'){
                arq = fopen("testehash2.dat","rb+");
                int num;
                cin >> num;
                int resto = h.funch1(num,TAMANHO_ARQUIVO);
                int deslocamento = h.funch2(num,TAMANHO_ARQUIVO);
                d.removeregistrohashd(arq,num,resto,deslocamento);
                fclose(arq);
            }
            if(entradaesp == 'p'){
                arq = fopen("testehash2.dat","rb+");
                d.imprimehashd(arq);
                fclose(arq);
            }
            if(entradaesp == 'm'){
            //save reg,ler;
            float CONTA_CHAMADA_FUNCAO = 0;
            arq = fopen("testehash2.dat","rb+");
                for(int i = 0;i<TAMANHO_ARQUIVO;i++){
                    fseek(arq,(i)*sizeof(hashd::save),SEEK_SET);
                    fread(&d.ler,sizeof(hashd::save),1,arq);
                    if(d.ler.key != -1){
                        cont2++;
                        int resto = h.funch1(d.ler.key,TAMANHO_ARQUIVO);
                        int deslocamento = h.funch2(d.ler.key,TAMANHO_ARQUIVO);
                        CONTA_CHAMADA_FUNCAO += d.mediaarqd(arq,d.ler.key,resto,deslocamento);
                        CONTA_ENTRADA_DE_ARQUIVO = 1;
                    }
                }
                cout << fixed << setprecision(1) << CONTA_CHAMADA_FUNCAO/cont2 << endl;
                cont2 = 0;
                fclose(arq);
            }
            cin >> entradaesp;
        }
    }
}
