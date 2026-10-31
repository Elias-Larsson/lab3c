#include "lakemedel.h"
#include <stdio.h>
#include <string.h>

void writeToFile(FILE *fp, Medicine medicines[ARRAY_SIZE], int registerSize);
void readFromFile(FILE *fp, Medicine medicines[ARRAY_SIZE], int *registerSize);

int main(void){
    FILE *fp;
    char file[ARRAY_SIZE]; 
    Medicine medicines[ARRAY_SIZE] = {0};
    int registerSize = 0;
    int menuInput;
    
    printf("Textfil: ");
    scanf("%99s", file);    
    fp = fopen(file, "r");

    if(fp!=NULL) {
        readFromFile(fp, medicines, &registerSize);
        fclose(fp);
        printf("%d lakemedel lasta fran fil. \n", registerSize);
    } else printf("Fil saknas skapar en ny \n");
    
    while(1) {
        printf(" (1) Registrera nytt lakemedel \n (2) Skriva ut alla lakemedel \n "
               "(3) Soka efter lakemedel \n (4) Lagg till storlekar \n (5) Andra "
               "lagersaldot för ett lakemedel \n (6) Avregistrera lakemedel \n (7) "
               "Varningar \n (8) Avsluta \n");
        scanf("%d", &menuInput);
        
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
            case 6: handleRemoveMedicine(medicines, &registerSize);
            break;
            case 7:
            break;
            case 8:
                fp = fopen(file, "w");
                if(fp != NULL) {
                    printf("Programmet avslutar och skriver till filen: %s \n", file);
                    writeToFile(fp, medicines, registerSize);
                }
            break;
        }
    }   
}

void writeToFile(FILE *fp, Medicine medicines[ARRAY_SIZE], int registerSize) {
    for (int i = 0; i < registerSize; i++) {
        fprintf(fp, "%s %d ", medicines[i].name, medicines[i].sizesCount);

        for (int j = 0; j < medicines[i].sizesCount; j++) {
            fprintf(fp, "%d %d ",
                    medicines[i].sizes[j],
                    medicines[i].stock[j]);
        }

        fprintf(fp, "\n");
    }
    fclose(fp);
}

void readFromFile(FILE *fp, Medicine medicines[ARRAY_SIZE], int *registerSize) {
    int j, i = *registerSize;

    while (i < ARRAY_SIZE &&
           fscanf(fp, "%20s %d",
                  medicines[i].name,
                  &medicines[i].sizesCount) == 2) {
                      
        if (medicines[i].sizesCount < 0 || medicines[i].sizesCount > MEDICINE_SIZE) {
            printf("Felaktigt antal storlekar i filen. \n");
            break;
        }
        
        for (j = 0; j < medicines[i].sizesCount; j++) {
            fscanf(fp, "%d %d",
                   &medicines[i].sizes[j],
                   &medicines[i].stock[j]);
        }
        i++;
    }
    *registerSize = i;
}