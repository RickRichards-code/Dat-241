#include <iostream>
using namespace std;

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
    char operacion;

    // Ingreso de los números y la operación
    cout << "Ingrese el primer número: ";
    cin >> num1;

    cout << "Ingrese el segundo número: ";
    cin >> num2;

    sumar(&num1, &num2, &resultado);
    cout << "La suma de " << num1 << " y " << num2 << " es: " << resultado << endl;

    restar(&num1, &num2, &resultado);
    cout << "La resta de " << num1 << " y " << num2 << " es: " << resultado << endl;

    multiplicar(&num1, &num2, &resultado);
    cout << "La multiplicación de " << num1 << " y " << num2 << " es: " << resultado << endl;
    
    if(num2 == 0) {
        cout << "Error: División por cero." << endl;
    } else {
        dividir(&num1, &num2, &resultado);
        cout << "La división de " << num1 << " entre " << num2 << " es: " << resultado << endl;
    }

    return 0;
}
