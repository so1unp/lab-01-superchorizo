#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define RANDOM_BYTE_COUNT 7

int main(int argc, char *argv[]) {
    int input_fd = STDIN_FILENO;

    // Si se pasa un archivo, abrirlo
    if (argc == 2) {
        input_fd = open(argv[1], O_RDONLY);
        if (input_fd == -1) {
            perror("open");
            return 1;
        }
    }

    unsigned char random_bytes[RANDOM_BYTE_COUNT];
    unsigned char message_byte;

    // Leer el archivo o entrada estándar y desencriptar
    while (read(input_fd, random_bytes, RANDOM_BYTE_COUNT) == RANDOM_BYTE_COUNT) {
        // Leer el siguiente byte del mensaje
        if (read(input_fd, &message_byte, 1) != 1) {
            perror("read");
            return 1;
        }

        // Imprimir el byte desencriptado
        write(STDOUT_FILENO, &message_byte, 1);
    }

    // Cerrar archivo de entrada si es necesario
    if (input_fd != STDIN_FILENO) {
        close(input_fd);
    }
    printf("\n");

    return 0;
}