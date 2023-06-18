#include <stdio.h>
#include <stdlib.h>
#include "shortest_path.h"

typedef struct moeda *p_moeda;

struct moeda {
    int valor;
    int peso;
    int qtde;
};

typedef struct adj *p_adj;

struct adj {
    int idx;
    p_adj prox;
};

typedef struct vertice *p_vertice;

struct vertice {
    int valor;
    int peso;
    p_adj adj;
};

typedef struct premiados *p_premiados;

struct premiados {
    int i;
    p_premiados prox;
};

int main(void) {
    int n, Q, i, s, e;
    int N = 0;

    scanf("%d %d", &n, &Q);

    p_moeda moedas;
    moedas = malloc(n * sizeof(struct moeda));

    // Recebe as moedas
    for (i = 0; i < n; i++) {
        int v, p, q;
        scanf("%d %d %d", &v, &p, &q);

        while (v * q > Q) {
            q--;
        }

        moedas[i].valor = v;
        moedas[i].peso = p;
        moedas[i].qtde = q; 

        N += q;
    }

    Grafo *g = novoGrafoVazio();

    adicionaVertice(g);

    s = 0;
    e = 0;
    p_vertice vs;

    vs = malloc((n * N + 2) * sizeof(struct vertice));

    p_premiados premiados = NULL;

    vs[0].valor = 0;
    vs[0].peso = 0;

    for (i = 0; i < n; i++) {
        int sn = e + 1;
        int aux_sn = e;

        p_vertice aux_v;
        aux_v = malloc((Q + 1) * sizeof(struct vertice));

        for (int k = 0; k <= moedas[i].qtde; k++) {
            for (int j = s; j <= e; j++) {
                if (i > 0 && moedas[i].valor + moedas[i - 1].valor >= Q && k > 0) {
                    break;
                }

                if (moedas[i].valor * k + vs[j].valor <= Q) {
                    aux_sn++;
                    adicionaVertice(g);

                    adicionaArco(g, j, aux_sn, moedas[i].peso * k);

                    if (moedas[i].valor * k + vs[j].valor == Q) {
                        p_premiados p;
                        p = malloc(sizeof(struct premiados));

                        p->i = aux_sn;
                        p->prox = premiados;
                        premiados = p;
                    } 

                    vs = (p_vertice) realloc(vs, aux_sn * sizeof(struct vertice));
                    vs[aux_sn].valor = moedas[i].valor * k + vs[j].valor;
                }
            }
        }

        s = sn;
        e = aux_sn;
    }

    e++;
    adicionaVertice(g);
    for (p_premiados prem = premiados; prem != NULL; prem = prem->prox) {
        adicionaArco(g, prem->i, e, 0);
    }

    int *dist = caminhoMinimo(g, 0, N + 2);
    
    if (dist[e] == 2147483647) {
        int min = 0;
        for (int i = 1; i < e; i++) {
            if ((vs[i].valor > vs[min].valor || (vs[i].valor == vs[min].valor && dist[i] < dist[min])) && dist[i] != 2147483647) {
                min = i;
            }
        }

        printf("%d %d\n", vs[min].valor, dist[min]);
    } else {
        printf("%d\n", dist[e]);
    }



    free(dist);
    destroiGrafo(g);

    return 0;
}