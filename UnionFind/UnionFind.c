#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct UniaoBusca {
    int n;
    int *v;
    char **nomes;  // Armazena os nomes dos líderes
} UniaoBusca;

UniaoBusca* ub_cria(int n) {
    UniaoBusca* ub = (UniaoBusca*) malloc(sizeof(UniaoBusca));
    ub->v = (int*) malloc(n * sizeof(int));
    ub->nomes = (char**) malloc(n * sizeof(char*)); // Aloca espaço para os nomes
    ub->n = n;
    
    if (ub->v != NULL && ub->nomes != NULL) {
        for (int i = 0; i < ub->n; i++) {
            ub->v[i] = -1; // Cada território é inicialmente seu próprio líder
            ub->nomes[i] = (char*) malloc(20 * sizeof(char)); // Aloca espaço para o nome
            sprintf(ub->nomes[i], "Lider_%d", i + 1); // Inicializa o nome dos líderes como "Lider_1", "Lider_2", etc.
        }
    }
    return ub;
}

void ub_libera(UniaoBusca* ub) {
    for (int i = 0; i < ub->n; i++) {
        free(ub->nomes[i]);
    }
    free(ub->nomes);
    free(ub->v);
    free(ub);
}

int ub_busca(UniaoBusca* ub, int x) {
    int r = x;
    while (ub->v[r] >= 0) {
        r = ub->v[r]; // Encontrar o líder
    }

    // Compressão do caminho
    while (ub->v[x] >= 0) {
        int aux = ub->v[x];
        ub->v[x] = r;
        x = aux;
    }

    return r;
}

int ub_uniao(UniaoBusca* ub, int x, int y) {
    x = ub_busca(ub, x);
    y = ub_busca(ub, y);

    if (x == y) return x; // Se já estão na mesma aliança, não faz nada

    // União por tamanho
    if (ub->v[x] <= ub->v[y]) {
        ub->v[x] += ub->v[y];
        ub->v[y] = x;
        return x;
    } else {
        ub->v[y] += ub->v[x];
        ub->v[x] = y;
        return y;
    }
}

void imprime(UniaoBusca* ub, int n) {
    for (int i = 0; i < n; i++) {
        printf("Territorio %d -> Lider: %s\n", i + 1, ub->nomes[ub_busca(ub, i)]);
    }
}
