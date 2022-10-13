using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace tetris
{
    public partial class Form1 : Form
    {
        int x = 0;
        int y = 0;

        byte[,] block_L = new byte[4, 4]
        {
            { 0, 0, 0, 0 },
            { 0, 1, 0, 0 },
            { 0, 1, 1, 1 },
            { 0, 0, 0, 0 }
        };

        byte[,] background = new byte[22, 12]
        {
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        };

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            make_block();
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (overlap_check(0, 1) == 0)
            {
                delete_block();
                y++;
                make_block();
            }

        }

        void make_block()
        {

            Graphics g = this.panel1.CreateGraphics();
            Pen p = new Pen(Color.Red, 2);
            Rectangle rec;



            for (int j = 0; j < 4; j++)
            {
                for(int i = 0; i < 4; i++)
                {
                    if (block_L[j, i] == 1)
                    {
                        rec = new Rectangle( (0 + 3) + (x * 22) + (i * 22), (0 + 3) + (y * 22) + (j * 22), 18, 18);
                        g.DrawRectangle(p, rec);

                    }
                }
            }

            p.Dispose();
            g.Dispose();
        }

        void delete_block()
        {

            Graphics g = this.panel1.CreateGraphics();
            Pen p = new Pen(Color.White, 2);
            Rectangle rec;



            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block_L[j, i] == 1)
                    {
                        rec = new Rectangle((0 + 3) + (x * 22) + (i * 22), (0 + 3) + (y * 22) + (j * 22), 18, 18);
                        g.DrawRectangle(p, rec);

                    }
                }
            }

            p.Dispose();
            g.Dispose();
        }

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if(e.KeyChar =='a')
            {
                if (overlap_check(-1, 0) == 0)
                {
                    delete_block();
                    x--;
                    make_block();
                }
            } else if (e.KeyChar == 'd')
            {
                if (overlap_check(1, 0) == 0)
                {
                    delete_block();
                    x++;
                    make_block();
                }
            } else if (e.KeyChar == 's')
            {
                if (overlap_check(0, 1) == 0)
                {
                    delete_block();
                    y++;
                    make_block();
                }
            }
        }

        int overlap_check(int offset_x, int offset_y)
        {
            int overlap_count = 0;

            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block_L[j, i] == 1 && background[j + y + 1 + offset_y, i + x + 1 + offset_x] == 1)
                    {
                        overlap_count++;

                    }
                }
            }
            return overlap_count;
        }
    }
}
