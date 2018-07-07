#include <stdio.h>
#include <stdlib.h>
 
int custoTrocas = 0; 
 
// Min Heap
struct MinHeap
{
    int size;
    int capacityMax;
    struct Node **array;
};
 
struct MinHeap* initMinHeap(int capacityMax)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacityMax = capacityMax;
    minHeap->array =
     (struct Node**)malloc(minHeap->capacityMax * sizeof(struct Node*));
    return minHeap;
}

// Promover ou Rebaixar o nó
void promoteDemoteMinHeap(struct MinHeap* minHeap, int idx)
{
    int parent = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->val < minHeap->array[parent]->val)
      parent = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->val < minHeap->array[parent]->val)
      parent = right;
 
    if (parent != idx)
    {
        swapNode(&minHeap->array[parent], &minHeap->array[idx]);
        promoteDemoteMinHeap(minHeap, parent);
    }
    
    custoTrocas++;
}
 
// Inserir um novo nó
void pushMinHeap(struct MinHeap* minHeap, struct Node* Node)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && Node->val < minHeap->array[(i - 1)/2]->val)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = Node;
}

//Retira o menor elemento, inseri o maior elemento no topo e faz o balanceamento
void popMinHeap(struct MinHeap* minHeap)
{
	swapNode(&minHeap->array[0], &minHeap->array[minHeap->size-1]);
	minHeap->array[minHeap->size-1] = NULL;
	minHeap->size = minHeap->size-1;
	
	promoteDemoteMinHeap(minHeap, 0);
}

//Retorna o menor nó da árvore
Node* topMinHeap(struct MinHeap* minHeap)
{
	return minHeap->array[0];
}
 
void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        promoteDemoteMinHeap(minHeap, i);
}
 
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}
 
// Função para criar uma árvore Heap
struct MinHeap* generateTreeMinHeap(int val[], int size)
{
    struct MinHeap* minHeap = initMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(i + 1, val[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}
 
