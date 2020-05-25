from tkinter import Tk, Canvas, BOTH
import time
import math
import numpy as np


root = Tk()
root.geometry('1000x700')
canv = Canvas(root, width=800, height=600, bg='white')
canv.pack(fill=BOTH, expand=1)


class Point:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.z = 0



def reading():
    for j in range(column):
        for i in range(row):
            points[i][j].x = float(f.readline())
            points[i][j].y = float(f.readline())
            points[i][j].z = float(f.readline())


def drawing_lines():
    for i in range(1, column):
        canv.create_line(points[0][i - 1].x, points[0][i - 1].y, points[0][i].x, points[0][i].y)
    for i in range(1, row):
        canv.create_line(points[i - 1][0].x, points[i - 1][0].y, points[i][0].x, points[i][0].y)
    for i in range(1, row):
        for j in range(1, column):
            canv.create_line(points[i][j - 1].x, points[i][j - 1].y, points[i][j].x, points[i][j].y)
            canv.create_line(points[i - 1][j].x, points[i - 1][j].y, points[i][j].x, points[i][j].y)

def drawing_circles():
    for i in range(row):
        for j in range(column):
            canv.create_oval(points[i][j].x - r, points[i][j].y - r, 
            points[i][j].x + r, points[i][j].y + r, fill = "black")


def modeling():
    canv.delete("all")
    reading()
    drawing_lines()
    drawing_circles()



f = open('Data.txt', 'r')

r = 3 # radius of circles

Time = int(f.readline())  # Time of work
row = int(f.readline())  # Number of rows
column = int(f.readline())  # Number of columns
Number = row * column  # Number of points

points = []
for i in range(row):
    points.append([])
    for j in range(column):
        points[i].append(Point())

for i in range(Time):
    modeling()
    canv.update()
    time.sleep(0.01)
    

    
f.close()
root.mainloop()
