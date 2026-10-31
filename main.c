#include "lakemedel.h"
#include <stdio.h>
#include <string.h>

void writeToFile(FILE *fp, Medicine medicines[ARRAY_SIZE], int registerSize);
void readFromFile(FILE *fp, Medicine medicines[ARRAY_SIZE], int registerSize);

int main(void){
    FILE *fp;
    char file[ARRAY_SIZE]; 
    Medicine medicines[ARRAY_SIZE] = {0};
    int registerSize = 0;
    int menuInput;
    
    printf("Textfil: ");
    scanf("%99s", file);    
    fp = fopen(file, "r");
    
    if(fp==NULL) {
        printf("Fil saknas skapar en ny \n");
        strcpy(file, "lakemedel.txt");
    } else fclose(fp);
    
    fp = fopen(file, "w");
    while(1) {
        printf(" (1) Registrera nytt lakemedel \n (2) Skriva ut alla lakemedel \n "
               "(3) Soka efter lakemedel \n (4) Lagg till storlekar \n (5) Andra "
               "lagersaldot för ett lakemedel \n (6) Avregistrera lakemedel \n (7) "
               "Varningar \n (8) Avsluta \n");
        scanf("%d", &menuInput);
        
        if(menuInput == 8) break;
        switch (menuInput) {
            case 1: handleAddMedicine(medicines, &registerSize);
            break;
            case 2: handlePrintMedicine(medicines, registerSize);
            break;
            case 3: handlePartialSearch(medicines, registerSize);
            break;
            case 4: handleAddSizes(medicines, registerSize);
            break;
            case 5: handleAdjustStock(medicines, registerSize);
            break;
        }
    }   
        writeToFile(fp, medicines, registerSize);
}

void writeToFile(FILE *fp, Medicine medicines[ARRAY_SIZE], int registerSize) {
    char name[ARRAY_SIZE];
    
    for (int i = 0; i < registerSize; i++) {
        if (medicines[i].name[0] == '\0') break;
        fprintf(fp, "%s ", medicines[i].name);
        
        for(int j = 0; j < MEDICINE_SIZE; j++) {
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