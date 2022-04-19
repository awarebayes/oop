from dataclasses import dataclass
import sys
import numpy as np

SCREEN_HEIGHT = 700
SCREEN_WIDTH = 700
SCALE_ADDITIONAL = 0.6

@dataclass(unsafe_hash=True)
class Line:
    x: int
    y: int

    def __init__(self, x, y):
        if y > x:
            x, y = y, x
        super(Line, self).__init__()
        self.x = x
        self.y = y

def find_center(vertices):
    vertices = np.array(vertices)
    median = (vertices.min(axis=0) + vertices.max(axis=0)) / 2
    vertices = vertices - median
    print("Shifing by", -median)
    return vertices

def scale(vertices):
    vertices = np.array(vertices)
    diff = np.abs(vertices.max(axis=1) - vertices.min(axis=1))
    max_coord_diff = np.max(diff)

    screen_dim = np.min([SCREEN_WIDTH, SCREEN_HEIGHT])
    required_scale = screen_dim / max_coord_diff
    required_scale *= SCALE_ADDITIONAL

    print("Scaling with", required_scale)

    vertices *= required_scale
    return vertices

def parse(path):
    file = open(path, "r")
    vertices = []
    lines = set()

    for line in file:
        splitted = line.split()
        if not splitted:
            continue

        line_type = splitted[0]

        if line_type == "f":
            faces = []
            vertices_groups = splitted[1:]
            for g in vertices_groups:
                faces.append(g.split("/")[0])
            faces = faces[:3]
            faces = list(map(int, faces))
            lines.add(Line(faces[0], faces[1]))
            lines.add(Line(faces[0], faces[2]))
            lines.add(Line(faces[1], faces[2]))

        if line_type == "v":
            vertex = list(map(float, splitted[1:]))
            vertices.append(vertex)
    file.close()
    return vertices, lines


def save(path, vertices, lines):
    file = open(path, "w")

    file.write(f"i {len(vertices)} {len(lines)}\n")

    for v in vertices:
        file.write(f"v {v[0]} {v[1]} {v[2]}\n")

    for l in lines:
        file.write(f"l {l.x-1} {l.y-1}\n")

    file.write("e\n")
    file.close()


if __name__ == '__main__':
    in_path, out_path = sys.argv[1:]
    vertices, lines = parse(in_path)

    vertices = find_center(vertices)
    vertices = scale(vertices)

    save(out_path, vertices, lines)
