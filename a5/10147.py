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

# Compiler looks at this first, as in main() in c++.
# This, for Python at least, makes the compiler easy to detect EOF
if __name__ == '__main__':
    ney = load_num()
    # While there is problem to solve
    for r in range(ney):
        n = load_num()
        Free = [0]*(n+2)
        d = [0]*(n+2)
        x = [0]*755
        y = [0]*755
        distMatrix = [[0 for i in range(755)] for j in range(755)]
        Trace = [0]*755

        inf = 1000000
        
        for i in range(1, n+1):
            x[i], y[i] = load_pair()

        for i in range(1, n+1):
            distMatrix[i][i] = 0
            for j in range(i+1,n+1):
                distMatrix[i][j] = distMatrix[j][i] = math.sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))

        m = load_num()

        for i in range(1,m+1):
            u, v = load_pair()
            distMatrix[u][v] = distMatrix[v][u] = -1

        for i in range(1, n+1):
            Free[i] = True
            d[i] = inf

        d[1] = 0

        for i in range(1,n+1):
            u = 0
            minD = inf

            for j in range(1, n+1):
                if (Free[j] and (d[j] < minD)):
                    u = j
                    minD = d[j]

            for j in range(1,n+1):
                if (Free[j] and (d[j] > distMatrix[u][j])):
                    d[j] = distMatrix[u][j]
                    Trace[j] = u

        non = True

        for v in range(2, n+1):
            if (distMatrix[v][Trace[v]] >= 0):
                print ("{} {}".format(v, Trace[v]))
                non = False

        if (non):
            print ("No new highways need")

        

        





