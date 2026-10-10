#include "lakemedel.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

Lakemedel lakemedelsregister[ARRAY_SIZE];
int registerIndex = 0;

bool lakemedelSök(char ord[]) {
    for(int i = 0; i < registerIndex; i++) {
        if(!strcmp(ord, lakemedelsregister[i].namn)) {
            printf("Lakemedlet finns redan \n");
            return true;
        }
    }
    return false;
}

void registreraLakemedel() {
    Lakemedel *l = &lakemedelsregister[registerIndex];

    printf("registrera lakemedel \n");
    printf("Ange namn: ");
    bool result = true;
    char namn[100];
    while(result == true) {
        scanf("%s", namn);
        result = lakemedelSök(namn);
        
    }
    strcpy(l->namn, namn);
    
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