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
       
       
def make_block(color):
    for j in range(0, 4):
        for i in range(0, 4):
            if (block_L[rotate,j,i] == 1):
                gotoxy(i+x, j+y)
                print("\033[%dm" % color + "*" + '\033[0m')

def delete_block():
    for j in range(0, 4):
        for i in range(0, 4):
            if (block_L[rotate, j,i] == 1):
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
        overlap_block = tmp_back & block_L[rotate]
        overlap_count = overlap_block.sum()
    return overlap_count

def overlap_check_rotate():
    overlap_count = 1
    tmp_rotate = rotate
    tmp_rotate += 1
    if tmp_rotate == 4:
        tmp_rotate = 0
    
    if (x >= 0) and (x <= 8) and (y <= 18): 
        tmp_back = background[0 + y: 4 + y, 0 + x:4 + x]
        overlap_block = (tmp_back & block_L[tmp_rotate])
        overlap_count = overlap_block.sum()
        
    return overlap_count



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

block_L = np.array([
    
    [
    [0, 0, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 1],
    [0, 0, 0, 0]
    ],
    
    [
    [0, 0, 0, 0],
    [0, 1, 1, 0],
    [0, 1, 0, 0],
    [0, 1, 0, 0]
    ],
    
    [
    [0, 0, 0, 0],
    [1, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 0]
    ],
    
    [
    [0, 0, 1, 0],
    [0, 0, 1, 0],
    [0, 1, 1, 0],
    [0, 0, 0, 0]
    ]
    
])

x=3
y=3
count = 0
text_color = np.array([30, 31, 32, 33, 34, 35, 36, 37])
rotate = 0
      
cls()                                                       
draw_background()
make_block(text_color[1])
while True:
    if msvcrt.kbhit():
        key = msvcrt.getch()
       
        if key == b'a':
            if teacher_overlap_check(-1, 0) == 0:
                delete_block()
                x -= 1
                make_block(text_color[1])
           
        elif key == b'd':
            if teacher_overlap_check(1, 0) == 0:
                delete_block()
                x += 1
                make_block(text_color[1])
           
        elif key == b's':
            if teacher_overlap_check(0, 1) == 0:
                delete_block()
                y += 1
                make_block(text_color[1])
                    
        elif key == b'r':
            if overlap_check_rotate() == 0:
                delete_block()
                rotate += 1
                if rotate == 4:
                    rotate = 0
                make_block(text_color[1])
               
    if count == 100:
        count = 0
        if teacher_overlap_check(0, 1) == 0:
            delete_block()
            y += 1
            make_block(text_color[1])
       
       
    count += 1
    time.sleep(0.01)