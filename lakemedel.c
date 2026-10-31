#include "lakemedel.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void addSizes(Medicine *medicine);
void printMedicine(Medicine *medicine);
bool medicineSearch(char query[], Medicine medicines[ARRAY_SIZE], int registerSize);
bool medicinePartialSearch(char query[ARRAY_SIZE], int i, Medicine medicines[ARRAY_SIZE]);
int searchMedicineIndex(Medicine medicines[ARRAY_SIZE], int registerSize);

void handleAdjustStock(Medicine medicines[], int registerSize) {
    int medicineIndex, adjustment;

    printf("Andra lagersaldo\n");
    medicineIndex = searchMedicineIndex(medicines, registerSize);

    if (medicineIndex == -1) return;

    Medicine *medicine = &medicines[medicineIndex];

    for (int i = 0; i < medicine->sizesCount; i++) {
        printf("Ange andring (+/-) for storlek %d: ", medicine->sizes[i]);
        scanf("%d", &adjustment);

        if (medicine->stock[i] + adjustment < 0) {
            printf("VARNING finns endast %d satter saldo till 0.\n",
                   medicine->stock[i]);
            medicine->stock[i] = 0;
        } else {
            medicine->stock[i] += adjustment;
        }
    }
}

void handleAddSizes(Medicine medicines[], int registerSize) {
    printf("Lagg till storlekar\n");

    int medicineIndex = searchMedicineIndex(medicines, registerSize);

    if (medicineIndex == -1) return;

    addSizes(&medicines[medicineIndex]);
}

void handlePartialSearch(Medicine medicines[], int registerSize) {
    char query[ARRAY_SIZE];

    printf("Sok lakemedel\n");
    printf("Ange sokstrang: ");
    scanf("%99s", query);

    printf("%-16s %-16s %s\n", "Lakemedel", "Storlekar", "Saldo");
    printf("_________________________________________\n");

    for (int i = 0; i < registerSize; i++) {
        if (medicinePartialSearch(query, i, medicines)) {
            printMedicine(&medicines[i]);
        }
    }
}

void handleAddMedicine(Medicine medicines[], int *registerSize) {
    bool result = true;
    char name[100];

    if (*registerSize >= ARRAY_SIZE) {
        printf("Registret ar fullt.\n");
        return;
    }

    printf("Registrera lakemedel\n");

    while (result) {
        printf("Ange namn: ");
        if (scanf("%20s", name) != 1) return;

        result = medicineSearch(name, medicines, *registerSize);

        if (result) {
            printf("Lakemedlet finns redan\n");
        }
    }

    strcpy(medicines[*registerSize].name, name);

    addSizes(&medicines[*registerSize]);

    (*registerSize)++;
}

void handlePrintMedicine(Medicine medicines[], int registerSize) {
    printf("Antal lakemedel i systemet: %d\n", registerSize);
    printf("%-16s %-16s %s\n", "Lakemedel", "Storlekar", "Saldo");
    printf("_________________________________________\n");

    for (int i = 0; i < registerSize; i++) {
        printMedicine(&medicines[i]);
    }
}

void handleRemoveMedicine(Medicine medicines[], int *registerSize) {
    char input;
    int i;
    
    printf("Avregistrera \n");

    int medicineIndex = searchMedicineIndex(medicines, *registerSize);

    if (medicineIndex == -1) return;
    printf("Vill du avregistrera %s (j/n)? ", medicines[medicineIndex].name);
    scanf(" %c", &input);
    if(input == 'j') {
        for(i = medicineIndex; i < *registerSize-1; i++) {
            medicines[i] = medicines[i+1];
        }
        (*registerSize)--;
    }
}

void handleStockWarnings(Medicine medicines[], int registerSize) {
    char threshold;
    int stockWarning[MEDICINE_SIZE], count, j;
    
    printf("Varningar \n");
    printf("Under vilket saldo vill du ha varningar: ");
    scanf(" %c", &threshold);
    printf("Foljande forpackningar har ett saldo under %d: ", threshold);
    printf("%-16s %-16s %s\n", "Lakemedel", "Storlekar", "Saldo");
    printf("_________________________________________\n");
    
    for(int i = 0; i < registerSize; i++) {
        count = 0;
        for(j = 0; j < registerSize; j++) {
            if(medicines[i].stock[j] < threshold) {
                stockWarning[count] = j;
                count++;
            }
        }
        
        if(count != 0) {
            printf("%-16s ", medicines[i].name);
            j = 0;
            while(j < count) {
                printf("%d, ", medicines[i].sizes[stockWarning[j]]);
                j++;
            }
            printf("%4s", " ");
            j = 0;
            while(j < count) {
                printf("%d, ", medicines[i].stock[stockWarning[j]]);
                j++;
            }
            printf("\n");
        }
    }
}

void handleRemoveSizes(Medicine medicines[ARRAY_SIZE], int registerSize) {
    int input;
    int i, j;
    
    printf("Ta bort storlek \n");

    int medicineIndex = searchMedicineIndex(medicines, registerSize);
    if (medicineIndex == -1) return;
    
    Medicine *medicine = &medicines[medicineIndex];
    while(1) {
        printf("Ange storlek du vill ta bort: ");
        scanf("%d", &input);
        for(i = 0; i < medicine->sizesCount; i++) {
            if(input == medicine->sizes[i]) { 
                for(j = i; j < medicine->sizesCount-1; j++) {
                    medicine->stock[j] = medicine->stock[j+1];
                    medicine->sizes[j] = medicine->sizes[j+1];
                }
                medicine->sizesCount--;
                printf("Storleken %d tas bort for %s. \n", medicine->sizes[i], medicine->name);
                return;
            }
        }
        printf("Den storleken finns ej.\n");
    }
}

void printMedicine(Medicine *medicine) {
    int i = 0;
     
    printf("%-16s ", medicine->name);
    while(medicine->sizesCount > i) {
        printf("%d, ", medicine->sizes[i]);
        i++;
    }
    printf("%4s", " ");
    i = 0;
    while(medicine->sizesCount > i) {
        printf("%d, ", medicine->stock[i]);
        i++;
    }
    printf("%10s", " ");
    printf("\n");
}

bool medicineSearch(char query[], Medicine medicines[], int registerSize) {
    for(int i = 0; i < registerSize; i++) {
        if(!strcmp(query, medicines[i].name)) {
            return true;
        }
    }
    return false;
}

bool medicinePartialSearch(char query[ARRAY_SIZE], int i, Medicine medicines[]) {
    if(strstr(medicines[i].name, query) != NULL) {
        return true;
    }
    return false;
}

int searchMedicineIndex(Medicine medicines[], int registerSize) {
    int medicineIndex = -1;
    int count;
    char query[ARRAY_SIZE];

    if (registerSize == 0) {
        printf("Inga lakemedel registrerade.\n");
        return -1;
    }

    while (1) {
        count = 0;

        printf("Ange sokstrang: ");
        if (scanf("%99s", query) != 1)
            return -1;

        for (int i = 0; i < registerSize; i++) {
            if (medicinePartialSearch(query, i, medicines)) {
                printMedicine(&medicines[i]);
                medicineIndex = i;
                count++;
            }
        }

        if (count == 1)
            break;

        printf("Du fick inte endast ett alternativ. Vanligen gor en ny sokning.\n");
    }

    return medicineIndex;
}

void addSizes(Medicine *medicine) {
    int i = 0;
    
    while (i < MEDICINE_SIZE) {
        printf("Ange storlek (0 för att avsluta): ");
        scanf("%d", &medicine->sizes[medicine->sizesCount]);
        if(medicine->sizes[medicine->sizesCount] == 0) break;
        
        medicine->sizesCount++;
        i++;
    }
}