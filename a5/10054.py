from sys import stdin
from collections import defaultdict, deque

# "Colors are represented by integers from 1 to 50"
MAX_COLORS = 51

def load_num():
    return int(stdin.readline())

# Adjust accordingly for triplets etc.
def load_pair():
    return tuple(map(int, stdin.readline().split()))

# instanceNum is the index number of problems.
def load_instance():
    instanceNum = load_num()
    return [load_pair() for b in range(instanceNum)]

def buildGraph(beads):
    """ Euler’s Theorem. For a connected multi-graph
    G, G is Eulerian if and only if every vertex has even degree. """

    # graphTrix... short for graph Matrix hehehe
    graphTrix = [defaultdict(int) for _ in range(MAX_COLORS)]
    degree = defaultdict(int)
    for b in beads:
        graphTrix[b[0]][b[1]] += 1
        graphTrix[b[1]][b[0]] += 1
        degree[b[0]] +=1
        degree[b[1]] +=1

    # Check degree.  If there exists a vertex with odd degree,
    # life just got easier.  We return None
    for k, v in degree.items():
        if v%2 != 0:
            return None

    # Create necklace using Fleury's algorithm
    def getNextBead(color):
        vColor, vDegree = 0, 0
        for col, deg in graphTrix[color].items():
            if deg > vDegree:
                vColor, vDegree = col, deg

        if vDegree>0:
            graphTrix[color][vColor] -= 1
            graphTrix[vColor][color] -= 1
            return (color, vColor)
        else:
            return None

    nxt = getNextBead(beads[0][1])
    necklace = deque([nxt])

    while True:
        nxt = getNextBead(necklace[-1][1])
        if nxt:
            necklace.append(nxt)
        elif len(beads) != len(necklace):
            prev = necklace.pop()
            necklace.appendleft(prev)
        else:
            break

    return necklace


if __name__ == '__main__':
    # First line is how many cases to solve.
    n = load_num()

    for i in range(n):
        beads = load_instance()
        necklace = buildGraph(beads)

        # Print result
        print("Case #{}".format(i+1))
        if necklace:
            # I do this because I know Python spends most time for printing stuff,
            # So the idea is to use as few print statements as possible.
            freddyKruger = ""
            for b in necklace:
                freddyKruger += "{} {}\n".format(b[0], b[1])
        else:
            freddyKruger = "some beads may be lost\n"

        if i+1 == n:
            print(freddyKruger[:-1])

        else:
            print(freddyKruger)
