#ifndef CONFIG_H
#include "package.h"
#include "status.h"
#include "transport.h"
#define CONFIG_H

typedef struct Config
{
    Status * tree;
    float maxProfit;
    int nPackages;
    int nTransports;
    Package ** packages;
    Transport ** transports;
} Config;

Status * config(Transport ** transports, Package ** packages,int nTransports,int nPackages);


#endif