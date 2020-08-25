#ifndef STATUS_H
#define STATUS_H
typedef struct Config Config;

typedef struct Status
{
    int * status;
    int stage;
    struct Status * parent;
    struct Status * lsib;
    struct Status * rsib;
    struct Status * child;
} Status;

Status *newTree(Config *c);
Status *newChild(Status *parent, Config *c);
Status * newSib(Status * lsib,Config * c);
float check(Status * status,Config * c);
Status *getFirstSib(Status *st);

#ifdef DEBUG
void printCurrent(Status * st,Config *c,float profit);
#endif

#endif