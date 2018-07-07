#include <stdio.h>
#include<malloc.h>
#include "util.h"
#include "lista.h"

//#include "heap.h"




typedef struct Heap{
    int idCaixa;
    int tempo;
    int velocidade;
    struct Heap *esquerda;
    struct Heap *direita;
    struct Heap *pai;
} Heap;

int CL=0;


struct Heap * PercorreHeap(Heap * heap) ;


struct Heap * Promove(Heap *Pai){
    int idcaixatmp=0;
    int tempotmp =0;
    int velocidadetemp= 0;


    idcaixatmp = Pai->idCaixa;
    tempotmp = Pai->tempo;
    velocidadetemp = Pai->velocidade;
    Pai->velocidade = Pai->pai->velocidade;
    Pai->idCaixa = Pai->pai->idCaixa;
    Pai->tempo = Pai->pai->tempo;
    Pai->pai->velocidade=velocidadetemp;
    Pai->pai->idCaixa = idcaixatmp;
    Pai->pai->tempo = tempotmp;
    return Pai;


}

void pinterHeap(Heap *h){
    printf("\n**********************\n");
    printf("\nPai : %d ", h);
    printf("\nEsquerda : %d  ", h->esquerda);
    printf("\nDireita : %d  ", h->direita);
    printf("\nTempo :%d  ", h->tempo);
    printf("\nCaixa : %d  ", h->idCaixa);
    printf("\nVelocidade : %d  ", h->velocidade);

}


 void Impressao(Heap *heap) {

     if (heap->esquerda != NULL && heap->direita != NULL && heap!=NULL) {
         if (heap->pai != NULL && (heap->pai->esquerda == NULL && heap->pai->direita == NULL)) {
              return pinterHeap(heap->pai->direita);
         }
         return pinterHeap(heap->esquerda);
     }
      return pinterHeap(heap);

}

struct Heap * Rebaixa(Heap *Pai){
    int idcaixatmp=0;
    int tempotmp =0;
    int velocidadetemp= 0;

    idcaixatmp = Pai->idCaixa;
    tempotmp = Pai->tempo;
    velocidadetemp = Pai->velocidade;
    Pai->velocidade = Pai->pai->velocidade;
    Pai->idCaixa = Pai->pai->idCaixa;
    Pai->tempo = Pai->pai->tempo;
    Pai->pai->velocidade=velocidadetemp;
    Pai->pai->idCaixa = idcaixatmp;
    Pai->pai->tempo = tempotmp;
    Impressao(Pai);
    return Pai;


}
struct Heap * ComparaTempo(Heap *Pai) {

    if (Pai->esquerda == NULL && Pai->direita== NULL && Pai->pai!=NULL) {

        while (Pai->tempo < Pai->pai->tempo) {
            Pai = Promove(Pai);
        }
    }

    if (Pai->direita!=NULL && Pai->esquerda!=NULL){

        if(Pai->esquerda->tempo< Pai->tempo){
            Pai= Promove(Pai->esquerda);
        }else {
            if(Pai->direita->tempo<Pai->tempo){
                Pai= Promove(Pai->direita);
            }
        }
    }
    return Pai;


}



void AtendeNovoCliente(fila *Cliente, Heap *Arvore, int cont){

    while( cont<=CL) {

        int tempo = Arvore->tempo;
        int velocidade = Arvore->velocidade;
        int qteitens = Cliente->QIT;
        Arvore->tempo = tempo + (velocidade * qteitens);
        Arvore = ComparaTempo(Arvore);
        Cliente = Cliente->prox;
        printf("\n\nContador: %d", cont);
        Impressao(Arvore);
        cont++;
        //retiraCliente(Cliente);

    }



    printf("Atendimento Finalizado!");


}





void Atendimento(fila *Cliente, fila *Caixa){

    int cont = 1;
    Heap * Arvore = NULL;
    Heap * Pai = NULL;

    fila * Cli;
    fila * Cai;

    Cli = Cliente->prox;
    Cai = Caixa->prox;
    
    Heap * heap;


    while (Cli->prox != NULL) {

        printf("\nAtendendo Novo Cliente\n");

        int idcaixa = 0;
        int velocidadecaixa = 0;
        int qteitens = 0;
        int tempo = 0;

        idcaixa = Cai->id;
        velocidadecaixa = Cai->QIT;
        qteitens = Cli->QIT;
        tempo = velocidadecaixa * qteitens;

        heap = (Heap *) malloc(sizeof(Heap));

        printf("\n\nContador: %d", cont);
        if(cont == 1) {
            heap->pai = NULL;
            heap->direita = NULL;
            heap->esquerda = NULL;
            heap->velocidade=velocidadecaixa;
            heap->idCaixa=idcaixa;
            heap->tempo=tempo;
            Pai = heap;
            Arvore = heap;
            Impressao(heap);

        } else {
            Pai = PercorreHeap(Pai);

            if(Pai->esquerda == NULL) {
                heap->direita = NULL;
                heap->esquerda = NULL;
                Pai->esquerda = heap;
                heap->velocidade=velocidadecaixa;
                heap->idCaixa=idcaixa;
                heap->tempo=tempo;
                heap->pai = Pai;

               heap = ComparaTempo(heap);
                Impressao(heap);

            } else {
                heap->direita = NULL;
                heap->esquerda = NULL;
                Pai->direita = heap;
                heap->velocidade=velocidadecaixa;
                heap->idCaixa=idcaixa;
                heap->tempo=tempo;
                heap->pai = Pai;

                heap = ComparaTempo(heap);
                Impressao(heap);

            }

        }

        cont++;



        if (Cai->prox == NULL){
            AtendeNovoCliente(Cli, Arvore, cont);
            return;
        } else {
            Cai= Cai->prox;
            Cli = Cli->prox;
        }

    }
    
    free(heap);
}


struct Heap * PercorreHeap(Heap * heap) {


    if (heap->esquerda != NULL && heap->direita != NULL) {

        if (heap->pai != NULL && (heap->pai->direita->esquerda == NULL || heap->pai->direita->direita == NULL)) {

            return heap->pai->direita;
        }
        return heap->esquerda;
    }

    return heap;

}



int main() {
    CL = GerarCliente();
    int CX = GerarCaixa(CL);

    printf("\n\nNumero Clientes %d\n ", CL);
    printf("Numero Caixas %d\n\n", CX);

    fila *Cliente = (fila *) malloc(sizeof(fila));

    if(!Cliente){
        printf(" Sem memoria disponivel!\n");
        exit(1);
    }else {
        iniciaFila(Cliente);
    }
    preencheFila(Cliente, CL);

    exibeFila(Cliente, CL);

    // printf("\nFila Cliente ok");

    fila *Caixa = (fila *) malloc(sizeof(fila));
    if(!Caixa){
        printf(" Sem memoria disponivel!\n");
        exit(1);
    }else {
        iniciaFila(Caixa);
    }
    preencheFila(Caixa, CX);
    exibeFila(Caixa, CX);

    Atendimento(Cliente, Caixa);


	char str [80];
	scanf ("%79s",str);
	
	free(Caixa);
	free(Cliente);
    return 0;
}
