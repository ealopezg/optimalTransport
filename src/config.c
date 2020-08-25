#include<stdio.h>
#include<stdlib.h>

#include"../include/status.h"
#include"../include/package.h"
#include"../include/transport.h"
#include"../include/config.h"

/**
 * @brief Opens the input file and
 * creates a Config object
 * 
 * @param filename i.e entrada1.in
 * @return Config* 
 */
Config * openFile(const char * filename){
    
    FILE * f;
    f = fopen (filename, "r");
    if(f == NULL){
        fclose(f);
        return NULL;
    }
    // If the file is not null
    char buffer[1000]; // Buffer to store the entire file
    Config *c = malloc(sizeof(Config)); // Create a new config object

    char ch;
    int i = 0;
    while ((ch = fgetc(f)) != EOF) // Reads the file until EOF
    {   
        if(ch!='|'){    // Ignores the |
            if(ch == '\n'){  // Replaces the newline with an space
                buffer[i] = ' ';
            }
            else{
                buffer[i] = ch;
            }
            i++;
        }
        else{
            ch = fgetc(f); // Ignores the char next to |
        }
    }
    fclose(f); // Closes the file
    
    buffer[i] = '\0';
    int n = 0;
    char *aux = &buffer[0]; // Pointer to the start to buffer

    sscanf(aux, "%d %d %n", &c->nTransports,&c->nPackages,&n); //Saves the nTransports and nPackages, the &n stores the bytes left in the pointer
    aux = aux + n;

    c->packages = malloc(c->nPackages*sizeof(Package)); //Creates the array of Packages
    c->transports = malloc(c->nTransports * sizeof(Transport)); //Creates the array of Transports
    
    for (int i = 0; i < c->nTransports; i++)
    {
        sscanf(aux, "%f %f %n", &c->transports[i].max_weight, &c->transports[i].profit,&n); //Store the max weight and profit for each transport
        aux = aux + n; //Moves the pointer

        c->transports[i].id = i; // Store the id
    }
    for (int i = 0; i < c->nPackages;i++){
        sscanf(aux, "%f %f %n", &c->packages[i].weight, &c->packages[i].profit,&n); //Store the weight and profit for each package
        aux = aux + n; //Moves the pointer

        c->packages[i].id = i; // Store the id
    }
    return c;
}

/**
 * @brief Write a file with solution of the problem.
 * 
 * @param c Config Object
 * @param st Optimal Status
 * @param filename i.e salida.out
 */
void writeFile(Config * c,Status * st,const char*filename){
    //First creates a string with the solution
    char*buffer=malloc(sizeof(char)*1000);
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

    // Save the file
    FILE *fp;
    fp = fopen(filename, "w+");
    fputs(buffer,fp);
    fclose(fp);
    free(buffer);

}