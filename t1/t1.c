#include <stdio.h>
#include <stdlib.h>

typedef struct node *p_node;

struct node {
    int v;
    int d;
};

typedef struct conn *p_conn;

struct conn {
    int d;
    int i;
    int *c;
};


void intercalar(p_node a, int p, int q, int r, int n) {
    p_node b;
    b = malloc(n * sizeof(struct node));

    for (int k = p; k <= q; k++) {
        b[k].v = a[k].v;
        b[k].d = a[k].d;
    }

    for (int s = r, u = q + 1; s > q && u <= r; s--, u++) {
        b[s].v = a[u].v;
        b[s].d = a[u].d;        
    }

    int i = p;
    int j = r;
    for (int x = p; x <= r; x++)
        if (b[i].d >= b[j].d) {
            a[x].v = b[i].v;
            a[x].d = b[i].d;
            i++;
        } else {
            a[x].v = b[j].v;
            a[x].d = b[j].d;
            j--;
        }

    free(b);
}

void ordernar(p_node a, int p, int r, int n) {
    if (p < r) {
        int q = (p + r) / 2;
        ordernar(a, p, q, n);
        ordernar(a, q, r, n);
        intercalar(a, p, q, r, n);
    }
}

void mostrar_nodes(p_conn conns, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < conns[i].d; j++) {
            printf("%d ", conns[i].c[j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    p_node g;
    g = malloc(n * sizeof(struct node));

    p_conn conns;
    conns = malloc(n * sizeof(struct conn));
    for (int i = 0; i < n; i++) {
        scanf(" %d ", &g[i].d);
        g[i].v = i;

        conns[i].d = g[i].d;
        conns[i].i = 0;
        conns[i].c = malloc(conns[i].d * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (g[i].d > 0) {
                if (g[j].d > 0) {
                    conns[g[i].v].c[conns[g[i].v].i] = g[j].v + 1;
                    conns[g[j].v].c[conns[g[j].v].i] = g[i].v + 1;

                    g[i].d--;
                    g[j].d--;
                    conns[g[i].v].i++;
                    conns[g[j].v].i++;
                }
            } else break;
        }

        if (g[i].d > 0) {
            printf("Não é uma sequência gráfica!");
            
            for (int k = 0; k < n; k++) {
                free(conns[k].c);
            }

            free(conns);
            free(g);

            return 0;
        }

        ordernar(g, i + 1, n - 1, n);
    }

    mostrar_nodes(conns, n);


    for (int k = 0; k < n; k++) {
        free(conns[k].c);
    }

    free(conns);
    free(g);

    return 0;
}