#ifndef LAKAMEDEL_H
#define LAKAMEDEL_H
#include <stdio.h>
#define ARRAY_SIZE 100

struct medicine {
    int stock[ARRAY_SIZE];
    int size[ARRAY_SIZE];
    char name[ARRAY_SIZE];
};
typedef struct medicine Medicine;

void addMedicine();
void printMedicineRegister();
void writeMedicineRegister(FILE *fp);

#endif