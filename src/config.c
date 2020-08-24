#include<stdio.h>
#include<stdlib.h>

#include"../include/status.h"
#include"../include/package.h"
#include"../include/transport.h"
#include"../include/config.h"


Config * openFile(const char * filename){
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

void writeFile(Config * c,Status * st,const char*filename){
    char*buffer=malloc(sizeof(char)*1000);
    int n = 0;
    int a = 0;
    float totalweight = 0;
    float totalprofit = 0;
    float weight = 0;
    float profit = 0;
    for(int i=0;i<c->nTransports;i++){
        a = snprintf(buffer+a,1000-a,"Transporte %d:\n",i+1)+a;
        for(int j=0;j<c->nPackages;j++){
            if(st->status[j]==i){
                a = snprintf(buffer+a,1000-a,"%d ",(int)c->packages[j].weight)+a;
                weight+=c->packages[j].weight;
                totalweight+=c->packages[j].weight;
                totalprofit+=(c->packages[j].weight* c->transports[i].profit)+ c->packages[j].profit;
                profit+=(c->packages[j].weight* c->transports[i].profit)+ c->packages[j].profit;
            }
        }
        a = snprintf(buffer+a,1000-a,"\nPeso: %.1f\nBeneficio: %.1f\n---\n",weight,profit)+a;
        weight = 0;
        profit = 0;
    }
    a = snprintf(buffer+a,1000-a,"Peso total: %.1f\nBeneficio total: %.1f\n",totalweight,totalprofit)+a;

    FILE *fp;

    fp = fopen(filename, "w+");
    fputs(buffer,fp);
    fclose(fp);

}