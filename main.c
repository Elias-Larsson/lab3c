#include "lakemedel.h"
#include <stdio.h>
#include <string.h>
#define ARRAY_SIZE 100

int main(void){
    FILE *fp;
    char textfil[ARRAY_SIZE];   
    int menuInput;
    printf("textfil: ");
    scanf("%99s", textfil);    
    fp = fopen(textfil, "r");
    
    if(fp==NULL) {
        printf("Fil saknas skapar en ny \n");
        strcpy(textfil, "lakemedel.txt");
    } else fclose(fp);
    
    fp = fopen(textfil, "a");
    while(1==1) {
        printf("(1) Registrera nytt lakemedel \n (2) Skriva ut alla lakemedel \n "
               "(3) Soka efter lakemedel \n (4) Lagg till storlekar \n (5) Andra "
               "lagersaldot för ett lakemedel \n (6) Avregistrera lakemedel \n (7) "
               "Varningar \n (8) Avsluta \n");
        scanf("%d",&menuInput);
        if(menuInput == 8) break;
        switch (menuInput) {
            case 1: registreraLakemedel();
            break;
            case 2: skrivUtLakemedel();
            break;
        }
    }
    fclose(fp); //skriv och stäng till lakemedel.txt
}
