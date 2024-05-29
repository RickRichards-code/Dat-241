#include <stdio.h>

// Función para sumar dos números usando punteros
void sumar(int *a, int *b, int *resultado) {
    *resultado = *a + *b;
}

// Función para restar dos números usando punteros
void restar(int *a, int *b, int *resultado) {
    *resultado = *a - *b;
}

// Función para multiplicar dos números usando sumas repetidas
void multiplicar(int *a, int *b, int *resultado) {
    int multiplicando = *a;
    int multiplicador = *b;
    *resultado = 0;
    for(int i = 0; i < multiplicador; i++) {
        *resultado += multiplicando;
    }
}

// Función para dividir dos números usando restas repetidas
void dividir(int *a, int *b, int *resultado) {
    int dividendo = *a;
    int divisor = *b;
    *resultado = 0;
    while(dividendo >= divisor) {
        dividendo -= divisor;
        (*resultado)++;
    }
}


int main() {
    int num1, num2;
    int resultado;


    printf("Ingrese el primer número: ");
    scanf("%d", &num1);

    printf("Ingrese el segundo número: ");
    scanf("%d", &num2);

    sumar(&num1, &num2, &resultado);
    printf("La suma de %d y %d es: %d\n", num1, num2, resultado);

    restar(&num1, &num2, &resultado);
    printf("La resta de %d y %d es: %d\n", num1, num2, resultado);

    multiplicar(&num1, &num2, &resultado);
    printf("La multiplicación de %d y %d es: %d\n", num1, num2, resultado);

    if (num2 != 0)
    {
        dividir(&num1, &num2, &resultado);
        printf("La división de %d entre %d es: %d\n", num1, num2, resultado);
    } else {
        printf("no se puede entre 0\n");
    }
    
    

    return 0;
}
