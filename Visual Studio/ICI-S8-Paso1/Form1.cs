using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ICI_S8_Paso1
{
    public partial class Form1 : Form
    {
        double temperatura;                     // Variable temperatura
        int grados_servo;                       // Variable grados del servo
        int vel_motor_vs;                       // Variable velocidad motor
        byte pos_servo;                         // Variable para almacenar la posicion del servo Knob1
        byte velocidad;                         // Variable para almacenar la velocidad del motor Knob2
        int t_wait;                             // Variable tiempo de espera
        int vel_barrido;                        // Variable velocidad barrido del servo

        public Form1()
        {
            InitializeComponent();
            serialPort1.Open();
            temperatura = 0;  
            serialPort1.DiscardInBuffer(); // Descarto todo lo que haya en buffer del puerto serie
        }
        // Lectura de la temperatura (T)
        private void button1_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte) 0x54;    // T
                packet[1] = (byte)Convert.ToInt32(textBox2.Text);
                packet[2] = (byte) 0xFF;
                packet[3] = (byte) 0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }
        // Cancelar todos los comandos (C)
        private void button2_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x43;      // C
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            byte[] packet = new byte[4];

            while (serialPort1.BytesToRead >= 4)
            {
                serialPort1.Read(packet, 0, 4);
                if (packet[3] == 0xE0)              // Si la última trama es correcta...
                {
                    if (packet[0] == 0x30)          
                    {
                        temperatura = (double)(packet[1] + packet[2] / 100.0);
                    }
                    else if (packet[0] == 0x20 && packet[3] == 0xE0)    
                    {
                        
                        grados_servo = Convert.ToInt32(packet[1]); 
                    }
                    else if (packet[0] == 0x40)
                    {
                        
                        vel_motor_vs = (int)(packet[1]);
                    }
                }
            }
        }
        // Timer
        private void timer1_Tick(object sender, EventArgs e)
        {
            
            // Mostrar temperatura
            lbDigitalMeter1.Value = temperatura;
            // Mostrar posicion del servo
            textBox1.Text = Convert.ToString(grados_servo);
            // Mostrar velocidad del motor
            lbAnalogMeter1.Value = vel_motor_vs;
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
       // private void Form1_FormClosed(object sender, FormClosedEventArgs e)
       //{
       //     serialPort1.Close();
       // }

       // Activar control servo mediante potenciometro (P)
        private void button3_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x50;     // P
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }
        // Control posición del servo mediante Knob (S)
        private void lbKnob1_KnobChangeValue(object sender, LBSoft.IndustrialCtrls.Knobs.LBKnobEventArgs e)
        {
            byte[] packet = new byte[4];
            pos_servo = Convert.ToByte(lbKnob1.Value);
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x53;
                packet[1] = pos_servo;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void lbAnalogMeter1_Load(object sender, EventArgs e)
        {

        }
        // Control del motor paso a paso mediante Knob (M)
        private void lbKnob2_KnobChangeValue(object sender, LBSoft.IndustrialCtrls.Knobs.LBKnobEventArgs e)
        {
            byte[] packet = new byte[4];
            velocidad = Convert.ToByte(lbKnob2.Value);
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x4D;         // M
                packet[1] = velocidad;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }
        // Botón giro izquierda (I)
        private void button4_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x49;
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }
        // Botón Giro derecha (D)
        private void button5_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x44;
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
        // Apertura y cierre (A)
        private void button6_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x41;
                t_wait = Convert.ToInt32(textBox3.Text);
                packet[1] = (byte)t_wait;
                vel_barrido = Convert.ToInt32(textBox4.Text);
                packet[2] = (byte)vel_barrido;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);


            }
        }
        // Mostrar en el display (X)
        private void button7_Click(object sender, EventArgs e)
        {
            byte[] packet = new byte[4];
            if (serialPort1.IsOpen)
            {
                packet[0] = (byte)0x58;             // X
                packet[1] = (byte)0xFF;
                packet[2] = (byte)0xFF;
                packet[3] = (byte)0xE0;
                serialPort1.Write(packet, 0, 4);
            }
        }
        // Cerrar puerto serie
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
       {
            serialPort1.Close();
        }

        private void button8_Click(object sender, EventArgs e)
        {
           
        }
    }
}
