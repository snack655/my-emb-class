using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Threading;

namespace ConsoleApp2
{
    class Program
    {
        
        static int count = 0;
        static byte[] num_byte = new byte[8] { 0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c };

        // byte[,]의 ,은 2차원이라는 것을 알리기 위해 필요한 것
        // ex) 3차원이라면? byte[,,]
        static byte[,] num_byte_2 = new byte[2, 8] {
                {0x00,0x38,0x44,0x04,0x08,0x10,0x20,0x7c},
                {0x00,0x38,0x44,0x04,0x18,0x04,0x44,0x38}
        };

        static byte[,] num_byte_3 = new byte[10, 8] {
            {0x00,0x38,0x44,0x4c,0x54,0x64,0x44,0x38},  //0
            {0x00,0x10,0x30,0x50,0x10,0x10,0x10,0x7c}, //1
            {0x00,0x38,0x44,0x04,0x08,0x10,0x20,0x7c}, //2
            {0x00,0x38,0x44,0x04,0x18,0x04,0x44,0x38}, //3
            {0x00,0x08,0x18,0x28,0x48,0x7c,0x08,0x08}, //4
            {0x00,0x7c,0x40,0x78,0x04,0x04,0x44,0x38}, //5
            {0x00,0x38,0x40,0x40,0x78,0x44,0x44,0x38}, //6
            {0x00,0x7c,0x04,0x08,0x10,0x20,0x20,0x20}, //7
            {0x00,0x38,0x44,0x44,0x38,0x44,0x44,0x38}, //8
            {0x00,0x38,0x44,0x44,0x3c,0x04,0x44,0x38}, //9
        };

        static byte[,] block_L = new byte[4, 4]
        {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 1},
            {0, 0, 0, 0}
        };

        static void Main(string[] args)
        {
            while (true)
            {
                for (int i = 0; i < 2; i++)
                {
                    Console.WriteLine();
                }

                for (int j = 0; j < 4; j++)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        if (block_L[j, i] == 1)
                        {
                            Console.Write("*");
                        }
                        else
                        {
                            Console.Write("-");
                        }
                    }
                    Console.WriteLine();
                }

                Thread.Sleep(1000);
                Console.Clear();
            }
        }
    }
}