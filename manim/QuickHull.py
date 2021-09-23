from manim import *
from itertools import cycle
import numpy as np
config.frame_width = 35
config.frame_height = 20

def swapPositions(list, pos1, pos2):
    list[pos1], list[pos2] = list[pos2], list[pos1]
    return list

def distancia(dot1, dot2):
    return np.sqrt((dot1[0]-dot2[0])**2+(dot1[1]-dot2[1])**2) #Distancia entre dos puntos

def dist_linea(dot1, dot2, dot3): #distancia de la recta formada por los primeros dos puntos y el tercer punto
  return abs((dot3[1]-dot1[1])*(dot2[0]-dot1[0]) - (dot2[1]-dot1[1])*(dot3[0]-dot1[0]))

def Lado(dot1, dot2, dot3): #Nos dice si un punto esta del lado izquierdo o derecho de los otros dos, tomando la direccion del punto 1 hacia el 2
  aux = (dot3[1]-dot1[1])*(dot2[0]-dot1[0]) - (dot2[1]-dot1[1])*(dot3[0]-dot1[0])
  if aux>0: #Se encuentra a la izquierda
    return 1
  if aux<0: #Se encuentra a la derecha
    return -1
  return 0 #Son colineales

def puntomaslejano(dot1, dot2, dots, lado, self): #Nos dice quien es el punto mas lejano de una recta
  dist_max = dist_linea(dot1, dot2, dot1)
  iter = 2
  max_iter=-1
  for i in range(len(dots)-3):
    if Lado(dot1, dot2, dots[iter]) ==lado and dist_linea(dot1, dot2, dots[iter])>dist_max:
      dist_max=dist_linea(dot1, dot2, dots[iter])
      max_iter=iter
    iter=iter+1
  return max_iter

def qh(dots, dot1, dot2, lado, hull, self):
  nuevo = puntomaslejano(dot1, dot2, dots, lado, self)
  if nuevo == -1:
    return
  line = Line(dot1, dot2).set_color(GRAY)
  self.play(Create(line))
  d = Dot(dots[nuevo]).set_color(RED)
  self.add(d)
  line2 = Line(dot1, dots[nuevo]).set_color(GRAY)
  self.play(Create(line2))
  line3 = Line(dot2, dots[nuevo]).set_color(GRAY)
  self.play(Create(line3))
  hull.append(dots[nuevo])

  qh(dots, dots[nuevo], dot1, -Lado(dot1, dot2, dots[nuevo]), hull, self)
  qh(dots, dots[nuevo], dot2, -Lado(dot2, dot1, dots[nuevo]), hull, self)

def Quickhull(dots, self):
  dots.sort()
  n= len(dots)
  hull = [dots[0], dots[n-1]] #agregamos los puntos en los extremos
  self.wait(1)
  d = Dot(dots[0]).set_color(RED)
  self.add(d)
  self.wait(1)
  d2 = Dot(dots[n-1]).set_color(RED)
  self.add(d2)
  qh(dots, dots[0], dots[n-1], 1, hull, self)
  qh(dots, dots[0], dots[n-1], -1, hull, self)
  hull.sort()

  return hull

class Sq(Scene):
    def construct(self):
        dots = [[0,0,0],[-2,-3,0],[-5,-5,0],[-2,-4,0],[-1,-1,0],[-1,1,0],[0,-2,0],[1,2,0],[1,-3,0],[1,-5,0],[2,0,0],[2,-2,0],[3,3,0],[3,-1,0],[3,-2,0],[3,-4,0],[3,-5,0],[4,1,0],[4,-3,0],[4,-6,0],[5,-2,0],[5,-5,0]]
        n = len(dots)
        for i in dots:
            self.add(Dot(i))
        it_dots =iter(dots)
        if len(dots)>=4:
            hull = Quickhull(dots, self)
            hull.sort(key=lambda x: (-np.arctan2(x[1], x[0])))
            hull.insert(0,hull[len(hull)-1])
            hull.pop()
        else:
            hull = dots
        print(hull)
        for idx, elem in enumerate(hull):
            thisel = elem
            nextel = hull[(idx + 1) % len(hull)]
            line = Line(Dot(thisel).get_center(), Dot(nextel).get_center()).set_color(WHITE)
            self.play(Create(line))
