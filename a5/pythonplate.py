from sys import stdin

# Defining boilerplate code for Python Submission
def load_num():
    return int(stdin.readline())

# Adjust accordingly for triplets etc.
def load_pair():
    return tuple(map(int, stdin.readline().split()))

# instanceNum is the number of problems.
def load_instance():
    instanceNum = load_num()
    return [load_pair() for b in range(instanceNum)]


# Compiler looks at this first, as in main() in c++.
# This, for Python at least, makes the compiler easy to detect EOF
if __name__ == '__main__':
    n = load_num()

    # While there is problem to solve
    for i in range(n):
        # Print result
        print("Problem number {}".format(c+1))

    # The command print is equivalent to stdout, but
    # DO NOT USE CONCATENATION (e.g. print ("high ") + 5)

# This code is for problems that look like this:

2           # Number of problems to be solved.
3           # Number of vertices for problem index 0 where each vertex is of tuple ([vertexColor], [vertexWeight])
5 2
2 5
6 9
2           # Problem index 1
2 1
7 3
0           # End of problem.
