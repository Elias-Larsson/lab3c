#include <stdio.h>
#include <string.h>

int main(void){
    struct Lakamedel{
        int saldo[100];
        int storlek[100];
        char namn[];
    };
    
    FILE *fp;
    char textfil[100];   
    
    printf("textfil: ");
    scanf("%99s", textfil);
    printf("%s \n", textfil);
    
    fp = fopen(textfil, "r");
    
    if(fp==NULL) {
        printf("Fil saknas skapar en ny \n");
        strcpy(textfil, "lakamedel.txt");
        fp = fopen(textfil, "w");
        printf("%99s", textfil);
    }

}