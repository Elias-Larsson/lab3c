#include <stdio.h>
#include <string.h>
#define ARRAY_SIZE 100
struct lakamedel{
    int saldo[ARRAY_SIZE];
    int storlek[ARRAY_SIZE];
    char namn[ARRAY_SIZE];
};
typedef struct lakamedel Lakamedel ;

Lakamedel lakamedelsregister[ARRAY_SIZE];
int registerIndex = 0;

void registreraLakamedel(char namn[], int storlek[]) {
    Lakamedel l = lakamedelsregister[registerIndex];
    
    strcpy(l.namn, namn);
    printf("%s \n",l.namn);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        l.storlek[i] = storlek[i];
        if(l.storlek[i] > 0) {
            printf("%d ", l.storlek[i]);
        }
    }
    lakamedelsregister[registerIndex] = l;
    registerIndex++;
    // spara i lakamedel.txt
};

int main(void){

    
    FILE *fp;
    char textfil[ARRAY_SIZE];   
    int menuInput;
    printf("textfil: ");
    scanf("%99s", textfil);    
    fp = fopen(textfil, "r");
    
    if(fp==NULL) {
        printf("Fil saknas skapar en ny \n");
        strcpy(textfil, "lakamedel.txt");
        fp = fopen(textfil, "w");
    }
    printf(" (1) Registrera nytt lakemedel \n (2) Skriva ut alla lakemedel \n (3) Soka efter lakemedel \n (4) Lagg till storlekar \n (5) Andra lagersaldot för ett lakemedel \n (6) Avregistrera lakemedel \n (7) Varningar \n (8) Avsluta \n");
    
    scanf("%d",&menuInput);
    switch (menuInput) {
        case 1: 
            printf("registrera lakamedel \n");
            char namn[ARRAY_SIZE];
            int storlek[ARRAY_SIZE] = {0};
            printf("Ange namn:");
            scanf("%99s", namn);
            // om läkemedel finns redan iterera och skriv 'finns redan'
            for(int i = 0; i < ARRAY_SIZE; i++) {
                printf("Ange storlek:");
                scanf("%d", &storlek[i]);
                if(storlek[i] == 0) {
                    break;
                }
                
            }
            registreraLakamedel(namn, storlek);
        break;

    }

}
