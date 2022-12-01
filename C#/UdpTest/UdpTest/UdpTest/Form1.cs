using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UdpTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.137.235", 10018);

            data = Encoding.UTF8.GetBytes("led1on");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.137.235", 10018);

            data = Encoding.UTF8.GetBytes("led1of");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.137.235", 10018);

            data = Encoding.UTF8.GetBytes("led2on");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.137.235", 10018);

            data = Encoding.UTF8.GetBytes("led2of");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.137.235", 10018);

            data = Encoding.UTF8.GetBytes("serlef");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            byte[] data = new byte[1024];

            UdpClient client = new UdpClient("192.168.137.235", 10018);

            data = Encoding.UTF8.GetBytes("serrit");
            client.Send(data, data.Length);

            client.Close(); 
            Console.WriteLine("Stopping clinet");
        }
    }
}
