_INF = 9223372036854775807

class Graph:
    def __init__(self, n, s, initial) -> None:
        self.d = []
        self.f = []

        for i in range(n):
            self.d.append(_INF)
            self.f.append(None)

        self.d[s] = initial

    def relax(self, u, v, w):
        if self.d[v] > self.d[u] + w and self.d[u] + w > 0:
            self.d[v] = self.d[u] + w
            self.f[v] = u

    def getDistOf(self, x):
        return self.d[x]
    
    def getFather(self, x):
        return self.f[x]
    

def calc_travel(E, initial_energy, n):
    g = Graph(n, 0, initial_energy)
    for i in range(1, n - 1):
        for e in E:
            g.relax(e[0], e[1], e[2])

        
    return g.getDistOf(n - 1)


def main():
    n = int(input())
    w = list(map(int, input().split()))

    E = []

    m = int(input())
    for _ in range(m):
        u, v = map(int, input().split())
        E.append([u, v, w[v]])

    initial_energy = 100
    left_energy = calc_travel(E, initial_energy, n)

    if (left_energy > m * 100):
        print("impossible")
    else:
        print("possible")

main()