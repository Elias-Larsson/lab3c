#ifndef LAKAMEDEL_H
#define LAKAMEDEL_H
#include <stdio.h>
#define ARRAY_SIZE 1000
#define MEDICINE_SIZE 10

typedef struct {
    char name[21];
    int sizes[MEDICINE_SIZE];
    int stock[MEDICINE_SIZE];
    int sizesCount;
} Medicine;

void handleAddMedicine(Medicine medicines[], int *registerSize);
void handlePrintMedicine(Medicine medicines[], int registerSize);
void handleAddSizes(Medicine medicines[], int registerSize);
void handleAdjustStock(Medicine medicines[], int registerSize);
void handlePartialSearch(Medicine medicines[], int registerSize);
void handleRemoveMedicine(Medicine medicines[], int *registerSize);
void handleStockWarnings(Medicine medicines[], int registerSize);
void handleRemoveSizes(Medicine medicines[], int registerSize);
#endif
