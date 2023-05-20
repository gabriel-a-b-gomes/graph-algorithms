def DFS_visit(u, c, ftr, adj, ts):
    c[u] = 1
    for x in adj[u]:
        if c[x[0]] == 0:
            ftr[x[0]] = u
            ts = DFS_visit(x[0], c, ftr, adj, ts)
    ts = [u] + ts

    return ts

def topological_sort(adj, n):
    ts = []
    ftr = []
    c = []
    for _ in range(n):
        c.append(0)
        ftr.append(None)
    for i in range(n):
        if c[i] == 0:
            ts = DFS_visit(i, c, ftr, adj, ts)

    return ts 

def solve(adj, s, t, n):
    cam = []

    for _ in range(n):
        cam.append([0, 0, 0])
    
    cam[t] = [1, 0, 0]

    v = topological_sort(adj, n)

    for i in range(n - 1, -1, -1):
        for u in adj[v[i]]:
            if u[1] == 0:
                cam[v[i]][0] += cam[u[0]][0] + cam[u[0]][1] + cam[u[0]][2]
            elif u[1] == 1: 
                cam[v[i]][1] += cam[u[0]][0] + cam[u[0]][1]
            else: 
                cam[v[i]][2] += cam[u[0]][0]

    return cam[s][0] + cam[s][1] + cam[s][2]

def main():
    n, m, s, t = map(int, input().split())

    adj = []
    for _ in range(n):
        adj.append([])

    for _ in range(m):
        u, v, c = map(int, input().split())
        adj[u].append([v, c])

    ans = solve(adj, s, t, n)

    print(ans)

main()