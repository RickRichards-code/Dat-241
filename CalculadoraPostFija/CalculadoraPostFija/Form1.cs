using System;
using System.Windows.Forms;
using CalculadoraPostFija.evaluacion;

namespace CalculadoraPostFija
{
    public partial class Form1 : Form
    {

        private string expression = "";
        private postFija calculator = new postFija();

        public Form1()
        {
            InitializeComponent();
        }

        private void btnNumber_Click(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            expression += button.Text;
            textBox1.Text = expression;
        }

        private void btnOperator_Click(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            expression += " " + button.Text + " ";
            textBox1.Text = expression;
        }

        private void btnDecimal_Click(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            expression += button.Text + " ";
            textBox1.Text = expression;
        }

        private void btnEqual_Click(object sender, EventArgs e)
        {
            try
            {
                string trimmedExpression = expression.Trim();
                Console.WriteLine("Expresión a evaluar: " + trimmedExpression);
                string[] tokens = trimmedExpression.Split(' ');
                foreach (var token in tokens)
                {
                    Console.WriteLine("Token: " + token);
                }

                double result = calculator.Evaluate(trimmedExpression);
                textBox1.Text = result.ToString();
                expression = result.ToString(); // Actualiza la expresión con el resultado
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
                expression = "";
                textBox1.Clear();
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            expression = "";
            textBox1.Clear();
        }

        

        private void button10_Click(object sender, EventArgs e)
        {
            expression += " ";
            textBox1.Text = expression;
        }

        private void button19_Click(object sender, EventArgs e)
        {

            if (textBox1.Text.Length > 0)
                textBox1.Text = textBox1.Text.Remove(textBox1.Text.Length - 1, 1);

        }
    }
}   
