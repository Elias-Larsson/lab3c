#ifndef LAKAMEDEL_H
#define LAKAMEDEL_H
#include <stdio.h>
#define ARRAY_SIZE 100

struct lakemedel {
    int saldo[ARRAY_SIZE];
    int storlek[ARRAY_SIZE];
    char namn[ARRAY_SIZE];
};
typedef struct lakemedel Lakemedel;

void registreraLakemedel();
void skrivUtLakemedel();
#endif