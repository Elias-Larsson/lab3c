#include "lakemedel.h"
#include "repository.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct lakemedel Lakemedel ;

Lakemedel lakemedelsregister[ARRAY_SIZE];
int registerIndex = 0;

void registreraLakemedel(FILE *fp) {
    Lakemedel *l = &lakemedelsregister[registerIndex];

    printf("registrera lakemedel \n");
    printf("Ange namn: ");
    scanf("%99s", l->namn);
    
    for(int i = 0; i < ARRAY_SIZE; i++) {
        printf("Ange storlek (0 för att avsluta): ");
        scanf("%d", &l->storlek[i]);
        if(l->storlek[i] == 0) {
            break;
        }
        
    }

    bool resultat = skrivLakemedel(fp, l);
    if(!resultat) {
        printf("error vid registrering av läkemedel till textfil"); 
    }
    
    // använd på meny 2
    // for (int i = 0; i < ARRAY_SIZE; i++) {
    //     l->storlek[i] = storlek[i];
    //     if(l->storlek[i] > 0) {
    //         printf("%d ", l->storlek[i]);
    //     }
    // }
    registerIndex++;
};