#include "lakemedel.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

Medicine medicineRegister[ARRAY_SIZE] = {0};
int registerSize = 0;

void printMedicine(int i) {
    printf("%s ", medicineRegister[i].name);
    
    for(int j = 0; j < MEDICINE_SIZE; j++) {
        if(medicineRegister[i].size[j] == 0) break;
        printf("%d ", medicineRegister[i].size[j]);
    }
    printf("\n");
}

bool medicineSearch(char query[]) {
    for(int i = 0; i < registerSize; i++) {
        if(!strcmp(query, medicineRegister[i].name)) {
            return true;
        }
    }
    return false;
}

bool medicinePartialSearch(char query[ARRAY_SIZE], int i) {
    if(strstr(medicineRegister[i].name, query) != NULL) {
        return true;
    }
    return false;
}

int searchMedicineIndex(char query[]) {
    int i, count = 0;
    int medicineIndex;
    
    printf("Lakemedel         Storlekar         Saldo\n");
    printf("_________________________________________\n");
    for(i = 0; i < registerSize; i++) {
        if(medicinePartialSearch(query, i)) {
            printMedicine(i); 
            medicineIndex = i;
            count++;
        }
    }
    if(count==1) return medicineIndex; else return -1;
}

void handleAddSizes() {
    char query[ARRAY_SIZE];
    int i, count, medicineIndex;
    
    printf("Lagg till storlekar \n");
    while(1) {
        printf("Ange sokstrang:");
        scanf("%99s", query);

        medicineIndex = searchMedicineIndex(query);
        if(medicineIndex != -1) break; else printf("Du fick inte endast ett alternativ. Vanligen gor en ny sokning.\n");
    }
    
    int j;
    int newSize;
    
    while(j < MEDICINE_SIZE && medicineRegister[medicineIndex].size[j] != 0) j++;
    
    while(j < MEDICINE_SIZE) {
        printf("Ange ny storlek: "); 
        scanf("%d", &newSize);
        if(newSize == 0) break;
      
        medicineRegister[medicineIndex].size[j] = newSize;
        j++;
    }
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
    Medicine *medicine = &medicineRegister[registerSize];

    printf("Registrera lakemedel \n");
    bool result = true;
    char name[100];
    while(result == true) {
        printf("Ange namn: ");
        scanf("%s", name);
        result = medicineSearch(name);
        if(result) {
            printf("Lakemedlet finns redan \n");
        }
    }
    strcpy(medicine->name, name);
    
    for(int i = 0; i < MEDICINE_SIZE; i++) {
        printf("Ange storlek (0 för att avsluta): ");
        scanf("%d", &medicine->size[i]);
        if(medicine->size[i] == 0) {
            break;
        }
    }
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
        if (medicineRegister[i].name[0] == '\0') break;
        fprintf(fp, "%s ", medicineRegister[i].name);
        
        for(int j = 0; j < ARRAY_SIZE; j++) {
            if (medicineRegister[i].size[j] == 0) break; 
            fprintf(
                fp, 
                "%d %d ",
                medicineRegister[i].size[j],
                medicineRegister[i].stock[j]
            );
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}