#ifndef LAKAMEDEL_H
#define LAKAMEDEL_H
#include <stdio.h>
#define ARRAY_SIZE 100
#define MEDICINE_SIZE 10

struct medicine {
    int stock[MEDICINE_SIZE];
    int sizes[MEDICINE_SIZE];
    int sizesCount;
    char name[ARRAY_SIZE];
};
typedef struct medicine Medicine;

void handleAddMedicine();
void handlePrintMedicine();
void writeMedicineToFile(FILE *fp);
void handleAddSizes();
void handleAdjustStock();
void handlePartialSearch();
#endif
