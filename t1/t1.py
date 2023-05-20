# def intercala(g, p, q, r, n):
#     B = []

#     for i in range(n):
#         B.append([])

#     for i in range(p, q + 1):
#         B[i] = g[i]
#     for j in range(q + 1, r + 1):
#         B[r + q + 1 - j] = g[j]

#     i = p
#     j = r

#     for k in range(p, r + 1): 
#         if (B[i][1] >= B[j][1]):
#             g[k] = B[i]
#             i += 1
#         else: 
#             g[k] = B[j]
#             j -= 1

# def sort_desc(g, p, r, n):
#     if (p < r):
#         q = (p + r) // 2
#         sort_desc(g, p, q, n)
#         sort_desc(g, q + 1, r, n)
#         intercala(g, p, q, r, n)

# def second(v):
#     return v[1]

def showRow(row):
    for i in row:
        print(i, end=" ")
    print()


def show(C):
    for row in C:
        showRow(row)

def main():
    n = int(input())
    d = list(map(int, input().split()))

    C = []
    g = []
    for i in range(n):
        g.append([i, d[i]])
        C.append([])

    i = 0
    while g[i][1] > 0:
        i = 0
        for j in range(i + 1, n):
            if (g[i][1] > 0):
                if (g[j][1] > 0):
                    C[g[i][0]].append(g[j][0] + 1)
                    C[g[j][0]].append(g[i][0] + 1)

                    g[j][1] -= 1
                    g[i][1] -= 1
            else:
                break
    
        if (g[i][1] > 0):
            print("Não é sequência gráfica!")
            return
        
        g.sort(key=lambda x : x[1], reverse=True)

    show(C)

main()
