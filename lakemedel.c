#include "lakemedel.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

Medicine medicines[ARRAY_SIZE] = {0};
int registerSize = 0;

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

void printMedicine(Medicine *medicine) {
    int i = 0;
    
    printf("%-16s %-16s %s \n", "Lakemedel", "Storlekar", "Saldo");
    printf("_________________________________________\n");  
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

bool medicineSearch(char query[]) {
    for(int i = 0; i < registerSize; i++) {
        if(!strcmp(query, medicines[i].name)) {
            return true;
        }
    }
    return false;
}

bool medicinePartialSearch(char query[ARRAY_SIZE], int i) {
    if(strstr(medicines[i].name, query) != NULL) {
        return true;
    }
    return false;
}

int searchMedicineIndex() {
    int i, medicineIndex, count = 0;
    char query[ARRAY_SIZE];

    while(1) {
        printf("Ange sokstrang:");
        scanf("%99s", query);

        printf("Lakemedel         Storlekar         Saldo\n");
        printf("_________________________________________\n");
        for(i = 0; i < registerSize; i++) {
            if(medicinePartialSearch(query, i)) {
                printMedicine(&medicines[i]); 
                medicineIndex = i;
                count++;
            }
        }
        if(count == 1) break; else printf("Du fick inte endast ett alternativ. Vanligen gor en ny sokning.\n");
    }
    return medicineIndex;
}

void handleAdjustStock() {
    int medicineIndex, adjustment, i = 0;
    
    printf("Lagg till storlekar \n");
    medicineIndex = searchMedicineIndex();
    
    Medicine *medicine = &medicines[medicineIndex];
    for(i = 0; i < medicine->sizesCount; i++) {
        printf("Ange andring (+/-) for storlek %d: ", medicine->sizes[i]);
        scanf("%d", &adjustment);
        printf("saldo: %d \n", medicine->stock[i]);
        if(medicine->stock[i] + adjustment < 0 ) {
            printf("VARNING finns endast %d satter saldo till 0. \n", medicine->stock[i]);
            medicine->stock[i] = 0;
        } else medicines->stock[i] += adjustment;
        printf("ny saldo: %d \n", medicines->stock[i]);
    } 
}

void handleAddSizes() {
    int medicineIndex;
    
    printf("Lagg till storlekar \n");
    medicineIndex = searchMedicineIndex();
        
    addSizes(&medicines[medicineIndex]);
}

void handlePartialSearch() {
    char query[ARRAY_SIZE];
    
    printf("Sok lakemedel \n");
    printf("Ange sokstrang: ");
    scanf("%s", query);
    
    printf("Lakemedel Storlekar Saldo\n");
    printf("_________________________\n");
    
    for(int i = 0; i < registerSize; i++) {
        if(medicinePartialSearch(query, i)) printMedicine(&medicines[i]);
    }
}

void handleAddMedicine() {
    bool result = true;
    char name[100];
    
    printf("Registrera lakemedel \n");
    while(result) {
        printf("Ange namn: ");
        scanf("%s", name);
        result = medicineSearch(name);
        if(result) {
            printf("Lakemedlet finns redan \n");
        }
    }
    strcpy(medicines[registerSize].name, name);
    
    addSizes(&medicines[registerSize]);
    registerSize++;
};

void handlePrintMedicine() {  
    for(int i = 0; i < registerSize; i++) {
        printMedicine(&medicines[i]);
    }
}

void writeMedicineToFile(FILE *fp) {
    char name[ARRAY_SIZE];
    
    for (int i = 0; i < registerSize; i++) {
        if (medicines[i].name[0] == '\0') break;
        fprintf(fp, "%s ", medicines[i].name);
        
        for(int j = 0; j < ARRAY_SIZE; j++) {
            if (medicines[i].sizes[j] == 0) break; 
            fprintf(
                fp, 
                "%d %d ",
                medicines[i].sizes[j],
                medicines[i].stock[j]
            );
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}