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

int main(void) {
    int n, Q, i;
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

        N += q + 1; // as q + valor 0

        
    }

    Grafo *g = novoGrafo(N + 2); // adiciona o primeiro e último vertice

    p_vertice vs;
    vs = malloc((N + 2) * sizeof(struct vertice));

    int k = 0;

    vs[0].valor = 0;
    vs[0].peso = 0;
    vs[0].adj = NULL;

    vs[N + 1].valor = 0;
    vs[N + 1].peso = 0;
    vs[N + 1].adj = NULL;

    int ii = 0, fi = 0;
    for (i = 0; i < n; i++) {
        int qi = moedas[i].qtde;

        int ki = k + 1;
        int kf = 0;
        while (qi >= 0) {
            k++;
            vs[k].valor = moedas[i].valor * qi;
            vs[k].peso = moedas[i].peso * qi;
            vs[k].adj = NULL;
            qi--;
        }

        kf = k;

        for (int j = ii; j <= fi; j++) {
            for (int u = ki; u <= kf; u++) {
                if (!(vs[u].valor == 0 && vs[j].adj != NULL))
                    if (vs[j].valor + vs[u].valor <= Q) {
                        adicionaArco(g, j, u, vs[u].peso);

                        p_adj aux;
                        aux = malloc(sizeof(struct adj));

                        aux->idx = u;
                        aux->prox = vs[j].adj;
                        vs[j].adj = aux;
                    }
            }
        }

        ii = ki;
        fi = kf;
    }

    for (int u = ii; u <= fi; u++) {
        if (vs[N + 1].valor + vs[u].valor <= Q) {
            adicionaArco(g, u, N + 1, vs[N + 1].peso);

            p_adj aux;
            aux = malloc(sizeof(struct adj));

            aux->idx = N + 1;
            aux->prox = vs[u].adj;
            vs[u].adj = aux;
        }
    }

    printf("Grafo gerado:\n");
    printGrafo(g);

    int *dist = caminhoMinimo(g, 0, N + 2);
    
    for (int i = 0; i <= N + 2; i++)
        printf("Distância mínima entre 0 e %d: %d\n", i, dist[i]);

    free(dist);
    destroiGrafo(g);

    return 0;
}