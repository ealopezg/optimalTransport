#include<stdio.h>

#include"../include/status.h"
#include"../include/package.h"
#include"../include/transport.h"
#include"../include/config.h"



/**
 * @brief Backtracking function, it takes
 * a config object and returns the optimal
 * combination (A Status Object).
 * 
 * @param c Config object
 * @return Status* Optimal Combination
 */
Status * backtracking(Config * c){
    c->tree = newTree(c); // Generates a new tree
    
    int completed = 0;
    Status *actual = c->tree; // Pointer to the tree of the config
    Status *best; // Stores the best status
    float bestProfit = 0; // Profit of the best status
    float actualProfit = -2; // Float to the store the actual status    
    int started=0; // FLAG TO CHECK IF THE ALGORTHIM HAS COMPLETED
    int createSib = 0; // Flag to check if the current status can create a right sibling
    int createChild = 0; // Flag to check if the current status can create a child
    while (completed==0)
    {
        if(actual->stage == -1 && started==1){
            completed = 1;
        }
        else{
            createChild = actual->stage!=c->nPackages-1;
            createSib = actual->status[actual->stage]!=c->nTransports-1;

            actualProfit = check(actual, c);
            #ifdef DEBUG
            printCurrent(actual,c,actualProfit);
            #endif
            if (actualProfit >= bestProfit && actualProfit>=0) //If the current status has best profit than the best status
            {
                best = actual; //Stores the status
                bestProfit = actualProfit; // Stores the profit
            }
            
            if(actualProfit!=-2 || (actualProfit==-2 && !createChild)){ //If the profit is not -2: The status is invalid and go to the parent
                while(!createSib){
                    actual = getFirstSib(actual)->parent; //Sets the actual status as the parent of the current node
                    createSib = actual->status[actual->stage]!=c->nTransports-1; //Check if the parent can create siblings
                }
                actual = newSib(actual,c); // Create a new sibling for the status
            }
            else{
                actual = newChild(actual, c); // Create a new child for the status
            }
            started = 1;
        }
    }
    return best;
}

