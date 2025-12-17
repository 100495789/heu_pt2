from constraint import *
import os
import sys

def read_input_file(file_path):
    # opening file from the path and reading it by lines
    with open(file_path, 'r') as file:
        lines = file.readlines()
    return [line.strip() for line in lines]

def read_data():
    # getting file data from a specified path file
    if len(sys.argv) != 3:
        print("Número incorrecto de argumentos de entrada!")
        sys.exit(1)

    file_path = sys.argv[1]

    if not os.path.isfile(file_path):
        print(f"No se encontró el archivo '{file_path}'.")
        sys.exit(1)

    data = read_input_file(file_path)

    n_rows = len(data)

    if n_rows % 2 != 0:
        print("La rejilla debe tener un número par de filas!")
        sys.exit(1)

    for line in data:
        n_cols = len(line)
        if n_cols != n_rows:
            print("La rejilla debe ser cuadrada!")
            sys.exit(1)
    return data

def parse_data(data):
    grid = []
    for line in data:
        row = []
        for l in line:
            if l == '.':
                row.append(-1)
            elif l == 'O':
                row.append(0)
            elif l == 'X':
                row.append(1)
            else:
                print("La fila tiene un elemento distinto de ., X u O")
                return sys.exit(1)
        # append changed row to the final grid
        grid.append(row)
    return grid

def check_color_equality(*args):
    # the amount of black and white figurines should be the same
    return sum(args) == len(args) // 2

def check_three_consecutive(pos1, pos2, pos3):
    # no more than two consecutive elements of the same color
    return not (pos1 == pos2 == pos3)

def main():
    problem = Problem()

    data = read_data()
    grid = parse_data(data)
    n = len(grid)

    for i in range(n):
        for j in range(n):
            if grid[i][j] == -1:
                problem.addVariable((i,j), [0,1])
            else:
                problem.addVariable((i,j), [grid[i][j]])

    # add constraint for the same amount of black and whites in rows
    for i in range(n):
            problem.addConstraint(check_color_equality, [(i, j) for j in range(n)])

    # add constraint for the same amount of black and whites in columns
    for j in range(n):
        problem.addConstraint(check_color_equality, [(i, j) for i in range(n)])

    # add constraint for the three consecutive colors in rows
    for i in range(n):
        for j in range(n - 2):
            problem.addConstraint(check_three_consecutive, [(i, j), (i, j+1), (i, j+2)])

    # add constraint for the three consecutive colors in columns
    for j in range(n):
        for i in range(n - 2):
            problem.addConstraint(check_three_consecutive, [(i, j), (i+1, j), (i+2, j)])

    print("+" + "---+" * n)
    for i in range(n):
        for j in range(n):
            value = grid[i][j]
            if value == 0:
                grid_element = 'O'
            elif value == 1:
                grid_element = 'X'
            else:
                grid_element = ' '
            print(f"| {grid_element} ", end='')
        print("| ")
    print("+" + "---+" * n)

    # retrieve solutions
    solutions = problem.getSolutions()
    print(f"{len(solutions)} soluciones encontradas")

    # writing to the file initial/resulting grid
    output = sys.argv[2]
    with open(output, 'w') as file:
        # initial grid
        file.write("+" + "---+" * n + '\n')
        for i in range(n):
            for j in range(n):
                value = grid[i][j]
                if value == 0:
                    grid_element = 'O'
                elif value == 1:
                    grid_element = 'X'
                else:
                    grid_element = ' '
                file.write(f"| {grid_element} ")
            file.write("|\n")
        file.write("+" + "---+" * n + '\n')

        # resulting grid if solution was found
        if solutions:
            solution = solutions[0]
            file.write("+" + "---+" * n + "\n")
            for i in range(n):
                for j in range(n):
                    value = solution[(i, j)]
                    if value == 0:
                        grid_element = 'O'
                    else:
                        grid_element = 'X'
                    file.write(f"| {grid_element} ")
                file.write("|\n")
            file.write("+" + "---+" * n)
        else:
            file.write("No se encontraron soluciones.")

if __name__ == "__main__":
    main()