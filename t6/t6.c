#include <stdio.h>
#include <stdlib.h>
#include "shortest_path.h"

#define _INF 2147483647

typedef struct moeda *p_moeda;

struct moeda {
    int valor;
    int peso;
    int qtde;
};

typedef struct adj *p_adj;

struct adj {
    int idx;
    int peso;
    p_adj prox;
};

typedef struct vertice *p_vertice;

struct vertice {
    int valor;
    p_adj adj;
};

typedef struct premiados *p_premiados;

struct premiados {
    int i;
    p_premiados prox;
};

void recebe_moeda(p_moeda moedas, int i, int Q) {
    int v, p, q;
    scanf("%d %d %d", &v, &p, &q);

    while (v * q > Q) {
        q--;
    }

    moedas[i].valor = v;
    moedas[i].peso = p;
    moedas[i].qtde = q; 
}

void initializa_vertices(p_vertice v, int n) {
    for (int j = 0; j <= n; j++) {
        v[j].valor = 0;
        v[j].adj = NULL;
    }
}

int atualiza_grafo(Grafo *g, p_vertice v, p_vertice aux, p_premiados *premiados, int an, int Q) {
    for (int j = 0; j <= Q; j++) {
        if (aux[j].valor == j) {
            an++;
            adicionaVertice(g);

            for (p_adj adj = aux[j].adj; adj != NULL; adj = adj->prox) {
                adicionaArco(g, adj->idx, an, adj->peso);
            }

            if (aux[j].valor == Q) {
                p_premiados p;
                p = malloc(sizeof(struct premiados));

                p->i = an;
                p->prox = *(premiados);
                *(premiados) = p;
            } 

            v[an].valor = aux[j].valor;
        }
    }

    return an;
}

void calcular_arcos(p_moeda moedas, p_vertice vs, p_vertice aux_v, int s, int e, int i, int Q) {
    for (int k = 0; k <= moedas[i].qtde; k++) {
        for (int j = s; j <= e; j++) {
            if (moedas[i].valor * k + vs[j].valor <= Q) {
                int u = moedas[i].valor * k + vs[j].valor;
                aux_v[u].valor = u;

                p_adj adj = malloc(sizeof(struct adj));
                adj->prox = aux_v[u].adj;
                adj->idx = j;
                adj->peso = moedas[i].peso * k;

                aux_v[u].adj = adj;
            }
        }
    }
}

int adiciona_arcos_premiados(Grafo *g, p_premiados premiados, int e) {
    e++;
    adicionaVertice(g);
    for (p_premiados prem = premiados; prem != NULL; prem = prem->prox) {
        adicionaArco(g, prem->i, e, 0);
    }

    return e;
}


int main(void) {
    int n, Q, i, s, e;

    scanf("%d %d", &n, &Q);

    Grafo *g = novoGrafoVazio();

    adicionaVertice(g);

    s = 0;
    e = 0;

    p_vertice vs;

    vs = malloc((n * (Q + 1) + 2) * sizeof(struct vertice));

    p_premiados premiados = NULL;

    vs[0].valor = 0;

    p_moeda moedas;
    moedas = malloc(n * sizeof(struct moeda));

    for (i = 0; i < n; i++) {
        recebe_moeda(moedas, i, Q);

        int sn = e + 1;
        int aux_sn = e;

        p_vertice aux_v;
        aux_v = malloc((Q + 1) * sizeof(struct vertice));

        initializa_vertices(aux_v, Q);

        calcular_arcos(moedas, vs, aux_v, s, e, i, Q);
        aux_sn = atualiza_grafo(g, vs, aux_v, &premiados, aux_sn, Q);

        s = sn;
        e = aux_sn;
    }

    e = adiciona_arcos_premiados(g, premiados, e);

    int *dist = caminhoMinimo(g, 0, e);
    
    if (dist[e] == _INF) {
        int min = 0;
        for (int i = 1; i < e; i++) {
            if ((vs[i].valor > vs[min].valor || (vs[i].valor == vs[min].valor && dist[i] < dist[min])) && dist[i] != _INF) {
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