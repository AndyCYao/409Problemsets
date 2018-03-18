from sys import stdin
import math


# Defining boilerplate code for Python Submission
def load_num():
    return int(stdin.readline())

# Adjust accordingly for triplets etc.
def load_pair():
    return tuple(map(int, stdin.readline().split()))

# instanceNum is the number of problems.
def load_instance_1(x , y):
    magicNum = load_num()
    for b in range(1, magicNum + 1):
        x[b], y[b] = tuple(map(int, stdin.readline().split()))

    return x,y, magicNum

def load_instance_2(d):
    instanceNum = load_num()
    for i in range(1, instanceNum + 1):
        tmp = load_pair()
        d[tmp[0]][tmp[1]] = d[tmp[1]][tmp[0]] = -1.0

def Distance(d, x, y, magicN):

    # That magic number 751 tho
    for i in range(1, magicN + 1):
        d[i][i] = 0
        for j in range(i+1, magicN + 1):
            d[i][j] = d[j][i] = math.sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))

    return d

def Prim(dist, magicN):
    Free = [0]*(magicN+2)
    d = [0]*(magicN+2)
    Trace = [0] * 751

    for i in range(1, magicN + 1):
        Free[i] = True
        d[i] = 100000

    d[1] = 0

    for j in range(1, magicN + 1):
        u = 0
        min = 100000
        for k in range(1, magicN + 1):
            if (Free[k] and (d[k] < min)):
                u = k
                min = d[k]
        Free[u] = False

        for l in range(1, magicN + 1):
            print (type(Free[l]))
            print (type(d[l]))
            print (type(dist[u][l]))
            if (Free[l] and (d[l] > dist[u][l])):
                d[l] = dist[u][l]
                Trace[l] = u

    return Trace

def Result(Trace, magicN):
    non = True
    for i in range(2,magicN + 1):
        if (dist[i][Trace[u]] >= 0):
            print ("{} {}\n".format(u, Trace[u]))
            non = False
    if (non):
        print ("No new highways need")

# Compiler looks at this first, as in main() in c++.
# This, for Python at least, makes the compiler easy to detect EOF
if __name__ == '__main__':
    n = load_num()

    x = [0]*751
    y = [0]*751
    distMatrix = [[0 for i in range(751)] for j in range(751)]
    # While there is problem to solve
    for i in range(n):
        # Print result
        x,y, magicN = load_instance_1(x, y)
        c = Distance(distMatrix, x, y, magicN)
        dee = load_instance_2(c)
        print (dee[0][0])
        Trace = Prim(dee, magicN)
        Result(Trace, magicN)
