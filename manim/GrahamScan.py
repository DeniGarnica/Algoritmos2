from manim import *
from itertools import cycle
import numpy as np
config.frame_width = 35
config.frame_height = 20

def Lado(dot1, dot2, dot3): #Nos dice si un punto esta del lado izquierdo o derecho de los otros dos, tomando la direccion del punto 1 hacia el 2
  aux = (dot3[1]-dot1[1])*(dot2[0]-dot1[0]) - (dot2[1]-dot1[1])*(dot3[0]-dot1[0])
  if aux>0: #Se encuentra a la izquierda
    return 1
  if aux<0: #Se encuentra a la derecha
    return -1
  return 0 #Son colineales

def GS_up(dots, self):
  n = len(dots)
  hull = [dots[0]]
  d1 = dots[0]
  d2 = dots[1]
  d3 = dots[2]
  line = []
  line.append(Line(dots[0], dots[1]).set_color(GRAY))
  self.play(Create(line[0]))
  line.append(Line(dots[1], dots[2]).set_color(GRAY))
  self.play(Create(line[1]))
  hull.append(d2)
  iter = 1
  for i in range(n-2):
    if Lado(d1, d2, d3) >= 0:

      self.remove(line[iter-1])
      self.remove(line[iter])
      hull.pop()
      d2 = d3
      hull.append(d2)
      iter = iter + 1
      d3 = dots[iter]
      line[iter-1] = Line(d1, d2).set_color(GRAY)
      self.play(Create(line[iter-1]))
      line.append(Line(d2, d3).set_color(GRAY))
      self.play(Create(line[iter]))
      if len(hull)>=3:
        d0 = hull[len(hull)-3]
        while Lado(d0, d1, d2) >= 0 and len(hull)>=3:
          hull.pop()
          hull.pop()
          self.remove(line[iter-1])
          self.remove(line[iter])
          d1 = d0
          hull.append(d2)
          line[iter-1] = Line(d1, d2).set_color(RED)
          self.play(Create(line[iter-1]))
          line[iter] = Line(d2, d3).set_color(RED)
          self.play(Create(line[iter]))
          if len(hull)>=3:
            d0 = hull[len(hull)-3]


    elif Lado(d1, d2, d3) < 0:
      hull.append(d3)
      d1 = d2
      d2 = d3
      iter = iter+1
      d3 = dots[iter]
      line.append(Line(d2, d3).set_color(GRAY))
      self.play(Create(line[iter]))

  if Lado(d1, d2, d3) >= 0:
      hull.pop()
      d2 = d3
      hull.append(d2)
      if len(hull)>=3:
        d0 = hull[len(hull)-3]
        while Lado(d0, d1, d2) >= 0 and len(hull)>=3:
          hull.pop()
          hull.pop()
          d1 = d0
          hull.append(d2)
          if len(hull)>=3:
            d0 = hull[len(hull)-3]

  return hull

def GS_down(dots, hull, self):
  n = len(dots)
  d1 = dots[n-1]
  d2 = dots[n-2]
  d3 = dots[n-3]
  hull2=[d1, d2]
  iter = 3
  while d3 != dots[0]:
    if Lado(d1, d2, d3) >= 0:
      hull2.pop()
      d2 = d3
      hull2.append(d2)
      iter = iter + 1
      d3 = dots[n-iter]
      if len(hull2)>=3:
        d0 = hull2[len(hull2)-3]
        while Lado(d0, d1, d2) >= 0 and len(hull2)>=3:
          hull2.pop()
          hull2.pop()
          d1 = d0
          hull2.append(d2)
          if len(hull2)>=3:
            d0 = hull2[len(hull2)-3]


    elif Lado(d1, d2, d3) < 0:
      hull2.append(d3)
      d1 = d2
      d2 = d3
      iter = iter+1
      d3 = dots[n-iter]


  if Lado(d1, d2, d3) >= 0:
      hull2.pop()
      d2 = d3
      hull2.append(d2)
      if len(hull2)>=3:
        d0 = hull2[len(hull2)-3]
        while Lado(d0, d1, d2) >= 0 and len(hull2)>=3:
          hull2.pop()
          hull2.pop()
          d1 = d0
          hull2.append(d2)
          if len(hull2)>=3:
            d0 = hull2[len(hull2)-3]
  hull2.pop()
  hull2.pop(0)
  for i in range(len(hull2)):
    hull.append(hull2[i])
  return hull

class Sq(Scene):
    def construct(self):
        dots = [[0,0,0],[-2,-3,0],[-5,-5,0],[-2,-4,0],[-1,-1,0],[-1,1,0],[0,-2,0],[1,2,0],[1,-3,0],[1,-5,0],[2,0,0],[2,-2,0],[3,3,0],[3,-1,0],[3,-2,0],[3,-4,0],[3,-5,0],[4,1,0],[4,-3,0],[4,-6,0],[5,-2,0],[5,-5,0]]
        n = len(dots)
        dots.sort(key=lambda x: (x[0], x[1]))
        for i in dots:
            self.add(Dot(i))
        it_dots =iter(dots)
        if len(dots)>=4:
            hull = GS_up(dots, self)
            GS_down(dots, hull, self)
        else:
            hull = dots
        for idx, elem in enumerate(hull):
            thisel = elem
            nextel = hull[(idx + 1) % len(hull)]
            line = Line(Dot(thisel).get_center(), Dot(nextel).get_center()).set_color(WHITE)
            self.play(Create(line))
