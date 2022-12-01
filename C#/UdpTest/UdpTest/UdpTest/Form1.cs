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

            UdpClient client = new UdpClient("192.168.71.129", 10018);

            data = Encoding.UTF8.GetBytes("kiki");
            client.Send(data, data.Length);

            client.Close();
            Console.WriteLine("Stopping clinet");
        }
    }
}
