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


def rotation(ux, uy, uz):
     for i in range(row):
        for j in range(column):
            global points 
            a = Point()
            b = Point()
            c = Point()
            a.x = points[i][j].x
            a.y = points[i][j].y
            a.z = points[i][j].z
            
            b.x = a.x
            b.y = np.cos(ux) * a.y - np.sin(ux)* a.z
            b.z = np.cos(ux) * a.z + np.sin(ux)* a.y

            c.x = b.x * np.cos(uy) + b.z * np.sin(uy)
            c.y = b.y
            c.z = b.z * np.cos(uy) - b.x * np.sin(uy)
            
            points[i][j].x = c.x * np.cos(uz) - c.y * np.sin(uz)
            points[i][j].y = c.z * np.cos(uz) + c.y * np.sin(uz)
            points[i][j].z = c.z




def reading():
    for i in range(row):
        for j in range(column):
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
            canv.create_line(points[j][i - 1].x, points[j][i - 1].y, points[j][i].x, points[j][i].y)
            canv.create_line(points[i - 1][j].x, points[i - 1][j].y, points[i][j].x, points[i][j].y)


def modeling():
    canv.delete("all")
    reading()
    rotation(1, 0, 0)
    drawing_lines()



f = open('Data.txt', 'r')

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
    time.sleep(0.02)
    

    
f.close()
root.mainloop()
