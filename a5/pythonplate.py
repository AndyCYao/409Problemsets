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

if __name__ == '__main__':
    n = load_num()

    # While there is problem to solve
    for i in range(n):
        # Print result
        print("Problem number {}".format(c+1))

    # The command print is equivalent to stdout, but
    # DO NOT USE CONCATENATION (e.g. print ("high ") + 5)
