#include<stdio.h>
#include<stdlib.h>

#include"../include/status.h"
#include"../include/package.h"
#include"../include/transport.h"
#include"../include/config.h"


Config * openFile(char * filename){
    char buffer[1000];
    FILE * f;

    f = fopen (filename, "r");
    if(f == NULL){
        return NULL;
    }
    
    Config *c = malloc(sizeof(Config));
    c->maxProfit = 0;

    char ch;
    int i = 0;
    int j = 0;
    char ant;
    while ((ch = fgetc(f)) != EOF)
    {   
        if(ch!='|'){
            if(ch == '\n'){
                buffer[i] = ' ';
            }
            else{
                buffer[i] = ch;
            }
            i++;
        }
        else{
            ch = fgetc(f);
        }
        }
    int n = 0;
    buffer[i] = '\0';
    char *aux = &buffer[0];
    sscanf(aux, "%d %d %n", &c->nTransports,&c->nPackages,&n);
    aux = aux + n;

    c->packages = malloc(c->nPackages*sizeof(Package));
    c->transports = malloc(c->nTransports * sizeof(Transport));
    fclose(f);
    for (int i = 0; i < c->nTransports; i++)
    {
        sscanf(aux, "%f %f %n", &c->transports[i].max_weight, &c->transports[i].profit,&n);
        aux = aux + n;
        c->transports[i].id = i;
    }
    for (int i = 0; i < c->nPackages;i++){
        sscanf(aux, "%f %f %n", &c->packages[i].weight, &c->packages[i].profit,&n);
        aux = aux + n;
        c->packages[i].id = i;
    }
    return c;
}