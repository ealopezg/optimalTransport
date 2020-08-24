#include<stdio.h>
#include<stdlib.h>
#include "../include/status.h"
#include "../include/config.h"
#include "../include/package.h"
#include "../include/transport.h"





Status * newTree(Config * c){
    Status * tree = malloc(sizeof(Status));
    tree->status = malloc(sizeof(int)*c->nPackages);
    for (int i = 0; i < c->nPackages; i++)
    {
        tree->status[i] = -2;
    }
    tree->parent = NULL;
    tree->lsib = NULL;
    tree->rsib = NULL;
    tree->child = NULL;
    tree->stage = -1;
    return tree;
}

Status * newChild(Status * parent,Config * c){
    Status * child = malloc(sizeof(Status));
    child->parent  = parent;
    child->rsib = NULL;
    child->lsib = NULL;
    parent->child = child;
    child->status = malloc(sizeof(int)*c->nPackages);
    for(int i = 0; i < c->nPackages;i++){
        child->status[i] = parent->status[i];
    }
    child->stage = parent->stage+1;
    child->status[child->stage]++;
    return child;
}

Status * newSib(Status * lsib,Config * c){
    Status * rsib = malloc(sizeof(Status));
    rsib->parent  = NULL;
    rsib->rsib = NULL;
    rsib->lsib = lsib;
    rsib->child = NULL;
    lsib->rsib = rsib;
    rsib->status = malloc(sizeof(int)*c->nPackages);
    for(int i = 0; i < c->nPackages;i++){
        rsib->status[i] = lsib->status[i];
    }
    rsib->stage = lsib->stage;
    rsib->status[rsib->stage]++;
    return rsib;
}
 
float check(Status * status,Config * c){

    float profits_per_transport[c->nTransports];
    float weights_per_transport[c->nTransports];
    for (int i = 0; i < c->nTransports; i++)
    {
        profits_per_transport[i] = 0;
        weights_per_transport[i] = 0;
    }
    for (int i = 0; i < c->nPackages; i++)
    {
        profits_per_transport[status->status[i]]+= c->packages[i].weight*c->transports[status->status[i]].profit + c->packages[i].profit;
        weights_per_transport[status->status[i]]+=c->packages[i].weight;
    }
    float totalProfit = 0;
    for (int i = 0; i < c->nTransports; i++)
    {
        totalProfit+=profits_per_transport[i];
        if(weights_per_transport[i]> c->transports[i].max_weight){
            return -1;
        }
    }
    return totalProfit;
}

int isCompleted(Status * st, Config * c){
    for(int i = 0; i < c->nPackages ; i++){
        if(st->status[i]!= c->nTransports-1){
            return 0;
        }
    }
    return 1;
}

// Status * newStatus(Status * st, Config *c){
//     float profit = check(st,c);
//     if(profit ==-1){
//         if(st->modified<c->nPackages){
//             return newSib(st,c);
//         }
//         else{
//             Status * aux = st;
//             while(aux->modified == c->nPackages){
//                 aux = aux->parent;
//             }

//         }
//     }
//     return newChild(st,c);
    
// }

Status * getFirstChild(Status * st){
    Status *aux = st;
    while (aux->parent == NULL)
    {
        aux = aux->lsib;
    }
    return aux;
}