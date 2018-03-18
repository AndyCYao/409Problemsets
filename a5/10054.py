# Defining boilerplate code for Python Submission
def load_num():
    return int(stdin.readline())

# Adjust accordingly for triplets etc.
def load_pair():
    return tuple(map(int, stdin.readline().split()))

def load_instance():
    instanceNum = load_num()
    return [load_pair() for b in range(instanceNum)]

if __name__ == '__main__':
