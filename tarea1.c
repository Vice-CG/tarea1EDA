#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función encode: realiza la sustitución de caracteres
void encode(FILE* input, FILE* output, char* palabra1, char* palabra2) {
    char c;
    
    // Leer el archivo carácter por carácter
    while ((c = fgetc(input)) != EOF) {
        // Reemplazar los caracteres de acuerdo con la correspondencia de palabra1 -> palabra2
        for (int i = 0; i < strlen(palabra1); i++) {
            if (c == palabra1[i]) {
                fputc(palabra2[i], output);  // Reemplazar el carácter
                break;  // Salir del bucle al realizar el reemplazo
            }
        }
        // Si no se hace ningún reemplazo, se escribe el carácter tal cual en el archivo de salida
        if (c != palabra1[0] && c != palabra1[1] && c != palabra1[2] && c != palabra1[3]) {
            fputc(c, output);
        }
    }
}

// Función que maneja la lectura del archivo y la ejecución de una función sobre el archivo
void procesarArchivo(const char* archivo_entrada, const char* archivo_salida, void (*funcion)(FILE*, FILE*, char*, char*), char* palabra1, char* palabra2) {
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

    // Llamamos a la función de transformación (encode)
    funcion(file_in, file_out, palabra1, palabra2);

    fclose(file_in);
    fclose(file_out);
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Uso: ./tarea1 [nombre del archivo txt] [encode/decode] [palabra 1] [palabra 2] [nombre del archivo txt nuevo]\n");
        return 1;
    }

    // Verificamos que las palabras tengan el mismo largo
    if (strlen(argv[3]) != strlen(argv[4])) {
        printf("Las palabras clave deben tener la misma longitud.\n");
        return 1;
    }

    // Verificamos que la operación sea "encode"
    if (strcmp(argv[2], "encode") == 0) {
        // Llamamos a la función de procesamiento de archivo
        procesarArchivo(argv[1], argv[5], encode, argv[3], argv[4]);
    } else {
        printf("Operación no soportada. Solo se soporta 'encode'.\n");
        return 1;
    }

    return 0;
}