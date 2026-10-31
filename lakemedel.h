#ifndef LAKAMEDEL_H
#define LAKAMEDEL_H
#include <stdio.h>
#define ARRAY_SIZE 100
#define MEDICINE_SIZE 10

typedef struct {
    char name[21];
    int sizes[MEDICINE_SIZE];
    int stock[MEDICINE_SIZE];
    int sizesCount;
} Medicine;

void handleAddMedicine(Medicine medicines[ARRAY_SIZE], int *registerSize);
void handlePrintMedicine(Medicine medicines[ARRAY_SIZE], int registerSize);
void handleAddSizes(Medicine medicines[ARRAY_SIZE], int registerSize);
void handleAdjustStock(Medicine medicines[ARRAY_SIZE], int registerSize);
void handlePartialSearch(Medicine medicines[ARRAY_SIZE], int registerSize);
#endif
