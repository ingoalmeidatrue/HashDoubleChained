///////////////////////////////////
///////INGO ROCHA ALMEIDA//////////
///////////////////////////////////
#include "hashdouble.h"

using namespace std;
//////////////////////////////////////////////////////////HASH DUPLO//////////////////////////////////////////////////////
//Toda funcao em hash duplo tem x,z e d como parametros. Tais parametros fazem referencia a:
//x = chave a ser inserida
//z = o resultado da primeira funcao hash
//d =  o resultado da segunda funcao hash
hashd::hashd(int tamanho){
    this->tam = tamanho;
    }
int hashd::mediaarqd(FILE *arq,int x,int z,int d){
    int num = x;
    int pos = z;
    int jump = d;
    save reg,ler;
    int CONTA_ENTRADA_DE_ARQUIVO = 0;
    fseek(arq,sizeof(reg)*(pos),SEEK_SET);
    fread(&ler,sizeof(reg),1,arq);
    CONTA_ENTRADA_DE_ARQUIVO++;
    while(ler.key != -1){
        if(ler.key == num){
            //cont2++;
            break;
        }
        pos += jump;
        if(pos == this->tam){
                pos = 0;
        }
        else if(pos > this->tam){
                int more = pos - this->tam;
                pos = 0 + more;
        }
        fseek(arq,pos*sizeof(reg),SEEK_SET);
        fread(&ler,sizeof(reg),1,arq);
        CONTA_ENTRADA_DE_ARQUIVO++;
    }
    return CONTA_ENTRADA_DE_ARQUIVO;
}
void hashd::openspace(FILE *arq){
    for(int i = 0 ; i<this->tam; i++){
		 save reg ;
		 reg.key =- 1;
		 fwrite(&reg,sizeof(reg),1,arq);
	}
}
void hashd::consultahasd(FILE *arq,int x,int z,int d){
        save reg,ler;
        if(arq == NULL){
            //cout << "o arquivo está nulo e não pode ser consultado" << endl;
            return;
        }
        int num = x;
        int pos = z;
        int deslocamento = d;
            fseek(arq,z*sizeof(reg),SEEK_SET);
            fread(&ler,sizeof(reg),1,arq);
            if(ler.key == num){
                cout << "chave: " <<  num << endl;
                cout << ler.name << endl;
                cout << ler.age << endl;
                return;
            }
            if(ler.key != num){
                    pos+=d;
                    if(pos == this->tam){
                        pos = 0;
                    }
                    else if(pos > this->tam){
                        int more = pos - this->tam;
                        pos = 0 + more;
                    }
                    fseek(arq,pos*sizeof(reg),SEEK_SET);
                    fread(&ler.key,sizeof(reg),1,arq);
                }
            while(pos != z){
                if(ler.key != num){
                    pos+=d;
                    if(pos == this->tam){
                        pos = 0;
                    }
                    else if(pos > this->tam){
                        int more = pos - this->tam;
                        pos = 0 + more;
                    }
                    fseek(arq,pos*sizeof(reg),SEEK_SET);
                    fread(&ler.key,sizeof(reg),1,arq);
                }
                if(ler.key == num){
                cout << "chave: " <<  num << endl;
                cout << ler.name << endl;
                cout << ler.age << endl;
                break;
                }
            }
            fseek(arq,pos*sizeof(reg),SEEK_SET);
            fread(&ler.key,sizeof(reg),1,arq);
            if(ler.key != num){
            cout << "chave nao encontrada: " << num << endl;
            fclose(arq);
            return;
            }
}
bool hashd::verificakeyhasd(FILE *arq,int x,int z,int d){
        save reg,ler;
        if(arq == NULL){
            //cout << "o arquivo está nulo e não pode ser consultado" << endl;
            return false;
        }
        int num = x;
        int pos = z;
        int deslocamento = d;
            fseek(arq,z*sizeof(reg),SEEK_SET);
            fread(&ler,sizeof(reg),1,arq);
            if(ler.key == num){
                cout << "chave ja existente" << endl;
                return true;
            }
            if(ler.key != num){
                    pos+=d;
                    if(pos == this->tam){
                        pos = 0;
                    }
                    else if(pos > this->tam){
                        int more = pos - this->tam;
                        pos = 0 + more;
                    }
                    fseek(arq,pos*sizeof(reg),SEEK_SET);
                    fread(&ler.key,sizeof(reg),1,arq);
            }
            while(pos != z){
                if(ler.key != num){
                    pos+=d;
                    if(pos == this->tam){
                        pos = 0;
                    }
                    else if(pos > this->tam){
                        int more = pos - this->tam;
                        pos = 0 + more;
                    }
                    fseek(arq,pos*sizeof(reg),SEEK_SET);
                    fread(&ler,sizeof(reg),1,arq);
                }
                fseek(arq,pos*sizeof(reg),SEEK_SET);
                fread(&ler,sizeof(reg),1,arq);
                if(ler.key == num){
                cout << "chave ja existente" << endl;
                return true;
                }
            }
            return false;
}
void hashd::removeregistrohashd(FILE *arq,int x,int z,int d){
        save reg,ler,escrev;
        if(arq == NULL){
            //cout << "o arquivo está nulo e não pode ser consultado" << endl;
            return;
        }
        int num = x;
        int pos = z;
        int deslocamento = d;
        escrev.key = -1;
        escrev.age = -1;
        for(int i = 0;i < 20; i++){
            escrev.name[i] = ' ';
        }
            fseek(arq,z*sizeof(reg),SEEK_SET);
            fread(&ler,sizeof(reg),1,arq);
            if(ler.key == num){
                fseek(arq,z*sizeof(reg),SEEK_SET);
                fwrite(&escrev,sizeof(reg),1,arq);
                return;
            }
            if(ler.key != num){
                    pos+=d;
                    if(pos == this->tam){
                        pos = 0;
                    }
                    else if(pos > this->tam){
                        int more = pos - this->tam;
                        pos = 0 + more;
                    }
                    fseek(arq,pos*sizeof(reg),SEEK_SET);
                    fread(&ler.key,sizeof(reg),1,arq);
                }
            while(pos != z){
                if(ler.key != num){
                    pos+=d;
                    if(pos == this->tam){
                        pos = 0;
                    }
                    else if(pos > this->tam){
                        int more = pos - this->tam;
                        pos = 0 + more;
                    }
                    fseek(arq,pos*sizeof(reg),SEEK_SET);
                    fread(&ler,sizeof(reg),1,arq);
                }
                if(ler.key == num){
                fseek(arq,pos*sizeof(reg),SEEK_SET);
                fwrite(&escrev,sizeof(reg),1,arq);
                return;
                }
            }
            cout << "chave nao encontrada: " << num << endl;
            return;
}
void hashd::insereregistrohashd(FILE *arq,int x,int z,int d){
        save reg,ler,escrev;//referencia a struct
        escrev.key = x;
        for(int i = 0;i < 20; i++){
                    escrev.name[i] = ' ';
        }//limpando vetor de char
        getline(cin,lixo);
        string nome; //nome pra ser inserido
        getline(cin,nome);
        for(int i = 0;i < 20; i++){
                    escrev.name[i] = nome[i];
        }//insercao do nome no vetor de char da struct
        int idade;
        cin >> idade;
        escrev.age = idade;//insercao da idade na struct
        if(verificakeyhasd(arq,x,z,d) == false){
        fseek(arq,z*sizeof(reg),SEEK_SET);
        fread(&ler,sizeof(reg),1,arq);
        if(ler.key == -1){
            fseek(arq,z*sizeof(reg),SEEK_SET);
            fwrite(&escrev,sizeof(reg),1,arq);
        }
        else if(ler.key != -1){
            int pos = z;
            fseek(arq,pos*sizeof(reg),SEEK_SET);
            fread(&ler,sizeof(reg),1,arq);
            int cont = 0;
            while(ler.key != -1 and cont <=11){
                pos+=d;
                if(pos == this->tam){
                    pos = 0;
                }
                else if(pos > this->tam){
                    int more = pos - this->tam;
                    pos = 0 + more;
                }
                fseek(arq,pos*sizeof(reg),SEEK_SET);
                fread(&ler,sizeof(reg),1,arq);
                cont++;
            }
            if(ler.key == -1){
                fseek(arq,pos*sizeof(reg),SEEK_SET);
                fwrite(&escrev,sizeof(reg),1,arq);
            }
        }
    }
}
void hashd::imprimehashd(FILE *arq){
    save reg,ler;
    for(int i = 0;i<this->tam;i++){
        fseek(arq,i*sizeof(reg),SEEK_SET);
        fread(&ler,sizeof(reg),1,arq);
        cout << i << ": ";
        if(ler.key == -1){
            cout << "vazio" << endl;
        }
        else{
        cout << ler.key << " " << ler.name << " " << ler.age << endl;
        }
    }
}


