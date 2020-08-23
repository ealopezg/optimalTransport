#ifndef STATUS_H


#define STATUS_H
typedef struct Status
{
    int * status;
    int modified;
    Status * parent;
    Status * lsib;
    Status * rsib;
    Status * child;
} Status;

Status * newChild(Status * parent,Config * c);
Status * newSib(Status * lsib,Config * c);
float check(Status * status,Config * c);


#endif