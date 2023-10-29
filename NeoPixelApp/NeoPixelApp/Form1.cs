using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports; // Abrir los puertos COM

namespace NeoPixelApp
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                // Parametros al abrir la app
                buttonOpen.Enabled = true;
                buttonClose.Enabled = false;
                buttonRed.Enabled = false;
                buttonYellow.Enabled = false;
                buttonBlue.Enabled = false;
                buttonLime.Enabled = false;

                comboBoxBaudRate.Text = "9600";

                progressBar1.Value = 0; //barra en 0

                string[] portlist = SerialPort.GetPortNames(); // retornamos todos los puertos seriales que estan habilitados 
                comboBoxPort.Items.AddRange(portlist);
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }


        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.Close(); //Cerrar el puerto serial
                }

                catch (Exception error)
                {
                    MessageBox.Show(error.Message);
                }
            }
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            try
            {

                serialPort1.PortName = comboBoxPort.Text;
                serialPort1.BaudRate = Convert.ToInt32(comboBoxBaudRate.Text);
                serialPort1.Open();

                buttonClose.Enabled = true;
                buttonOpen.Enabled = false;
                buttonRed.Enabled = true;
                buttonYellow.Enabled = true;
                buttonBlue.Enabled = true;
                buttonLime.Enabled = true;
                progressBar1.Value = 100; // progreso de la barra 100%
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }
        
        private void buttonRed_Click(object sender, EventArgs e)
        {
            serialPort1.WriteLine($"255,0,0,{trackBarI.Value}");
        }

        private void buttonBlue_Click(object sender, EventArgs e)
        {
            serialPort1.WriteLine($"0,0,255,{trackBarI.Value}");
        }

        private void buttonYellow_Click(object sender, EventArgs e)
        {
            serialPort1.WriteLine($"241, 196, 15,{trackBarI.Value}");
        }

        private void buttonLime_Click(object sender, EventArgs e)
        {
            serialPort1.WriteLine($"39, 174, 96,{trackBarI.Value}");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.WriteLine($"91, 44, 111,{trackBarI.Value}");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.WriteLine($"255, 255, 255,{trackBarI.Value}");
        }
    }

}