#include <stdio.h>

int GerarCliente(int capacityMax){

    return rand() % capacityMax + 1;
}
/*
//Essa função foi baseada na regra o numero de cliente precisa ser maior que o de caixa
//Caso queiram usar
int GerarCaixa(int CL){ 
    return  rand()%(CL+1);
}
*/
int a=0;
int tam = 0;


struct Fila{
    int id;  // identificador do cliente;
    int QIT;  // quantidade itens do cliente ou velocidade
    struct Fila *prox;
};

typedef struct Fila fila;

int filaVazia(fila *FILA) {
    if(FILA->prox == NULL)
        return 1;
    else
        return 0;
}

void iniciaFila(fila *FILA) {
    FILA->prox = NULL;
    int tam = 0;
}

fila *GeraFila() {
    fila *novo=(fila *) malloc(sizeof(fila));
    if(!novo){
        printf("Sem memoria disponivel!\n");
        exit(1);
    }else{
        novo->id=a+1;  //Gera id ;
        a=a+1; //incrementa id
        novo->QIT = (rand()%100)+1; //Preenche com valor aleatorio com quantidade de itens;
        return novo;
    }
}

void preencheFila(fila *FILA, int x) {
    while (a < x) {
        fila *novo = GeraFila();
        novo->prox = NULL;
        if (filaVazia(FILA))
            FILA->prox = novo;
        else {
            fila *tmp = FILA->prox;

            while (tmp->prox != NULL)
                tmp = tmp->prox;
            tmp->prox = novo;
        }
        tam = x;
    }
    a=0;
}

void exibeFila(fila *FILA, int x) {
    if(filaVazia(FILA)){
        printf("Fila vazia!\n\n");
        return ;
    }
    fila *tmp;
    tmp = FILA->prox;
    //printf("Fila:");
    while( tmp != NULL){
        printf("Fila pos %d - ", tmp->id);
        printf("%d itens na cesta\n", tmp->QIT);
        tmp = tmp->prox;
    }
}

fila *retiraCliente(fila *FILA) {
    if(FILA->prox == NULL){
        //printf("Filas Clientes já esta vazia\n");
        return NULL;
    }else{
        fila *tmp = FILA->prox;
        FILA->prox = tmp->prox;
        tam--;
        return tmp;

    }

}

