#ifndef LAKAMEDEL_H
#define LAKAMEDEL_H
#include <stdio.h>
#define MAX_MEDICINES 1000
#define MAX_SIZES 10

typedef struct {
    char name[21];
    int sizes[MAX_SIZES];
    int stock[MAX_SIZES];
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
