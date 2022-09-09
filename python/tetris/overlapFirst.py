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
       
       
def make_block():
    for j in range(0, 4):
        for i in range(0, 4):
            if (block_L[j,i] == 1):
                gotoxy(i+x, j+y)
                print("*")

def delete_block():
    for j in range(0, 4):
        for i in range(0, 4):
            if (block_L[j,i] == 1):
                gotoxy(i+x, j+y)
                print("-")
               
def overlap_check(tmp_x, tmp_y):
    overlap_count = 0
   
    for j in range(4):
        for i in range(4):
            if(block_L[j, i] == 1 and background[j + y + tmp_y, i + x + tmp_x] == 1):
                overlap_count += 1
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

block_L = np.array([
    [0, 0, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 1],
    [0, 0, 0, 0]
])

x=3
y=3
count = 0
                                                             
draw_background()
make_block()
while True:
    if msvcrt.kbhit():
        key = msvcrt.getch()
       
        if key == b'a':
            if(overlap_check(-1, 0) == 0):
                delete_block()
                x -= 1
                make_block()
           
        elif key == b'd':
            if(overlap_check(1, 0) == 0):
                delete_block()
                x += 1
                make_block()
           
        elif key == b's':
            if(overlap_check(0, 1) == 0):
                delete_block()
                y += 1
                make_block()
               
    if count == 100:
        count = 0
       
        if(overlap_check(0, 1) == 0):
            delete_block()
            y += 1
            make_block()
       
       
    count += 1
    time.sleep(0.01)