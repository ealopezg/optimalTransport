#include<stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "../include/package.h"
#include "../include/transport.h"
#include "../include/status.h"
#include "../include/config.h"
#include "../include/backtracking.h"



int main(int argc, char const *argv[])
{
    if(argc !=3){
        return 0;
    }
    Config *c = openFile(argv[1]);
    if(c != NULL){
        Status *sol = backtracking(c);
        writeFile(c,sol,argv[2]);
    }
    

    return 0;
}
