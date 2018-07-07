#include <iostream>
#include<malloc.h>
#include "Node.h"
#include "MinHeap.h"
#include "Lista.h"

using namespace std;



//--------------------------------FUNÇÃO DE ATENDIMENTO DE CLIENTES-------------------------------------------------



int atendimento(MinHeap* filaCaixa, fila* filaCliente, int quantidadeClientes) {

	struct MinHeap* filaCaixasOcupados = initMinHeap(filaCaixa->size);
	int custo;
	int tempo = 0;
	int clientesProcessados = 0;

	while (clientesProcessados < quantidadeClientes) {
		//Retirar caixa com prioridade
		Node* caixa = topMinHeap(filaCaixa);
		
		if (caixa != NULL) {
			popMinHeap(filaCaixa);		
		
			//Inserir tempo de processamento			
			custo = filaCliente->prox->QIT * caixa->val;			
			caixa->auxVal = caixa->val;			
			caixa->val = custo;
			caixa->itensProcessados = filaCliente->prox->QIT; //nova linha
			
			pushMinHeap(filaCaixasOcupados, caixa);
			
			if (tempo < caixa->val) {
				tempo = caixa->val;
			}
		}		
		else {
			Node* caixaOcupado = topMinHeap(filaCaixasOcupados);
			
			if (caixaOcupado != NULL) {					
				popMinHeap(filaCaixasOcupados);
				
				//Inserir tempo de processamento
				if (filaCliente->prox != NULL) {
					custo = filaCliente->prox->QIT * caixaOcupado->auxVal;
					caixaOcupado->val += custo;
					caixaOcupado->itensProcessados += filaCliente->prox->QIT; //nova linha
				} 			
				
				if (tempo < caixaOcupado->val)	{
					tempo = caixaOcupado->val;
				}
				
				pushMinHeap(filaCaixasOcupados, caixaOcupado);
				clientesProcessados++;		
			}	
		}	
		retiraCliente(filaCliente);
	}
			
	
	cout << "\n----------------------------------MIN HEAP DE CUSTO (Atendimento dos Clientes)----------------------------------\n ";
	int i = 0;

	cout << "\nEstado da heap de custo quando o ultimo cliente foi alocado para ser atendido: \n\n";

    while (i < filaCaixasOcupados->size)
    {
        printf("Caixa pos %d - [custo: %d] (T: %d) {Total de itens processados: %d}\n ",
		 i+1 ,filaCaixasOcupados->array[i]->val, filaCaixasOcupados->array[i]->auxVal,filaCaixasOcupados->array[i]->itensProcessados);
        i++;
    }
    
    free (filaCaixasOcupados);
    
    return tempo;	
}




//--------------------------------PROGRAMA PRINCIPAL----------------------------------------------------------------




int main()
{	
	printf("PROGRAMA FILA DE SUPERMERCADO\n\n");
	
//------------ÁREA DE DEFINIÇÃO DA QUANTIDADE DE CAIXAS E CLIENTES--------------------------------------------------

	const int MAX_NUMBER_OF_CLIENTS =  rand() % 10000 + 1;
	const int MAX_NUMBER_OF_CASHIERS =  rand() % MAX_NUMBER_OF_CLIENTS + 1;
	
//-------------------------------PROCESSAMENTO DO PROGRAMA ----------------------------------------------------------
	
    int cashierPriority[MAX_NUMBER_OF_CASHIERS];
    
    for (int n = 0; n < MAX_NUMBER_OF_CASHIERS; n++) {
    	cashierPriority[n] = rand() % 100 + 1;
	}

    struct MinHeap* filaCaixa = generateTreeMinHeap(cashierPriority, MAX_NUMBER_OF_CASHIERS);
	
	int i = 0;
	
	cout << "--------------------------------------MIN HEAP DE CAIXAS DESOCUPADOS----------------------------------\n ";

    printf("\nEstado inicial da Heap de caixas desocupados \ncom seus tempos de processamento (prioridades): \n\n ");
    while (i < MAX_NUMBER_OF_CASHIERS)
    {
        printf("Caixa pos %d - (T: %d)\n ", i+1 ,filaCaixa->array[i]->val);
        i++;
    }	
	
	fila *filaCliente = (fila *) malloc(sizeof(fila));
	if(!filaCliente){
        printf("Sem memoria disponivel!\n");
        exit(1);
    }else {
        iniciaFila(filaCliente);
    }
    
	preencheFila(filaCliente, MAX_NUMBER_OF_CLIENTS);
	
	cout << "\n------------------------------------------CLIENTES-----------------------------------------------\n ";
	printf("\nEstado inicial da fila de clientes: \n\n");
	exibeFila(filaCliente, MAX_NUMBER_OF_CLIENTS);
	
	int tempo = atendimento(filaCaixa, filaCliente, MAX_NUMBER_OF_CLIENTS);
	
cout << "\n------------------------------------------TEMPO TOTAL-----------------------------------------------\n ";
	
	printf("\n O tempo total de atendimento foi de: %d unidades de tempo.", tempo);
	cout<<"\n\n";
	
	
	free (filaCliente);
	free (filaCaixa);
	
	cin.get();
    return 0;
}
