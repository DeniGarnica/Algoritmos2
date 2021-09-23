from manim import *
from itertools import cycle
import numpy as np
import random

class  Vectors(VectorScene):
    def construct(self):
        plane =self.add_plane(animate=True).add_coordinates()
        vector = self.add_vector([-3,-2],color = YELLOW)

        basis = self.get_basis_vectors()
        self.add(bvasis)
        self.vector_to_coords(vector = vector)
        vector2 = self.add_vector([2,2])
        self.write_vevtor_coordinates(vector = vector2)

class Matrix(LinearTransformationScene):
    def __init__(self):
                LinearTransformationScene.__init__(
                self,
                show_coordinates = True,
                leave_ghost_vectors = True,
                show_basis_vectors = True
                )
    def construct(self):

        matrix = [[1,2],[2,1]]
        matrix_tex = MathTex("A=\\begin{bmatrix} 1& 2 \\\\2&1\\end{bmatrix}").to_edge(UL).add_backgrouund_rectangle()
        unit_square = self.get_unit_square()
        text = always_redraw(lambda : Tex("Det(A)").set(width=0.7).move_to(unit_square.get_center()))
        vect = self.get_vector([1,-2],color = PURPLE_B)

        rect1 = Rectangle(height = 2, width = 1, stroke_color = BLUE_A,
         fill_color = BLUE_D, fill_opacity = 0.6).shift(UP*2+LEFT*2)

        circ1 = Circle(radius = 1, stroke_color = BLUE_A,
         fill_color = BLUE_D, fill_opacity = 0.6).shift(DOWN*2+RIGHT*1)

        self.add_transformable_mobject(vect, unit_squre, rect1, circ1)
        #self.add_background_mobject(matrix_tex, text)
        self.apply_matrix(matrix)

        self.wait()
