#include "lakemedel.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

Lakemedel lakemedelsregister[ARRAY_SIZE];
int registerIndex = 0;

void registreraLakemedel() {
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
    registerIndex++;
};

void skrivUtLakemedel() {    
    for(int i = 0; i < registerIndex; i++) {
        printf("%s ", lakemedelsregister[i].namn);
        for(int j = 0; j < ARRAY_SIZE; j++) {
            if(lakemedelsregister[i].storlek[j] == 0) {
                break;
            }
            printf("%d ", lakemedelsregister[i].storlek[j]);
        }
    }
}