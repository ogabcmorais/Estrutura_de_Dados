#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct lista {
    int qtd;
    struct produto dados[MAX];
};

/* ======================================================================
 * Funções base (Aula 05)
 * Convenção: retornam 1 em caso de sucesso e 0 em caso de falha.
 * Posições em busca_lista_pos são contadas a partir de 1.
 * ====================================================================== */

Lista* cria_lista(void) {
    Lista *li = (Lista*) malloc(sizeof(struct lista));
    if (li != NULL)
        li->qtd = 0;
    return li;
}

void libera_lista(Lista* li) {
    free(li);
}

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return -1;
    return li->qtd;
}

int lista_cheia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == MAX);
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return -1;
    return (li->qtd == 0);
}

int busca_lista_pos(Lista* li, int pos, struct produto *p) {
    if (li == NULL || pos <= 0 || pos > li->qtd)
        return 0;
    *p = li->dados[pos - 1];
    return 1;
}

int busca_lista_cod(Lista* li, int cod, struct produto *p) {
    int i;
    if (li == NULL)
        return 0;
    for (i = 0; i < li->qtd; i++) {
        if (li->dados[i].codigo == cod) {
            *p = li->dados[i];
            return 1;
        }
    }
    return 0;
}

int insere_lista_final(Lista* li, struct produto p) {
    if (li == NULL || li->qtd == MAX)
        return 0;
    li->dados[li->qtd] = p;
    li->qtd++;
    return 1;
}

int insere_lista_inicio(Lista* li, struct produto p) {
    int i;
    if (li == NULL || li->qtd == MAX)
        return 0;
    for (i = li->qtd - 1; i >= 0; i--)
        li->dados[i + 1] = li->dados[i];
    li->dados[0] = p;
    li->qtd++;
    return 1;
}

/* Inserção ordenada de forma crescente pelo campo codigo */
int insere_lista_ordenada(Lista* li, struct produto p) {
    int i, k;
    if (li == NULL || li->qtd == MAX)
        return 0;
    i = 0;
    while (i < li->qtd && li->dados[i].codigo < p.codigo)
        i++;
    for (k = li->qtd - 1; k >= i; k--)
        li->dados[k + 1] = li->dados[k];
    li->dados[i] = p;
    li->qtd++;
    return 1;
}

/* Remoção com deslocamento (preserva a ordem) */
int remove_lista(Lista* li, int cod) {
    int i, k = 0;
    if (li == NULL || li->qtd == 0)
        return 0;
    while (k < li->qtd && li->dados[k].codigo != cod)
        k++;
    if (k == li->qtd)
        return 0;
    for (i = k + 1; i < li->qtd; i++)
        li->dados[i - 1] = li->dados[i];
    li->qtd--;
    return 1;
}

/* Remoção otimizada: o último elemento ocupa a posição removida */
int remove_lista_otimizado(Lista* li, int cod) {
    int i = 0;
    if (li == NULL || li->qtd == 0)
        return 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd)
        return 0;
    li->dados[i] = li->dados[li->qtd - 1];
    li->qtd--;
    return 1;
}

int remove_lista_inicio(Lista* li) {
    int i;
    if (li == NULL || li->qtd == 0)
        return 0;
    for (i = 1; i < li->qtd; i++)
        li->dados[i - 1] = li->dados[i];
    li->qtd--;
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL || li->qtd == 0)
        return 0;
    li->qtd--;
    return 1;
}

/* ======================================================================
 * NOVAS FUNÇÕES - Lista de Exercícios, Aula 05
 * ====================================================================== */

/* Questão 1 -----------------------------------------------------------
 * Devolve 1 se cabem mais n inserções, 0 caso contrário.
 * Compara n com o espaço livre (MAX - qtd); a subtração evita overflow
 * que poderia ocorrer em qtd + n para n muito grande.
 */
int lista_tem_espaco(Lista* li, int n) {
    if (li == NULL || n < 0)
        return 0;
    return (n <= MAX - li->qtd);
}

/* Questão 2 ----------------------------------------------------------- */
float soma_precos(Lista* li) {
    int i;
    float soma = 0.0f;
    if (li == NULL)
        return 0.0f;
    for (i = 0; i < li->qtd; i++)
        soma += li->dados[i].preco;
    return soma;
}

/* Questão 3 ----------------------------------------------------------- */
int busca_por_nome(Lista* li, char *nome, struct produto *p) {
    int i;
    if (li == NULL || nome == NULL)
        return 0;
    for (i = 0; i < li->qtd; i++) {
        if (strcmp(li->dados[i].nome, nome) == 0) {
            if (p != NULL)
                *p = li->dados[i];
            return 1;
        }
    }
    return 0;
}

/* Questão 4 -----------------------------------------------------------
 * Mantém a lista em ordem decrescente de preco. Em caso de preços
 * iguais, o novo produto é inserido depois dos já existentes.
 */
int insere_lista_decrescente(Lista* li, struct produto p) {
    int i, k;
    if (li == NULL || li->qtd == MAX)
        return 0;
    i = 0;
    while (i < li->qtd && li->dados[i].preco >= p.preco)
        i++;
    for (k = li->qtd - 1; k >= i; k--)
        li->dados[k + 1] = li->dados[k];
    li->dados[i] = p;
    li->qtd++;
    return 1;
}

/* Questão 5 -----------------------------------------------------------
 * Comparação estrita (>) para que, em caso de empate, permaneça o
 * primeiro produto de maior preço. A remoção é feita diretamente pelo
 * índice (técnica otimizada), evitando que uma busca por codigo atinja
 * outro produto com o mesmo código.
 */
int remove_mais_caro(Lista* li, struct produto *removido) {
    int i, pos;
    if (li == NULL || li->qtd == 0)
        return 0;
    pos = 0;
    for (i = 1; i < li->qtd; i++) {
        if (li->dados[i].preco > li->dados[pos].preco)
            pos = i;
    }
    if (removido != NULL)
        *removido = li->dados[pos];
    li->dados[pos] = li->dados[li->qtd - 1];
    li->qtd--;
    return 1;
}

/* Questão 6 ----------------------------------------------------------- */
int conta_faixa_preco(Lista* li, float min, float max) {
    int i, cont = 0;
    if (li == NULL)
        return 0;
    for (i = 0; i < li->qtd; i++) {
        if (li->dados[i].preco >= min && li->dados[i].preco <= max)
            cont++;
    }
    return cont;
}

/* Questão 7 -----------------------------------------------------------
 * Após remover a posição i, o último elemento passa a ocupar i e ainda
 * não foi avaliado; por isso i só avança quando NÃO há remoção.
 */
int remove_abaixo_de(Lista* li, float precoMinimo) {
    int i = 0, removidos = 0;
    if (li == NULL)
        return 0;
    while (i < li->qtd) {
        if (li->dados[i].preco < precoMinimo) {
            li->dados[i] = li->dados[li->qtd - 1];
            li->qtd--;
            removidos++;
        } else {
            i++;
        }
    }
    return removidos;
}

/* Questão 8 -----------------------------------------------------------
 * Percorre origem; insere ao final de destino cada produto cujo codigo
 * ainda não exista em destino. Para assim que destino ficar cheio.
 * Códigos repetidos dentro da própria origem também são ignorados, pois
 * o primeiro já terá sido inserido em destino.
 */
int mescla_listas(Lista* destino, Lista* origem) {
    int i, j, existe, inseridos = 0;
    if (destino == NULL || origem == NULL)
        return 0;
    for (i = 0; i < origem->qtd; i++) {
        if (destino->qtd == MAX)
            break;
        existe = 0;
        for (j = 0; j < destino->qtd; j++) {
            if (destino->dados[j].codigo == origem->dados[i].codigo) {
                existe = 1;
                break;
            }
        }
        if (!existe) {
            destino->dados[destino->qtd] = origem->dados[i];
            destino->qtd++;
            inseridos++;
        }
    }
    return inseridos;
}
