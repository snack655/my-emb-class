import msvcrt
import time
import os
import ctypes
import numpy as np

def cls():
    os.system('cls')
     

def gotoxy(x,y):
    ctypes.windll.kernel32.SetConsoleCursorPosition(ctypes.windll.kernel32.GetStdHandle(-11),(((y&0xFFFF)<<0x10)|(x&0xFFFF)))

def draw_background():
    for j in range(0, 22):
        for i in range(0, 12):
            if background[j, i] == 1:
                print("*", end="")
            else:
                print("-", end="")
        print("")
        
def print_background_value():
    for j in range(0, 22):
        for i in range(0, 12):
            if background[j, i] == 1:
                gotoxy(i+15, j)
                print("1")
            else:
                gotoxy(i+15, j)
                print("0")       
       
def make_block():
    for j in range(0, 4):
        for i in range(0, 4):
            if (block[block_num, j, i] == 1):
                gotoxy(i+x, j+y)
                print("\033[%dm" % text_color[block_num] + "*" + '\033[0m')

def delete_block():
    for j in range(0, 4):
        for i in range(0, 4):
            if (block[block_num, j, i] == 1):
                gotoxy(i+x, j+y)
                print("-")
               
# def my_overlap_check(tmp_x, tmp_y):
#     overlap_count = 0
   
#     if((x + tmp_x + 1) <= 0):
#         overlap_count += 1
#     else:
#         sumArray = sum(background[y + tmp_y + 1 : y + tmp_y + 3, x + tmp_x + 1  : x + tmp_x + 4] & block_L[1:3, 1:])
       
#         for i in sumArray:
#             if i == 1:
#                 overlap_count += 1
       
    # return overlap_count

def teacher_overlap_check(xx, yy):
    overlap_count = 1
    if ((x + xx) >= 0) and ((x + xx) <= 8) and ((y + yy) <= 18): 
        tmp_back = background[0 + y + yy: 4 + y + yy, 0 + x + xx:4 + x + xx]
        overlap_block = tmp_back & block[block_num]
        overlap_count = overlap_block.sum()
    return overlap_count

def overlap_check_rotate():
    overlap_count = 1
    # tmp_rotate = rotate
    # tmp_rotate += 1
    # if tmp_rotate == 4:
    #     tmp_rotate = 0
    
    if (x >= 0) and (x <= 8) and (y <= 18): 
        tmp_back = background[0 + y: 4 + y, 0 + x:4 + x]
        tmp_block_L = np.dot(block[block_num].T, reverse_col) * (-1)
        overlap_block = (tmp_back & tmp_block_L)
        overlap_count = overlap_block.sum()
        
    return overlap_count

def insert_block():
    for j in range(0, 4):
        for i in range(0, 4):
            if (block[block_num, j, i] == 1):
                background[j + y, i + x] = 1
                
def line_check(line_num):
    count_block = 0
    
    for i in range(0, 10):
        if background[line_num, i+1] == 1:
            count_block += 1
            
            
            
    j = line_num
    if count_block == 10:
        for j in range(j, 1, -1):
            for i in range(0, 10):
                background[j, i + 1] = background[j - 1, i + 1]
                background[j, i + 1] = background[j - 1, i + 1]
                
        cls()
        draw_background()
        print_background_value()

background = np.array([
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
])

# block_L = np.array([
#     [0, 0, 0, 0],
#     [0, 1, 0, 0],
#     [0, 1, 1, 1],
#     [0, 0, 0, 0]
# ])


block = np.array(
    [
          [
              [0, 0, 0, 0],
              [0, 1, 0, 0],
              [0, 1, 1, 1],
              [0, 0, 0, 0]
          ],
          [
              [0, 0, 0, 0],
              [0, 1, 1, 0],
              [0, 1, 1, 0], 
              [0, 0, 0, 0]
          ]
    ]
)

reverse_col = np.array([
    [0, 0, 0, -1],
    [0, 0, -1, 0],
    [0, -1, 0, 0],
    [-1, 0, 0, 0],
])

x=3
y=3
count = 0
block_num = 0
text_color = np.array([31, 34, 33, 34, 35, 36, 37, 93])
rotate = 0

      
cls()                                                       
draw_background()
make_block()
print_background_value()

while True:
    if msvcrt.kbhit():
        key = msvcrt.getch()
       
        if key == b'a':
            if teacher_overlap_check(-1, 0) == 0:
                delete_block()
                x -= 1
                make_block()
           
        elif key == b'd':
            if teacher_overlap_check(1, 0) == 0:
                delete_block()
                x += 1
                make_block()
           
        elif key == b's':
            if teacher_overlap_check(0, 1) == 0:
                delete_block()
                y += 1
                make_block()
                    
        elif key == b'r':
            if overlap_check_rotate() == 0:
                delete_block()
                block[block_num] = np.dot(block[block_num].T, reverse_col) * (-1)
                make_block()
               
    if count == 100:
        count = 0
        if teacher_overlap_check(0, 1) == 0:
            delete_block()
            y += 1
            make_block()
        else:
            insert_block()
            print_background_value()
            
            for i in range(1, 21):
                line_check(i);
            
            if(block_num + 1 >= 2):
                block_num = 0
            else:
                block_num += 1
                
            x = 3
            y = 3
       
       
    count += 1
    time.sleep(0.01)