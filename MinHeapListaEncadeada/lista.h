
struct Fila{
    int id;  // identificador do cliente;
    int QIT;  // quantidade itens do cliente ou velocidade
    struct Fila *prox;
};

typedef struct Fila fila;

int tam =0;
int a=0;


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
        a=a+1; //\incrementa id
        novo->QIT = (rand()%10)+1; //Preenche com valor aleatorio com quantidade de itens;
        return novo;
    }
}

void preencheFila(fila *FILA, int x) {
    printf(" a %d\n" , a);
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
    printf("Fila :");
    while( tmp != NULL){
        printf("%5d - ", tmp->id);
        printf("%5d\n", tmp->QIT);
        tmp = tmp->prox;
    }

}

fila *retiraCliente(fila *FILA) {
    if(FILA->prox == NULL){
        printf("Filasw Clientes já esta vazia\n");
        return NULL;
    }else{
        fila *tmp = FILA->prox;
        FILA->prox = tmp->prox;
        tam--;

        printf("\nRetirado ");
        return tmp;

    }


}