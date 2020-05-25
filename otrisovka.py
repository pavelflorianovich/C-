from tkinter import Tk, Canvas, BOTH
import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
'''
root = Tk()
root.geometry('1000x700')
canv = Canvas(root, width=800, height=600, bg='white')
canv.pack(fill=BOTH, expand=1)

'''
class Point:
    def __init__(self):
        self.x = 0
        self.y = 0

'''
def reading():
    for i in range(3):
        for j in range(3):
            otrisovka[i][j].x = float(f.readline())
            otrisovka[i][j].y = float(f.readline())


'''


'''
def rendering(): # отрисовка линии
    for i in range(len(otrisovka)):
        for j in range(0, len(otrisovka[i]) - 1):
            canv.create_line(otrisovka[i][j].x, otrisovka[i][j].y, otrisovka[i][j+1].x, otrisovka[i][j+1].y)
        for j in range(len(otrisovka[i])):
            for i in range(len(otrisovka) - 1):
                canv.create_line(otrisovka[i][j].x, otrisovka[i][j].y, otrisovka[i+1][j].x, otrisovka[i+1][j].y)




def modeling():
    canv.delete("all")
    rendering()
    #root.after(20, modeling)
'''
otrisovka = []
for i in range(3):
    otrisovka.append([])
    for j in range(3):
        otrisovka[i].append(Point())

f = open('Data1.txt')
f.read(1)
for i in range(3):
    for j in range(3):
        otrisovka[i][j].x = f.readline(i*3+2*j)
        otrisovka[i][j].y = f.readline(3*i+2*j+1)

for i in range(3):
    for j in range(3):
        print(otrisovka[i][j])
'''        
>>> x = open('test.txt','r')
>>> x.readline()  # прочитать первую строку
This is line1.
>>> x.readline(2)  # прочитать вторую строку
This is line2.
>>> x.readlines()  # прочитать все строки
['This is line1.','This is line2.','This is line3.']'''
'''
#entry_conditions (90, 90, 90, 0, 0, 0)
modeling()
#grafic()
'''
#root.mainloop()
