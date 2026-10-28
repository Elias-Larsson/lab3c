#include "lakemedel.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

Medicine medicineRegister[ARRAY_SIZE] = {0};
int registerSize = 0;

bool medicineSearch(char name[]) {
    for(int i = 0; i < registerSize; i++) {
        if(!strcmp(name, medicineRegister[i].name)) {
            printf("Lakemedlet finns redan \n");
            return true;
        }
    }
    return false;
}

void addMedicine() {
    Medicine *medicine = &medicineRegister[registerSize];

    printf("registrera lakemedel \n");
    printf("Ange namn: \n");
    bool result = true;
    char name[100];
    while(result == true) {
        scanf("%s", name);
        result = medicineSearch(name);
        
    }
    strcpy(medicine->name, name);
    
    for(int i = 0; i < ARRAY_SIZE; i++) {
        printf("Ange storlek (0 för att avsluta): ");
        scanf("%d", &medicine->size[i]);
        if(medicine->size[i] == 0) {
            break;
        }
    }
    registerSize++;
};

void printMedicineRegister() {    
    for(int i = 0; i < registerSize; i++) {
        printf("%s ", medicineRegister[i].name);
        
        for(int j = 0; j < ARRAY_SIZE; j++) {
            if(medicineRegister[i].size[j] == 0) break;
            printf("%d ", medicineRegister[i].size[j]);
        }
        printf("\n");
    }
}

void writeMedicineRegister(FILE *fp) {
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