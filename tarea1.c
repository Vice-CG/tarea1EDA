#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función encode: realiza la sustitución de caracteres
void encode(FILE* input, FILE* output, char* palabra1, char* palabra2) {
    char c;
    
    while ((c = fgetc(input)) != EOF) {
        int reemplazado = 0;
        for (int i = 0; i < strlen(palabra1); i++) {
            if (c == palabra1[i]) {
                fputc(palabra2[i], output);
                reemplazado = 1;
                break;
            }
        }
        if (!reemplazado) {
            fputc(c, output);
        }
    }
}

// Función decode: realiza la sustitución inversa de caracteres
void decode(FILE* input, FILE* output, char* palabra1, char* palabra2) {
    char c;
    
    while ((c = fgetc(input)) != EOF) {
        int reemplazado = 0;
        for (int i = 0; i < strlen(palabra2); i++) {
            if (c == palabra2[i]) {
                fputc(palabra1[i], output);
                reemplazado = 1;
                break;
            }
        }
        if (!reemplazado) {
            fputc(c, output);
        }
    }
}

// Función general para procesar archivos
void procesarArchivo(const char* archivo_entrada, const char* archivo_salida,
                     void (*funcion)(FILE*, FILE*, char*, char*),
                     char* palabra1, char* palabra2) {
    FILE* file_in = fopen(archivo_entrada, "r");
    if (file_in == NULL) {
        perror("No se pudo abrir el archivo de entrada");
        return;
    }

    FILE* file_out = fopen(archivo_salida, "w");
    if (file_out == NULL) {
        perror("No se pudo abrir el archivo de salida");
        fclose(file_in);
        return;
    }

    funcion(file_in, file_out, palabra1, palabra2);

    fclose(file_in);
    fclose(file_out);
}

int main(int argc, char *argv[]) {
    if (argc < 6) {
        printf("Uso: ./tarea1 [archivo entrada] [encode/decode] [palabra 1] [palabra 2] [archivo salida]\n");
        return 1;
    }

    if (strlen(argv[3]) != strlen(argv[4])) {
        printf("Las palabras clave deben tener la misma longitud.\n");
        return 1;
    }

    if (strcmp(argv[2], "encode") == 0) {
        procesarArchivo(argv[1], argv[5], encode, argv[3], argv[4]);
    } else if (strcmp(argv[2], "decode") == 0) {
        procesarArchivo(argv[1], argv[5], decode, argv[3], argv[4]);
    } else {
        printf("Operación no soportada. Use 'encode' o 'decode'.\n");
        return 1;
    }

    return 0;
}
