#include<stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "../include/package.h"
#include "../include/transport.h"
#include "../include/status.h"
#include "../include/config.h"



int main(int argc, char const *argv[])
{
    Config *c = openFile("entrada1.in");
    if(c != NULL){
        Status *sol = backtracking(c);
        for (int i = 0; i < c->nPackages; i++)
        {
            printf("%d ", sol->status[i]);
        }
    }

    return 0;
}
