#include<stdio.h>
#include"../include/status.h"
#include"../include/config.h"
#include"../include/transport.h"
#include"../include/package.h"

Status * backtracking(Transport ** transports, Package ** packages,int nTransports,int nPackages){
    Config * c = malloc(sizeof(Config));
    c->transports = transports;
    c->packages = packages;
    c->nPackages = nPackages;
    c->nTransports = nTransports;
    c->maxProfit = 0.0;
    c->tree = newTree(c);

    int completed = 0;
    Status * aux = c->tree;
    while (!completed){
        int * newS = newStatus(aux,c);
    }
}

Status * get(Status * last,Config * c){
    if(isCompleted(last,c)){
        return last;
    }


}