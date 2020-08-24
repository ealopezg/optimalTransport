#include<stdio.h>
#include<stdlib.h>
#include"../include/transport.h"

Transport * new_transport(int id,float max_weight,float profit){
    Transport * tp = malloc(sizeof(Transport));
    tp->id = id;
    tp->max_weight = max_weight;
    tp->profit = profit;

    return tp;
}
