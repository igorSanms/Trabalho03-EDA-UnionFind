#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "UnionFind.c"

// Função para redimensionar o array de territórios ao adicionar ou remover
UniaoBusca* redimensionar_ub(UniaoBusca* ub, int novo_tamanho) {
    UniaoBusca* novo_ub = ub_cria(novo_tamanho);

    for (int i = 0; i < (ub->n < novo_tamanho ? ub->n : novo_tamanho); i++) {
        novo_ub->v[i] = ub->v[i];
        strcpy(novo_ub->nomes[i], ub->nomes[i]); // Copia os nomes dos líderes
    }

    ub_libera(ub); // Libera o antigo Union-Find
    return novo_ub; // Retorna o novo com o tamanho ajustado
}

void menu() {
    int op, territorio1, territorio2, num_territorios = 2;
    char escolha_lider[20];
    UniaoBusca* jogo = ub_cria(num_territorios);

    do {
        system("cls");
        printf("\n-- MENU --\n");
        printf("1. Unir dois territorios (formar aliança)\n");
        printf("2. Verificar se dois territorios estao na mesma aliança\n");
        printf("3. Mostrar o estado atual das alianças\n");
        printf("4. Adicionar um territorio\n");
        printf("5. Remover um territorio\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Informe o primeiro territorio (1 a %d): ", num_territorios);
                scanf("%d", &territorio1);
                printf("Informe o segundo territorio (1 a %d): ", num_territorios);
                scanf("%d", &territorio2);

                if (territorio1 < 1 || territorio1 > num_territorios || territorio2 < 1 || territorio2 > num_territorios) {
                    printf("Erro: Um ou ambos os territorios nao existem!\n");
                } else {
                    printf("Escolha o líder para a nova aliança (%s ou %s): ", jogo->nomes[ub_busca(jogo, territorio1 - 1)], jogo->nomes[ub_busca(jogo, territorio2 - 1)]);
                    scanf("%s", escolha_lider);

                    int novo_lider = ub_uniao(jogo, territorio1 - 1, territorio2 - 1); // Ajuste para 0-indexado
                    
                    // Atualizar o líder da nova aliança
                    if (strcmp(escolha_lider, jogo->nomes[territorio1 - 1]) == 0) {
                        strcpy(jogo->nomes[novo_lider], jogo->nomes[territorio1 - 1]);
                    } else {
                        strcpy(jogo->nomes[novo_lider], jogo->nomes[territorio2 - 1]);
                    }

                    printf("Territorios %d e %d unidos sob o lider %s!\n", territorio1, territorio2, jogo->nomes[novo_lider]);
                }
                break;

            case 2:
                printf("Informe o primeiro territorio (1 a %d): ", num_territorios);
                scanf("%d", &territorio1);
                printf("Informe o segundo territorio (1 a %d): ", num_territorios);
                scanf("%d", &territorio2);

                if (territorio1 < 1 || territorio1 > num_territorios || territorio2 < 1 || territorio2 > num_territorios) {
                    if (territorio1 < 1 || territorio1 > num_territorios) {
                        printf("Erro: Territorio %d nao existe!\n", territorio1);
                    }
                    if (territorio2 < 1 || territorio2 > num_territorios) {
                        printf("Erro: Territorio %d nao existe!\n", territorio2);
                    }
                } else {
                    if (ub_busca(jogo, territorio1 - 1) == ub_busca(jogo, territorio2 - 1)) {
                        printf("Territorios %d e %d estao na mesma aliança!\n", territorio1, territorio2);
                    } else {
                        printf("Territorios %d e %d estao em alianças diferentes!\n", territorio1, territorio2);
                    }
                }
                break;

            case 3:
                printf("Estado atual das alianças: \n");
                imprime(jogo, num_territorios);
                break;

            case 4:
                // Adicionar um novo território
                num_territorios++;
                jogo = redimensionar_ub(jogo, num_territorios);
                printf("Territorio %d adicionado!\n", num_territorios);
                break;

            case 5:
                printf("Informe o numero do territorio que deseja remover (1 a %d): ", num_territorios);
                scanf("%d", &territorio1);

                if (territorio1 < 1 || territorio1 > num_territorios) {
                    printf("Erro: Territorio %d nao existe!\n", territorio1);
                } else if (num_territorios <= 2) {
                    printf("Erro: O jogo deve ter no minimo 2 territorios.\n");
                } else {
                    // Remover território
                    for (int i = territorio1 - 1; i < num_territorios - 1; i++) {
                        jogo->v[i] = jogo->v[i + 1];
                        strcpy(jogo->nomes[i], jogo->nomes[i + 1]); // Ajusta os líderes
                    }
                    num_territorios--;
                    jogo = redimensionar_ub(jogo, num_territorios);
                    printf("Territorio %d removido!\n", territorio1);
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

        getch(); // Aguarda a tecla para limpar a tela
    } while (op != 0);

    ub_libera(jogo); // Libera a memória alocada
}

int main() {
    menu();
    return 0;
}
