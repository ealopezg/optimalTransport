#ifndef CONFIG_H
#define CONFIG_H
typedef struct Status Status;
typedef struct Package Package;
typedef struct Transport Transport;
typedef struct Config
{
    Status * tree;
    int nPackages;
    int nTransports;
    Package * packages;
    Transport * transports;
} Config;

Config * openFile(const char *filename);
void writeFile(Config * c,Status * st,const char* filename);
#endif