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
        printf("count: %d",  medicine->sizesCount);
        if(medicine->sizes[medicine->sizesCount] == 0) break;
        
        medicine->sizesCount++;
        i++;
    }
}

void printMedicine(int i) {
    printf("%s ", medicines[i].name);
    
    for(int j = 0; j < MEDICINE_SIZE; j++) {
        if(medicines[i].sizes[j] == 0) break;
        printf("%d ", medicines[i].sizes[j]);
    }
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
                printMedicine(i); 
                medicineIndex = i;
                count++;
            }
        }
        if(count == 1) break; else printf("Du fick inte endast ett alternativ. Vanligen gor en ny sokning.\n");
    }
    return medicineIndex;
}

// void handleAdjustStock() {
//     int medicineIndex;
//     
//     printf("Lagg till storlekar \n");
//     medicineIndex = searchMedicineIndex();
//     while(medicineRegister[medicineIndex].)
// }

void handleAddSizes() {
    int newSize, medicineIndex;
    
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
        if(medicinePartialSearch(query, i)) printMedicine(i);
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
        printMedicine(i);
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