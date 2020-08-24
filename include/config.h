#ifndef CONFIG_H
#define CONFIG_H
typedef struct Status Status;
typedef struct Package Package;
typedef struct Transport Transport;
typedef struct Config
{
    Status * tree;
    float maxProfit;
    int nPackages;
    int nTransports;
    Package * packages;
    Transport * transports;
} Config;

Status * config(Transport * transports, Package * packages,int nTransports,int nPackages);
Config * openFile(char *filename);

#endif