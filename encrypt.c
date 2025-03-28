#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define PREFIX_LEN 7
#define BUFFER_SIZE 1024  // Tamaño del buffer para leer desde stdin

void encrypt_message(const char *message, size_t length, int output_fd) {
    srand((unsigned int)time(NULL) ^ (unsigned int) getpid()); // Mejor inicialización de semilla aleatoria

    for (size_t i = 0; i < length; i++) {
        unsigned char random_bytes[PREFIX_LEN];
        
        // Generar 7 bytes aleatorios
        for (int j = 0; j < PREFIX_LEN; j++) {
            random_bytes[j] = (unsigned char) rand() % 256;
        }

        // Escribir los 7 bytes aleatorios
        write(output_fd, random_bytes, PREFIX_LEN);
        // Escribir el byte del mensaje original
        write(output_fd, &message[i], 1);
    }
}

int main(int argc, char *argv[]) {
    int output_fd = STDOUT_FILENO; // Por defecto, salida estándar
    char buffer[BUFFER_SIZE];
    size_t message_length = 0;
    char *message = NULL;

    if (argc == 2) {  // Si hay un solo argumento, es el mensaje
        message = argv[1];
        message_length = strlen(message);
    } 
    else if (argc == 3) {  // Si hay dos argumentos, el primero es el archivo de salida
        output_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1) {
            perror("Error al abrir el archivo de salida");
            return 1;
        }
        message = argv[2];
        message_length = strlen(message);
    } 
    else {  
        // Si no hay argumentos, leer desde stdin
        ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            perror("Error al leer desde la entrada estándar");
            return 1;
        }
        message = buffer;
        message_length = (size_t)bytes_read;
    }

    encrypt_message(message, message_length, output_fd);

    if (output_fd != STDOUT_FILENO) {
        close(output_fd);
    }

    return 0;
}