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
    Status *best;
    float bestProfit = 0;
    float actualProfit = -2;
    int started=0;
    char input[10];
    float p;

    int createSib = 0;
    int createChild = 0;
    while (completed==0)
    {
        if(aux->stage == -1 && started==1){
            completed = 1;
        }
        else{
            createChild = aux->stage!=c->nPackages-1;
            createSib = aux->status[aux->stage]!=c->nTransports-1;
            actualProfit = check(aux, c);
            //printStatus(aux,c,actualProfit);
            //printf("CC: %d CS: %d PROFIT: %f\n",createChild,createSib,actualProfit);
            if (actualProfit >= bestProfit && actualProfit>=0)
            {
                best = aux;
                bestProfit = actualProfit;
            }
            if(actualProfit==-1){
                while(!createSib){
                    aux = getFirstChild(aux)->parent;
                    createSib = aux->status[aux->stage]!=c->nTransports-1;
                }
                aux = newSib(aux,c);
            }
            else if(createChild){
                aux = newChild(aux, c); //HIJO
                //printf("Se creó un hijo\n");
            }
            else{
                if(createSib){
                    aux = newSib(aux, c);
                    //printf("Se creo un hermano\n");
                }
                else{
                    while(!createSib){
                        aux = getFirstChild(aux)->parent;
                        createSib = aux->status[aux->stage]!=c->nTransports-1;
                    }
                    aux = newSib(aux,c);
                }
            }
            
            
            started = 1;
        }
    }
    return best;
}

