///////////////////////////////////
///////INGO ROCHA ALMEIDA//////////
///////////////////////////////////
#include "hashencadeado.h"

using namespace std;
////////////////////////////////////////////////////////////////////// HASH ENCADEADO /////////////////////////////////////////////////////////////
//Toda fun��o (tirando a de abertura de arquivo e a de impressao) em hash encadeado tem x e z como parametros. Tais parametros fazem refer�ncia a:
//x = chave a ser inserida
//z = o resultado da primeira funcao hash

//Fun��o que realiza a m�dia de acessos ao arquivo
hashe::hashe(int tamanho){
    this->tam = tamanho;
    }
int hashe::mediaarqe(FILE *arq,int x,int z){
    int num = x;
    int pos = z;
    int CONTA_ENTRADA_DE_ARQUIVO = 0;
    save2 reg,ler;
    fseek(arq,z*sizeof(reg),SEEK_SET);
    fread(&ler,sizeof(reg),1,arq);
    CONTA_ENTRADA_DE_ARQUIVO++;//toda vez que possui um fread na funcao � preciso aumentar o contador de entrada de arquivo
    while(ler.key != -1){
        if(ler.key == num){//Quando for igual pare porque j� achei a quantidade certa de vezes de entrada no arquivo
            break;
        }
        if(num != ler.key and ler.pont != -2){
            while(num != ler.key and ler.pont != -2){//procurando na lista de ponteiros do numero
            pos = ler.pont;
            fseek(arq,pos*sizeof(reg),SEEK_SET);
            fread(&ler,sizeof(reg),1,arq);
            CONTA_ENTRADA_DE_ARQUIVO++;
            }
            if(ler.key != num){
            }
            else if(ler.key == num){
                    break;
            }
        }
    }
    return CONTA_ENTRADA_DE_ARQUIVO;
}
//fun��o para abertura de espa�os no arquivo
void hashe::openspace2(FILE *arq){
    for(int i = 0 ; i<this->tam; i++){
		 save2 reg;
		 reg.pont = -2;
		 reg.key = -1;
		 fwrite(&reg,sizeof(reg),1,arq);
	}
}
//fun��o para verificar se um n�mero j� est� presente dentro do hash
bool hashe::verificakeyhase(FILE *arq,int x,int z){
     if(arq == NULL){
            //cout << "o arquivo est� nulo e n�o pode ser consultado" << endl;
            return false;
    }
    save2 ler,reg;
    int num = x;
    int pos = z;
    fseek(arq,z*sizeof(reg),SEEK_SET);
    fread(&ler,sizeof(reg),1,arq);
    //int verf = funch1(ler.key,this->tam);
    if(num == ler.key){//a chave bate na posicao certo, logo j� existe no hash
        cout << "chave ja existente" << endl;
        return true;
    }
    else if(num != ler.key and ler.pont == -2){//a chave presente na posi��o inicial � diferente de num e o ponteiro aponta pra nada, ent�o o num procurado n�o existe no hash
				return false;
    }
	else if(num != ler.key and ler.pont != -2){//a chave presente na posi��o inicial � diferente de num e o ponteiro � n�o nulo, ent�o o num procurado pode existir no hash
            while(num != ler.key and ler.pont != -2){//percorrendo a lista de ponteiros para tentar achar o numero desejado
            pos = ler.pont;
            fseek(arq,pos*sizeof(reg),SEEK_SET);
            fread(&ler,sizeof(reg),1,arq);
            }
            fseek(arq,pos*sizeof(reg),SEEK_SET);
            fread(&ler,sizeof(reg),1,arq);
                if(num == ler.key){//finalmente achei o num
                cout << "chave ja existente" << endl;
                    return true;
                }
                else if(num != ler.key){//n�o achei o num
                    return false;
                }
    }
}
//fun��o para inserir um registro do hash
void hashe::insereregistrohashe(FILE *arq,int x,int z){
        save2 reg,ler,escrev,before,mudado;
        save2 leitura,anterior,escrita;
        int num = x;
        escrev.key = x;//setando a chave a ser inserida
        for(int i = 0;i < 20; i++){//limpando o vetor de nome na struct
                escrev.name[i] = ' ';
        }
        getline(cin,lixo);
        string nome;
        getline(cin,nome);
        for(int i = 0;i < 20; i++){//passando o nome para o vetor de nome na struct
                escrev.name[i] = nome[i];
        }
        int idade;
        cin >> idade;
        escrev.age = idade;//setando a idade
        escrev.pont = -2;//setando o ponteiro para qual ele aponta
        if(verificakeyhase(arq,x,z) == false){
        int start = z;
        int pos = z;
        int modatual = z;
        int posicaotroca = this->tam - 1;
        int newpos = this->tam-1;
        int posatras = this->tam -1;
        int aux = this->tam;
        fseek(arq,z*sizeof(reg),SEEK_SET);
        fread(&ler,sizeof(reg),1,arq);
        int teste = ler.key%this->tam;
        if(ler.key == -1){//a posi��o inicial n�o tem n�mero, ent�o posso escrever nela direto
            fseek(arq,z*sizeof(reg),SEEK_SET);
            fwrite(&escrev,sizeof(reg),1,arq);
        }
       else if(teste != z and ler.key != -1){//existe uma lista e o mod eh diferente
                        while(ler.key != -1 and aux>0){//achando a nova posicao a ser inserida
                                    fseek(arq,newpos*sizeof(reg),SEEK_SET);
                                    fread(&ler,sizeof(reg),1,arq);
                                    if(ler.key!=-1)newpos--;
                                    aux--;
                        }
						//cout<<"newpos :"<<newpos<<endl;
						fseek(arq,(newpos)*sizeof(reg),SEEK_SET);
						fread(&ler,sizeof(reg),1,arq);
						if(ler.key == -1){
                            fseek(arq,start*sizeof(reg),SEEK_SET);
                            fread(&mudado,sizeof(reg),1,arq);//salvando o registro que ser� mudado de lugar
							int pontehash = mudado.key%this->tam;//achando o mod do registro que estava no local errado para encaixar na posi��o correta
							fseek(arq,pontehash*sizeof(reg),SEEK_SET);
							fread(&ler,sizeof(reg),1,arq);
							int prepos=pontehash;
                            while(pontehash!= start){//while para achar a nova posi��o do registro antigo
                                fseek(arq,(prepos)*sizeof(reg),SEEK_SET);
                                fread(&before,sizeof(reg),1,arq);
                                fseek(arq,(pontehash)*sizeof(reg),SEEK_SET);
                                fread(&ler,sizeof(reg),1,arq);
                                if(pontehash!=start){
                                    prepos = pontehash;//achando a posicao do registro antigo
                                    pontehash=ler.pont;
                                }
                            }
                            if(pontehash == start){//encontrei um espa�o vazio
                                fseek(arq,z*sizeof(reg),SEEK_SET);
                                fwrite(&escrev,sizeof(reg),1,arq);//escrevendo o registro desejado na posicao que ele deve ser inserido no hash
                                fseek(arq,(newpos)*sizeof(reg),SEEK_SET);//deslocando para a posicao que o registro antigo ser� colocado
                                fwrite(&mudado,sizeof(reg),1,arq);//escrevendo o antigo registro no lugar certo
                                fseek(arq,(prepos)*sizeof(reg),SEEK_SET);
                                fread(&before,sizeof(reg),1,arq);
                                before.pont = newpos;//alterando o ponteiro do registro antes de escrever
                                fseek(arq,(prepos)*sizeof(reg),SEEK_SET);
                                fwrite(&before,sizeof(reg),1,arq);//escrevendo o registro agora com o ponteiro alterado para a posicao que o antigo registro foi trocado
                            }
                        }
        }
        else if(ler.key != -1 and ler.pont == -2 and teste == z){//tenho numero no local mas nao tenho lista de ponteiros.A lista presente no local � do mesmo mod ent�o vou inserir na ultima posicao vazia e encadear o ponteiro pra ela
                        fseek(arq,pos*sizeof(reg),SEEK_SET);
                        fread(&before,sizeof(reg),1,arq);//salvando a primeira posi��o que colide
                        fseek(arq,posatras*sizeof(reg),SEEK_SET);
                        fread(&ler,sizeof(reg),1,arq);
                        while(ler.key != -1 and posatras >= 0){//lendo de tr�s pra frente enquanto procuro posi��es
                            posatras--;
                            fseek(arq,posatras*sizeof(reg),SEEK_SET);
                            fread(&ler,sizeof(reg),1,arq);
                        }
                        if(ler.key == -1){//achei uma posi��o que posso inserir
                            before.pont = posatras;//apontando o ponteiro da primeira posi��o para a que acabei de achar
                            fseek(arq,posatras*sizeof(reg),SEEK_SET);//indo para a posi��o que acabei de achar
                            fwrite(&escrev,sizeof(reg),1,arq);//salvando o novo registro na nova posi��o
                            fseek(arq,start*sizeof(reg),SEEK_SET);
                            fwrite(&before,sizeof(reg),1,arq);//escrevendo o registro da primeira posi��o que colide agora com o ponteiro alterado
                            //fseek(arq,posatras*sizeof(reg),SEEK_SET);//indo para a posi��o que acabei de achar
                            //fwrite(&escrev,sizeof(reg),1,arq);//salvando o novo registro na nova posi��o
                        }
            }
        //existe uma lista
        else if(ler.key != -1 and ler.pont != -2 and teste == z){//tenho numero no local mas tenho lista de ponteiros.A lista presente no local � do mesmo mod ent�o vou inserir na ultima posicao vazia e encadear o ponteiro pra ela
                //existe uma lista e o mod eh o mesmo
                pos = ler.pont;
                fseek(arq,pos*sizeof(reg),SEEK_SET);
				fread(&before,sizeof(reg),1,arq);//salvando a primeira posi��o que colide
				while(start != pos and before.pont != -2){//procurando a ultima posicao da lista de ponteiros
                    pos = before.pont;
                    fseek(arq,pos*sizeof(reg),SEEK_SET);
                    fread(&before,sizeof(reg),1,arq);
				}
                int posa = pos;//posicao marcando o ultimo numero da lista
                    while(ler.key != -1 and pos >= 0){//achando novo local de inser��o
                        posicaotroca--;
                        fseek(arq,posicaotroca*sizeof(reg),SEEK_SET);
                        fread(&ler,sizeof(reg),1,arq);
                    }
                    //fseek(arq,posicaotroca*sizeof(reg),SEEK_SET);
                    //fread(&ler,sizeof(reg),1,arq);
                    if(ler.key == -1){//verificando se o local est� dispon�vel
                    before.pont = posicaotroca;//apontando o ponteiro da primeira posi��o para a que acabei de achar
                    fseek(arq,posicaotroca*sizeof(reg),SEEK_SET);//indo para a posi��o que acabei de achar
                    fwrite(&escrev,sizeof(reg),1,arq);//salvando o novo registro na nova posi��o
                    fseek(arq,posa*sizeof(reg),SEEK_SET);
                    fwrite(&before,sizeof(reg),1,arq);//escrevendo o registro da primeira posi��o que colide agora com o ponteiro alterado
                    }
				}
    }
}
//fun��o para consultar se um registro est� presente no hash
void hashe::consultahase(FILE *arq,int x,int z){
    int start = z;
    int pos = z;
    int num = x;
    save2 reg,ler;
    fseek(arq,z*sizeof(reg),SEEK_SET);
    fread(&ler,sizeof(reg),1,arq);
    //int verf = funch1(ler.key,this->tam);
    if(num == ler.key){//achei meu n�mero na posi��o correta basta imprimir
        cout << "chave: " <<  num << endl;
        cout << ler.name << endl;
        cout << ler.age << endl;
    }
    else if(num != ler.key and ler.pont != -2){//O n�mero na primeira colis�o � diferente do que procuro e tenho uma lista de ponteiros, logo o n�mero pode existir nessa lista
        while(num != ler.key and ler.pont != -2){//procurando o n�mero na lista de ponteiros
        pos = ler.pont;
        fseek(arq,pos*sizeof(reg),SEEK_SET);
        fread(&ler,sizeof(reg),1,arq);
        }
        fseek(arq,pos*sizeof(reg),SEEK_SET);
        fread(&ler,sizeof(reg),1,arq);
        if(ler.key != num){
            cout << "chave nao encontrada: " << num << endl;
        }
        else if(ler.key == num){//achei meu n�mero
            cout << "chave: " <<  num << endl;
            cout << ler.name << endl;
            cout << ler.age << endl;
        }
    }
    else if(num != ler.key and ler.pont == -2){//O n�mero na primeira colis�o � diferente do que procuro e n�o tenho uma lista de ponteiros, logo o n�mero n�o existe
        cout << "chave nao encontrada: " << num << endl;
    }
}
//fun��o para remover um registro do hash
void hashe::removeregistrohashe(FILE *arq,int x,int z){
    save2 escrev,reg,ler,first,after;
    int start = z;
    int pos = z;
    int num = x;
    escrev.key = -1;//limpando o registro que ser� usado para apagar o registro escolhido
    escrev.age = -1;//limpando o registro que ser� usado para apagar o registro escolhido
    escrev.pont = -2;//limpando o registro que ser� usado para apagar o registro escolhido
    for(int i = 0;i < 20; i++){
        escrev.name[i] = ' ';
    }//limpando o registro que ser� usado para apagar o registro escolhido
    fseek(arq,z*sizeof(reg),SEEK_SET);
    fread(&ler,sizeof(reg),1,arq);
    if(ler.key == num and ler.pont == -2){//n�o tem lista nenhuma, apenas esse numero. Apenas apago o registro.
        fseek(arq,z*sizeof(reg),SEEK_SET);
        fwrite(&escrev,sizeof(reg),1,arq);
    }
    else if(ler.key == num and ler.pont != -2){//� o topo da lista de ponteiros entao basta tirar e puxar o proximo numero da lista para a primeira posi��o e apagar no local do proximo
        fseek(arq,pos*sizeof(reg),SEEK_SET);
        fread(&first,sizeof(reg),1,arq);
        fseek(arq,(first.pont)*sizeof(reg),SEEK_SET);
        fread(&after,sizeof(reg),1,arq);
        fseek(arq,pos*sizeof(reg),SEEK_SET);
        fwrite(&after,sizeof(reg),1,arq);
        fseek(arq,(first.pont)*sizeof(reg),SEEK_SET);
        fwrite(&escrev,sizeof(reg),1,arq);
    }
    else if(ler.key != num and ler.pont != -2){//n�o � o topo da lista de ponteiros mas pode est� no meio da lista
                while(num != ler.key and ler.pont != -2){
                    pos = ler.pont;
                    fseek(arq,pos*sizeof(reg),SEEK_SET);
                    fread(&ler,sizeof(reg),1,arq);
                    }
                    fseek(arq,pos*sizeof(reg),SEEK_SET);
                    fread(&ler,sizeof(reg),1,arq);
                    if(num != ler.key){
                        cout << "chave nao encontrada: " << num << endl;
                    }//finalmente achei o num
                    else if(num == ler.key){
                        fseek(arq,start*sizeof(reg),SEEK_SET);
                        fread(&first,sizeof(reg),1,arq);
                        fseek(arq,pos*sizeof(reg),SEEK_SET);
                        fread(&after,sizeof(reg),1,arq);
                        first.pont = after.pont;
                        fseek(arq,start*sizeof(reg),SEEK_SET);
                        fwrite(&first,sizeof(reg),1,arq);
                        fseek(arq,pos*sizeof(reg),SEEK_SET);
                        fwrite(&escrev,sizeof(reg),1,arq);
                    }//o numero nao existe no hash
    }
    else{
         cout << "chave nao encontrada: " << num << endl;
    }
}
void hashe::imprimehashe(FILE *arq){
    save2 reg,ler;
    for(int i = 0;i<this->tam;i++){
        fseek(arq,i*sizeof(reg),SEEK_SET);
        fread(&ler,sizeof(reg),1,arq);
        cout << i << ": ";
        if(ler.key == -1 and ler.pont == -2){
            cout << "vazio" << " "<< "nulo" << endl;
        }
        else if(ler.key != -1 and ler.pont == -2){
        cout << ler.key << " " << ler.name << " " << ler.age << " "<<"nulo"<< endl;
        }
        else if(ler.key != -1 and ler.pont != -2){
        cout << ler.key << " " << ler.name << " " << ler.age << " "<< ler.pont << endl;
        }
    }
}
