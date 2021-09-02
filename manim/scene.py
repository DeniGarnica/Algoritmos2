from manim import *
from itertools import cycle
config.frame_width = 35
config.frame_height = 20

class Sq(Scene):
    def construct(self):
        dots = [[0,0,0],[-2,-3,0],[-5,-5,0],[-2,-4,0],[-1,-1,0],[-1,1,0],[0,-2,0],[1,2,0],[1,-3,0],[1,-5,0],[2,0,0],[2,-2,0],[3,3,0],[3,-1,0],[3,-2,0],[3,-4,0],[3,-5,0],[4,1,0],[4,-3,0],[4,-6,0],[5,-2,0],[5,-5,0]]
        for i in dots:
            self.add(Dot(i))
        it_dots =iter(dots)
        for idx, elem in enumerate(dots):
            thisel = elem
            nextel = dots[(idx + 1) % len(dots)]
            line = Line(Dot(thisel).get_center(), Dot(nextel).get_center()).set_color(WHITE)
            self.play(Create(line))
