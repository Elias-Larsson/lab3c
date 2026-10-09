#include "repository.h"
#include "lakemedel.h"
#include <stdio.h>

bool skrivLakemedel(FILE *fp, Lakemedel *l) {
    printf("skrivlakemedel: %s", l->namn);
    if (fp == NULL) {
        printf("hittade inte lakemedel.txt");
        return false;
    }
    fp = fopen("lakemedel.txt", "a");
    fprintf(fp,"%s\n",l->namn);
    return true;
}