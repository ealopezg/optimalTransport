#include<stdio.h>
#include<stdlib.h>
#include "../include/status.h"
#include "../include/config.h"
#include "../include/package.h"
#include "../include/transport.h"

/**
 * @brief Generates an empty tree
 * The first element has status as an int array with each element with -2
 * -2: indicates the root of the tree
 * 
 * @param c Config object 
 * @return Status* 
 */
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
    tree->stage = -1; //Represents each i-package modified, the root is -1 stage 
    return tree;
}

/**
 * @brief Generates a child for the current status
 * the child stage will the next stage of the parent
 * @param parent Parent (Current status)
 * @param c Config Object
 * @return Status* 
 */
Status * newChild(Status * parent,Config * c){
    Status * child = malloc(sizeof(Status));
    child->parent  = parent;
    child->rsib = NULL;
    child->lsib = NULL;
    parent->child = child;
    child->status = malloc(sizeof(int)*c->nPackages);
    for(int i = 0; i < c->nPackages;i++){// Copies the parent elements
        child->status[i] = parent->status[i];
    }
    child->stage = parent->stage+1;
    child->status[child->stage]++;
    return child;
}
/**
 * @brief Generates a right sibling for the current status
 * the sibling stage will be the same as the left sibling
 * @param lsib Left Sibling (Current status)
 * @param c Config Object
 * @return Status* 
 */
Status * newSib(Status * lsib,Config * c){
    Status * rsib = malloc(sizeof(Status));
    rsib->parent  = NULL;
    rsib->rsib = NULL;
    rsib->lsib = lsib;
    rsib->child = NULL;
    lsib->rsib = rsib;
    rsib->status = malloc(sizeof(int)*c->nPackages);
    for(int i = 0; i < c->nPackages;i++){// Copies the sibling elements
        rsib->status[i] = lsib->status[i];
    }
    rsib->stage = lsib->stage; // The stage is the same
    rsib->status[rsib->stage]++; 
    return rsib;
}
 

/**
 * @brief Returns the status's profit as a float:
 * It can be:
 *  -1: If the status is invalid (A transport has exceeded the max weight)
 *  -2: If the status hasn't reached the last package but it can reach it and every transport has not reach the max weight
 *  0... : The profit of the status
 * @param status Actual status
 * @param c Config
 * @return float profit
 */
float check(Status * status,Config * c){
    if(status->stage == -1){ //If the status is the root return -2
        return -2;
    }
    float profits_per_transport[c->nTransports]; //Array to store the profits for each transport
    float weights_per_transport[c->nTransports]; //Array to store the weights for each transport
    int notCompleted = 0;

    //Initializes the arrays
    for (int i = 0; i < c->nTransports; i++)
    {
        profits_per_transport[i] = 0; 
        weights_per_transport[i] = 0;
    }
    //For each element of the status , also like for every package
    for (int i = 0; i < c->nPackages; i++)
    {
        if(status->status[i]!=-2 && status->status[i]!=-1){ //-2 indicates that the algorithm hasn't decided the transport
                                                            //-1 indicates that the package will not be entered into any transport (0 weight and 0 profit)
            profits_per_transport[status->status[i]]+= c->packages[i].weight*c->transports[status->status[i]].profit + c->packages[i].profit;
            weights_per_transport[status->status[i]]+=c->packages[i].weight;
        }
        else if(status->status[i]==-2){ //-2 indicates that the algorithm hasn't decided the transport
            notCompleted = 1;
        }
    }
    float totalProfit = 0;
    for (int i = 0; i < c->nTransports; i++)
    {
        totalProfit+=profits_per_transport[i]; // Sums the profits
        if(weights_per_transport[i]> c->transports[i].max_weight){ // If the weight reaches the max, returns -1 : INVALID STATUS
            return -1;
        }
    }
    if(notCompleted){
        return -2; //If the status hasn't reached the last package but it can reach it and every transport has not reach the max weight
    }
    return totalProfit;
}

#ifdef DEBUG
/**
 * @brief If the debug is activated it will print the
 * current Status with the profit and the stage
 * 
 * @param st Current status
 * @param c Config
 * @param profit Profit of the status
 */
void printCurrent(Status * st,Config *c,float profit){
    printf("Embarque: ");
    for (int i = 0; i < c->nPackages; i++)
        {
            printf("%d ", st->status[i]);
        }
    printf("Beneficio: %f NIVEL: %d\n",profit,st->stage);
}
#endif

/**
 * @brief Get the First Child of an
 * status, it explores the tree until reaches a node that has parent node
 * (LEFT SIBLING)
 * 
 * @param st 
 * @return Status* 
 */
Status * getFirstSib(Status * st){
    Status *aux = st;
    while (aux->parent == NULL)
    {
        aux = aux->lsib;
    }
    return aux;
}
