def max_trail(root, adj, ca):
    T = {
        'E': [],
        'm': 0
    }
    u = root
    v = root
    c = ca
    while len(adj[u]) > 0:
        j = 0
        while j < len(adj[u]) and not (c < 0 or c != adj[u][j][1]):
            if (j < len(adj[u])):
                j += 1
            else:
                return T, u, c
            
        if (j >= len(adj[u])):
            return T, u, c

        v = adj[u][j]
        c = v[1]
        T['E'].append(v)

        aux = adj[u][len(adj[u]) - 1]
        adj[u][len(adj[u]) - 1] = v
        adj[u][j] = aux

        adj[u].pop()

        for i in range(len(adj[v[0]])):
            if (adj[v[0]][i][0] == u):
                aux = adj[v[0]][len(adj[v[0]]) - 1]
                adj[v[0]][len(adj[v[0]]) - 1] = adj[v[0]][i]
                adj[v[0]][i] = aux
        adj[v[0]].pop()

        u = v[0]

        T['m'] += 1

    return T, u, c

def find_vertex(T, adj):
    for i in range(len(T['E'])):
        if (len(adj[T['E'][i][0]]) > 1):
            return i
        
    return None

def euler_trail(adj, m):
    # We are going to define the root of the euler tree being the 
    # first node.
    r = 0
    c = -1
    T, w, c = max_trail(r, adj, c)
    if (r != w):
        return None
    while T['m'] < m:
        s = find_vertex(T, adj)
        if (s == None):
            return s
        
        Tl, w, c = max_trail(T['E'][s][0], adj, T['E'][s][1])
        if (T['E'][s][0] != w):
            return None

        T['E'] = T['E'][0:s + 1] + Tl['E'] + T['E'][s+1:len(T['E'])]

        T['m'] += Tl['m']
    
    return T


def show_euler_trail(T):
    T['E'] = [[0, 0]] + T['E']
    for v in T['E']:
        print(v[0], end=" ")
    print()

def main():
    n, m = map(int, input().split())
    adj = []
    for i in range(n):
        adj.append([])
    for i in range(m):
        u, v, c = map(int, input().split())

        adj[u].append([v, c])
        adj[v].append([u, c])

    T = euler_trail(adj, m)

    if (T == None):
        print("Não possui trilha Euleriana alternante")
        return
    
    show_euler_trail(T)
    
main()