using System;
using System.IO.Ports;
using System.Windows.Forms;

namespace SerialTest
{
    public partial class Form1 : Form
    {

        SerialPort port;

        public Form1()
        {
            InitializeComponent();
        }


        private void button1_Click(object sender, EventArgs e)
        {
            port.WriteLine("LED ON 1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            port.WriteLine("LED OFF 1");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            port.WriteLine("LEFT");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            port.WriteLine("RIGHT");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            // connect
            port = new SerialPort();
            if (port.IsOpen == false)
            {
                port.PortName = "COM4";
                port.BaudRate = 9600;
                port.DataBits = (int)8;
                port.Parity = Parity.None;
                port.StopBits = StopBits.One;
                port.ReadTimeout = (int)500;
                port.WriteTimeout = (int)500;

                port.Open();
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            // close
            if (port.IsOpen == true)
            {
                port.Close();
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            port.WriteLine("LED ON 2");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            port.WriteLine("LED OFF 2");
        }
    }
}
