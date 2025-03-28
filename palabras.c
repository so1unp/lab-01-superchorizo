#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int cActual;   
    int unaPalabra = 0; 

    if(1 < argc) {
    for (int i = 1; i < argc; i++)
    {
      printf("%s ",argv[i]);
      printf("\n");  
    }
} else {

    while ((cActual = getchar()) != EOF) {
        if (cActual == ' ' || cActual == '\n') {
            if (unaPalabra) {
                printf("\n");  
                unaPalabra = 0;  
            }
        } else {
            if (!unaPalabra) {
                unaPalabra = 1;  
            }
            printf("%c", cActual);
        }
    }
}
    exit(EXIT_SUCCESS);
}