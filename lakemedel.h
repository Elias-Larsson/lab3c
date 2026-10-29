#ifndef LAKAMEDEL_H
#define LAKAMEDEL_H
#include <stdio.h>
#define ARRAY_SIZE 100
#define MEDICINE_SIZE 10

struct medicine {
    int stock[ARRAY_SIZE];
    int size[MEDICINE_SIZE];
    char name[ARRAY_SIZE];
};
typedef struct medicine Medicine;

void handleAddMedicine();
void handlePrintMedicine();
void writeMedicineToFile(FILE *fp);
void handleAddSizes();
void handlePartialSearch();
#endif
