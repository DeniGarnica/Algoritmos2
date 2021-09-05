from manim import *
from itertools import cycle
config.frame_width = 35
config.frame_height = 20

def dist_linea(dot1, dot2, dot3):
  return abs((dot3[1]-dot1[1])*(dot2[0]-dot1[0]) - (dot2[1]-dot1[1])*(dot3[0]-dot1[0]))

def Lado(dot1, dot2, dot3):
  aux = (dot3[1]-dot1[1])*(dot2[0]-dot1[0]) - (dot2[1]-dot1[1])*(dot3[0]-dot1[0])
  if aux>0:
    return 1
  if aux<0:
    return -1
  return 0

def puntomaslejano(dot1, dot2, dots, lado):
  dist_max = dist_linea(dot1, dot2, dot1)
  iter = 2
  max_iter=-1
  for i in range(len(dots)-3):
    if Lado(dot1, dot2, dots[iter]) ==lado and dist_linea(dot1, dot2, dots[iter])>dist_max:
      dist_max=dist_linea(dot1, dot2, dots[iter])
      max_iter=iter
    iter=iter+1
  return max_iter

def qh(dots, dot1, dot2, lado, hull):
  nuevo = puntomaslejano(dot1, dot2, dots, lado)
  if nuevo == -1:
    return
  hull.append(dots[nuevo])
  qh(dots, dots[nuevo], dot1, -Lado(dot1, dot2, dots[nuevo]), hull)
  qh(dots, dots[nuevo], dot2, -Lado(dot2, dot1, dots[nuevo]), hull)

def Quickhull(dots):
  dots.sort()
  n= len(dots)
  hull = [dots[0], dots[n-1]] #agregamos los puntos en los extremos
  qh(dots, dots[0], dots[n-1], 1, hull)
  qh(dots, dots[0], dots[n-1], -1, hull)
  hull.sort()
  return hull

class Sq(Scene):
    def construct(self):
        dots = [[0,0,0],[-2,-3,0],[-5,-5,0],[-2,-4,0],[-1,-1,0],[-1,1,0],[0,-2,0],[1,2,0],[1,-3,0],[1,-5,0],[2,0,0],[2,-2,0],[3,3,0],[3,-1,0],[3,-2,0],[3,-4,0],[3,-5,0],[4,1,0],[4,-3,0],[4,-6,0],[5,-2,0],[5,-5,0]]
        n = len(dots)
        for i in dots:
            self.add(Dot(i))
        it_dots =iter(dots)
        hull = Quickhull(dots)
        print(hull)
        for idx, elem in enumerate(hull):
            thisel = elem
            nextel = hull[(idx + 1) % len(hull)]
            line = Line(Dot(thisel).get_center(), Dot(nextel).get_center()).set_color(WHITE)
            self.play(Create(line))
