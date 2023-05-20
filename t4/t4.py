class NodeSet:
    def __init__(self, N):
        self.f = []
        self.rank = []
        self.clusters = N

        for i in range(N):
            self.f.append(i)
            self.rank.append(0)

    def find_set(self, x):
        if (x == self.f[x]):
            return x
        return self.find_set(self.f[x])
    
    def link(self, x, y):
        if (self.rank[x] > self.rank[y]):
            self.f[y] = x
        else:
            self.f[x] = y
            if (self.rank[x] == self.rank[y]):
                self.rank[y] += 1

    def union(self, e):
        self.link(self.find_set(e[0]), self.find_set(e[1]))
        self.clusters -= 1

    def get_clusters(self):
        return self.clusters

def calc_network_cost(E, N, K):
    cost = 0
    
    sets = NodeSet(N)
        
    E.sort(key= lambda x : x[2])

    for j in range(len(E)):
        conn = E[j]
        if (sets.get_clusters() == K):
            break

        if (sets.find_set(conn[0]) != sets.find_set(conn[1])):
            cost += conn[2]
            sets.union(conn)

    return cost

def main():
    N, M, K = map(int, input().split())

    E = []

    for _ in range(M):
        u, v, w = map(int, input().split())
        E.append([u, v, w])

    network_cost = calc_network_cost(E, N, K)

    print(network_cost)

main()