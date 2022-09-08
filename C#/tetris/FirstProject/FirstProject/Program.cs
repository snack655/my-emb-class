using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Threading;
using System.Security.Cryptography;

namespace ConsoleApp2
{
    class Program
    {
        
        static int count = 0;
        static int block_num = 1;
        static int[] block_color = new int[2] { 4, 9 };
        static ConsoleColor[] colors = (ConsoleColor[])ConsoleColor.GetValues(typeof(ConsoleColor));


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

        static byte[,] background = new byte[22, 12]
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

        //static byte[,] block_L = new byte[4, 4]
        //{
        //    {0, 0, 0, 0},
        //    {0, 1, 0, 0},
        //    {0, 1, 1, 1},
        //    {0, 0, 0, 0}
        //};

        static byte[,,,] block = new byte[2, 4, 4, 4] 
        {
            {
                { {0, 0, 0, 0},
                  {0, 1, 0, 0},
                  {0, 1, 1, 1},
                  {0, 0, 0, 0} },

                { {0, 0, 0, 0},
                  {0, 1, 1, 0},
                  {0, 1, 0, 0},
                  {0, 1, 0, 0} },

                { {0, 0, 0, 0},
                  {0, 1, 1, 1},
                  {0, 0, 0, 1},
                  {0, 0, 0, 0} },

                { {0, 0, 1, 0},
                  {0, 0, 1, 0},
                  {0, 0, 1, 1},
                  {0, 0, 0, 0} }
            },
            {
                { {0, 0, 0, 0},
                  {0, 1, 1, 0},
                  {0, 1, 1, 0},
                  {0, 0, 0, 0} },

                { {0, 0, 0, 0},
                  {0, 1, 1, 0},
                  {0, 1, 1, 0},
                  {0, 0, 0, 0} },

                { {0, 0, 0, 0},
                  {0, 1, 1, 0},
                  {0, 1, 1, 0},
                  {0, 0, 0, 0} },

                { {0, 0, 0, 0},
                  {0, 1, 1, 0},
                  {0, 1, 1, 0},
                  {0, 0, 0, 0} }
            },
        };

        static int x = 3;
        static int y = 4;
        static int rotate = 0;

        static void Main(string[] args)
        {

            ConsoleKeyInfo key_value;
            String ch;
            make_background();

            make_block();

            while (true)
            {
                if (Console.KeyAvailable)
                {

                    key_value = Console.ReadKey(true); // true를 넣어야 함 -> echo 기능
                    ch = key_value.Key.ToString();

                    if (ch == "A")
                    {
                        if(overlap_check(-1, 0) == 0)
                        {
                            delete_block();
                            x--;
                            make_block();
                        }
                        
                        // Console.WriteLine("a");
                    }
                    else if (ch == "D")
                    {
                        if(overlap_check(1, 0) == 0)
                        {
                            delete_block();
                            x++;
                            make_block();
                        }
                        
                        //Console.WriteLine("d");
                    }
                    else if (ch == "S")
                    {
                        if(overlap_check(0, 1) == 0)
                        {
                            delete_block();
                            y++;
                            make_block();
                        }
                       
                        //Console.WriteLine("s");
                    }
                    else if (ch == "R")
                    {
                        if (overlap_check_rotate() == 0)
                        {
                            delete_block();
                            rotate++;
                            if (rotate > 3) rotate = 0;
                            make_block();
                        }
                    }
                }

                if(count >= 100)
                {
                    count = 0;

                    if (overlap_check(0, 1) == 0)
                    {
                        delete_block();
                        y++;
                        make_block();
                    }
                    else
                    {
                        insert_block();
                        print_background_value();
                        
                        for(int i = 1; i <= 20; i++)
                        {
                            line_check(i);
                        }

                        block_num++;
                        if(block_num > 1)
                        {
                            block_num = 0;
                        }

                        y = 3;
                        x = 3;
                    }
                }


                Thread.Sleep(10);
                count++;
              
                //Thread.Sleep(1000);
                //delete_block();
                //y++;
            }
      
        }

        static void make_background()
        {
            int x_pos = 0;
            int y_pos = 0;
            for (int j = 0; j < 22; j++)
            {
                for (int i = 0; i < 12; i++)
                {
                    if (background[j, i] == 1)
                    {
                        Console.SetCursorPosition(i + x_pos, j + y_pos);
                        Console.Write("*");
                    }
                    else
                    {
                        Console.SetCursorPosition(i + x_pos, j + y_pos);
                        Console.Write("-");
                    }
                }
            }
        }

        static void print_background_value()
        {
            int x_pos = 14;
            int y_pos = 0;
            for (int j = 0; j < 22; j++)
            {
                for (int i = 0; i < 12; i++)
                {
                    if (background[j, i] == 1)
                    {
                        Console.SetCursorPosition(i + x_pos, j + y_pos);
                        Console.Write("1");
                    }
                    else
                    {
                        Console.SetCursorPosition(i + x_pos, j + y_pos);
                        Console.Write("0");
                    }
                }
            }
        }

        static void make_block()
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block[block_num, rotate, j, i] == 1)
                    {
                        Console.ForegroundColor = colors[block_color[block_num]];
                        Console.SetCursorPosition(i + x, j + y);
                        Console.Write("*");
                    }
                    //else
                    //{
                    //    Console.SetCursorPosition(i + x, j + y);
                    //    Console.Write("-");
                    //}
                }
            }
        }

        static void delete_block()
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block[block_num, rotate, j, i] == 1)
                    {
                        Console.ForegroundColor = colors[7];
                        Console.SetCursorPosition(i + x, j + y);
                        Console.Write("-");
                    }
                }
            }
        }

        static int overlap_check(int tmp_x, int tmp_y)
        {
            int overlap_count = 0;
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block[block_num, rotate, j, i] == 1 && background[j + y + tmp_y, i + x + tmp_x] == 1)
                    {
                        overlap_count++;
                    }
                }
            }

            return overlap_count;
        }

        static int overlap_check_rotate()
        {
            int overlap_count = 0;
            int tmp_rotate = rotate;

            tmp_rotate++;
            if (tmp_rotate > 3) tmp_rotate = 0;
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block[block_num, tmp_rotate, j, i] == 1 && background[j + y, i + x] == 1)
                    {
                        overlap_count++;
                    }
                }
            }

            return overlap_count;
        }

        static void insert_block()
        {
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (block[block_num, rotate, j, i] == 1)
                    {
                        background[j + y, i + x] = 1;
                    }
                }
            }
        }

        static void line_check(int line_num)
        {
            int count_block=0;

            for(int i = 0; i < 10; i++)
            {
                if (background[line_num, i+1] == 1)
                {
                    count_block++;
                }
            }

            if(count_block == 10)
            {
                for(int j = line_num; j > 1; j--)
                {
                    for(int i = 0; i < 10; i++)
                    {
                        background[j, i + 1] = background[j-1, i + 1];
                    }
                }

                make_background();
                print_background_value();
            }
        }
    }
}