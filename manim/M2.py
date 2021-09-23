from manim import *
import numpy as np
import math
config.frame_width = 20
config.frame_height = 20

class LinearTransformationSceneExample(LinearTransformationScene):
    def __init__(self):
        LinearTransformationScene.__init__(
            self,
            show_coordinates=False,
            leave_ghost_vectors=False,
            show_basis_vectors = False
        )
    def construct(self):
        object = [[-2, 0, 0], [0, 2, 0], [2, 0, 0], [2, -2, 0], [-2, -2, 0],]
        ob= Polygon(*object, stroke_color = PURPLE_D ,fill_color = PURPLE_D, fill_opacity = 0.7)
        matrix = [[1, 0], [0, 0.5]]
        matrix2 = [[0, -1], [1, 0]]
        tex1 = MathTex(
                        "\\begin{bmatrix} 1 & 0 & 0 & 0\\\\ 0 & \\frac{1}{2} & 0 & 0\\\\ 0 & 0 & 1 & 0\\\\ 0 & 0 & 0 & 1\\end{bmatrix}")
        tex1.scale(1)
        tex1.move_to(LEFT*6, UP*20)
        tex3 = MathTex(
                        "\\begin{bmatrix} \\cos(90^{\\circ}) & -\\sin(90^{\\circ}) & 0 & 0\\\\\\sin(90^{\circ}) & \\cos(90^{\circ}) & 0 & 0\\\\ 0 & 0 & 1 & 0\\\\ 0 & 0 & 0 & 1\\end{bmatrix}")
        tex3.scale(1)
        tex3.move_to(LEFT*6, UP*20)
        tex2 = MathTex(
                        "\\begin{bmatrix} 1 & 0 & 0 & 0 \\\\0 & 1 & 0 & -1\\\\ 0 & 0 & 1 & 0\\\\ 0 & 0 & 0 & 1\\end{bmatrix}")
        tex2.scale(1)
        tex2.move_to(LEFT*6, UP*20)
        tex4 = MathTex(
                        "\\begin{bmatrix} 1 & 0 & 0 & 0 \\\\0 & 1 & 0 & 2\\\\ 0 & 0 & 1 & 0\\\\ 0 & 0 & 0 & 1\\end{bmatrix}")
        tex4.scale(1)
        tex4.move_to(LEFT*6, UP*20)
        self.add_transformable_mobject(ob)
        self.play(Write(tex1))
        self.play(ApplyMatrix(matrix, ob))
        self.play(FadeOut(tex1))
        self.play(Write(tex2))
        self.play(ob.animate.shift(DOWN*1))
        self.play(FadeOut(tex2))
        self.play(Write(tex3))
        self.play(ApplyMatrix(matrix2, ob))
        self.play(FadeOut(tex3))
        self.play(Write(tex4))
        self.play(ob.animate.shift(UP*2))
        self.play(FadeOut(tex4))
        self.wait()
