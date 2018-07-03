#include <stdio.h>
#include <stdlib.h>
 
struct Node
{
    int timeToProcess;
    int val;
    int cost;
    struct Node *left, *right;
};
 
//Criar novo n�
struct Node* newNode(int timeToProcess, int val)
{
    struct Node* temp =
          (struct Node*) malloc(sizeof(struct Node));
    temp->left = temp->right = NULL;
    temp->timeToProcess = timeToProcess;
    temp->val = val;
    temp->cost = timeToProcess*val;
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

