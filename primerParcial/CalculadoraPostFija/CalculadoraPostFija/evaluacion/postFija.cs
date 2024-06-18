using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculadoraPostFija.evaluacion
{
    public class postFija
    {
        public double Evaluate(string expression)
        {
            Stack<double> stack = new Stack<double>();

            // Separar la expresión por espacios
            string[] tokens = expression.Split(' ');

            foreach (string token in tokens)
            {
                if (string.IsNullOrWhiteSpace(token))
                {
                    continue;
                }

                if (double.TryParse(token, out double number))
                {
                    stack.Push(number);
                    Console.WriteLine($"Pushed number: {number}");
                }
                else
                {
                    // Verificar que haya al menos dos operandos en la pila
                    if (stack.Count < 2)
                    {
                        throw new InvalidOperationException("Expresión postfija no válida. No hay suficientes operandos en la pila.");
                    }

                    double operand2 = stack.Pop();
                    double operand1 = stack.Pop();
                    double result;

                    switch (token)
                    {
                        case "+":
                            result = operand1 + operand2;
                            stack.Push(result);
                            break;
                        case "-":
                            result = operand1 - operand2;
                            stack.Push(result);
                            break;
                        case "*":
                            result = operand1 * operand2;
                            stack.Push(result);
                            break;
                        case "/":
                            result = operand1 / operand2;
                            stack.Push(result);
                            break;
                        case "^":
                            result = Math.Pow(operand1, operand2);
                            stack.Push(result);
                            break;
                        default:
                            throw new InvalidOperationException("Operador desconocido: " + token);
                    }
                    Console.WriteLine($"Applied operator: {token}, result: {result}");
                }
            }

            // Verificar que al final solo haya un valor en la pila
            if (stack.Count != 1)
            {
                throw new InvalidOperationException("Expresión postfija no válida. La pila no contiene exactamente un elemento al final.");
            }

            return stack.Pop();
        }
    }
}
