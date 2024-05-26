#include <iostream>

// Función para sumar dos números
int suma(int a, int b) {
    return a + b;
}

// Función para restar dos números
int resta(int a, int b) {
    return a - b;
}

// Función para multiplicar dos números (en base a sumas)
int multiplicacion(int a, int b) {
    int resultado = 0;
    for (int i = 0; i < b; i++) {
        resultado += a;
    }
    return resultado;
}

// Función para dividir dos números (en base a restas)
int division(int a, int b) {
    int cociente = 0;
    while (a >= b) {
        a -= b;
        cociente++;
    }
    return cociente;
}

int main() {
    int a = 10, b = 3;
    int sum = suma(a, b);
    int rest = resta(a, b);
    int producto = multiplicacion(a, b);
    int cociente = division(a, b);

    std::cout << "Suma: " << sum << std::endl;
    std::cout << "Resta: " << rest << std::endl;
    std::cout << "Multiplicación: " << producto << std::endl;
    std::cout << "División: " << cociente << std::endl;

    return 0;
}

