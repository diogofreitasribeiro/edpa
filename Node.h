#include <stdio.h>
#include <stdlib.h>
 
struct Node
{
	int id;
    int val;
    int auxVal;
    int itensProcessados; //nova linha
    struct Node *left, *right;
};
 
//Criar novo n�
struct Node* newNode(int id, int val)
{
    struct Node* temp =
          (struct Node*) malloc(sizeof(struct Node));
    temp->left = temp->right = NULL;
    temp->val = val;
    temp->auxVal = 0;
    return temp;
}

// Faz a troca dos n�s
void swapNode(struct Node** a, struct Node** b)
{
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

// Verifica se o n� � uma folha
int isLeaf(struct Node* root)
{
    return !(root->left) && !(root->right) ;
}

