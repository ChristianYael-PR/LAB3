#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mapeo de los dígitos a las letras correspondientes del teclado telefónico
const char *phoneMap[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

// Función recursiva para generar todas las combinaciones posibles
void backtrack(char *digits, int index, char *current, char **result, int *count) {
    if (digits[index] == '\0') {  // Caso base: si llegamos al final de los dígitos, almacenamos la combinación
        result[*count] = strdup(current);  // Guardamos la combinación en el array de resultados
        (*count)++;  // Incrementamos el contador de combinaciones
        return;  // Retornamos para probar otra combinación
    }
    
    const char *letters = phoneMap[digits[index] - '0'];  // Obtenemos las letras correspondientes al dígito actual
    for (int i = 0; letters[i] != '\0'; i++) {  // Iteramos sobre cada letra posible
        current[index] = letters[i];  // Agregamos la letra a la combinación actual
        backtrack(digits, index + 1, current, result, count);  // Llamado recursivo para el siguiente dígito
    }
}

// Función principal que inicia el proceso de generación de combinaciones
char **letterCombinations(char *digits, int *returnSize) {
    if (*digits == '\0') {  // Si la entrada está vacía, devolvemos un array vacío
        *returnSize = 0;
        return NULL;
    }
    
    int maxComb = 1;  // Variable para almacenar el número máximo de combinaciones posibles
    for (int i = 0; digits[i] != '\0'; i++) {  // Calculamos el número máximo de combinaciones posibles
        maxComb *= strlen(phoneMap[digits[i] - '0']);  // Multiplicamos las posibilidades por cada dígito
    }
    
    char **result = (char **)malloc(maxComb * sizeof(char *));  // Reservamos memoria para el array de resultados
    char current[5] = {0};  // Array para almacenar la combinación actual (máximo 4 caracteres + terminador nulo)
    int count = 0;  // Contador de combinaciones generadas
    
    backtrack(digits, 0, current, result, &count);  // Llamamos a la función recursiva para generar combinaciones
    
    *returnSize = count;  // Guardamos el número total de combinaciones generadas
    return result;  // Retornamos el array de combinaciones
}

int main() {
    char digits[5];  // Array para almacenar los dígitos ingresados por el usuario (máximo 4 + terminador nulo)
    printf("Ingrese los dígitos: ");  // Solicitamos al usuario que ingrese los dígitos
    scanf("%4s", digits);  // Leemos los dígitos ingresados (máximo 4 caracteres para evitar desbordamiento)
    
    int returnSize;  // Variable para almacenar el número de combinaciones generadas
    char **combinations = letterCombinations(digits, &returnSize);  // Llamamos a la función para obtener combinaciones
    
    printf("[ ");  // Imprimimos el inicio del array de combinaciones
    for (int i = 0; i < returnSize; i++) {  // Iteramos sobre todas las combinaciones generadas
        printf("\"%s\"%s", combinations[i], (i < returnSize - 1) ? ", " : "");  // Imprimimos cada combinación
        free(combinations[i]);  // Liberamos la memoria asignada para cada combinación
    }
    printf(" ]\n");  // Cerramos la impresión del array
    
    free(combinations);  // Liberamos la memoria asignada para el array de combinaciones
    return 0;  // Finalizamos el programa
}

