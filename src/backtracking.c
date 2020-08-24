#include<stdio.h>

#include"../include/status.h"
#include"../include/package.h"
#include"../include/transport.h"
#include"../include/config.h"




Status * backtracking(Config * c){
    c->tree = newTree(c);
    int completed = 0;
    Status *aux = c->tree;
    Status *aux1;
    int invalid = 0;
    Status *best;
    float bestProfit = 0;
    float actualProfit;
    int j = 0;
    while (completed==0)
    {
        
        
        if(aux->status[c->nPackages-1] == c->nTransports-1){
            aux1 = getFirstChild(aux);
            while (aux1->parent->status[aux1->parent->stage] == c->nTransports - 1)
            {
                aux1 = getFirstChild(aux1->parent);
                
            }

            aux = newSib(aux1->parent, c);
            printf("Se devolvió\n");
        }
        else if(aux->stage == c->nPackages-1){
            aux = newSib(aux, c);
            printf("Se creo un hermano\n");
        }
        else{
            printf("Se crea un hijo\n");
            aux = newChild(aux, c);
        }
        actualProfit = check(aux, c);

        
        if (actualProfit > bestProfit)
        {
            best = aux;
            bestProfit = actualProfit;
        }
        
        for (int i = 0; i < c->nPackages; i++)
        {
            printf("%d ", aux->status[i]);
        }
        printf("\n");
        completed = isCompleted(aux, c);
        printf("completed: %d\n", completed);
    }
    printf("terminó");
    return best;
}

