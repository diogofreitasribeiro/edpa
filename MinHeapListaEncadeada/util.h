#include <stdio.h>

int GerarCliente(){

    return (rand()%10000)+1;
}

int GerarCaixa(int CL){
    return  rand()%(CL+1);
}






