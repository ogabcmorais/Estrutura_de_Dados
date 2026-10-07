/* ======================================================================
 Lista de Exercícios — Aula 06 // Listas dinâmicas encadeadas
 * ====================================================================== */

#include <stdlib.h>
#include <string.h>
#include "lista_tarefas.h"


struct elemento {
    struct tarefa dados;
    struct elemento *prox;
};

typedef struct elemento Elem;


ListaTarefas* cria_lista(void) {
    ListaTarefas *li = (ListaTarefas*) malloc(sizeof(ListaTarefas));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(ListaTarefas* li) {
    Elem *no;
    if (li == NULL)
        return;
    while (*li != NULL) {
        no = *li;
        *li = (*li)->prox;
        free(no);
    }
    free(li);
}

int tamanho_lista(ListaTarefas* li) {
    int cont = 0;
    Elem *no;
    if (li == NULL)
        return -1;
    for (no = *li; no != NULL; no = no->prox)
        cont++;
    return cont;
}

int lista_vazia(ListaTarefas* li) {
    if (li == NULL)
        return -1;
    return (*li == NULL);
}

int lista_cheia(ListaTarefas* li) {
    if (li == NULL)
        return -1;
    return 0;   /* lista dinâmica: ela nunca fica cheia */
}

int insere_tarefa_inicio(ListaTarefas* li, struct tarefa t) {
    Elem *no;
    if (li == NULL)
        return 0;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = t;
    no->prox = *li;
    *li = no;
    return 1;
}

int insere_tarefa_final(ListaTarefas* li, struct tarefa t) {
    Elem *no, *aux;
    if (li == NULL)
        return 0;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = t;
    no->prox = NULL;
    if (*li == NULL) {
        *li = no;
    } else {
        aux = *li;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = no;
    }
    return 1;
}

/* ordena pela prioridade do menor para o maior. 
   em empate, a nova tarefa fica depois das que já tinham a mesma prioridade. */
int insere_tarefa_ordenada(ListaTarefas* li, struct tarefa t) {
    Elem *no, *ant, *atual;
    if (li == NULL)
        return 0;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = t;
    if (*li == NULL || (*li)->dados.prioridade > t.prioridade) {
        no->prox = *li;
        *li = no;
    } else {
        ant = *li;
        atual = ant->prox;
        while (atual != NULL && atual->dados.prioridade <= t.prioridade) {
            ant = atual;
            atual = atual->prox;
        }
        ant->prox = no;
        no->prox = atual;
    }
    return 1;
}

int remove_tarefa_inicio(ListaTarefas* li) {
    Elem *no;
    if (li == NULL || *li == NULL)
        return 0;
    no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_tarefa_final(ListaTarefas* li) {
    Elem *ant = NULL, *no;
    if (li == NULL || *li == NULL)
        return 0;
    no = *li;
    while (no->prox != NULL) {
        ant = no;
        no = no->prox;
    }
    if (ant == NULL)
        *li = NULL;
    else
        ant->prox = NULL;
    free(no);
    return 1;
}

int remove_tarefa(ListaTarefas* li, int codigo) {
    Elem *ant = NULL, *no;
    if (li == NULL || *li == NULL)
        return 0;
    no = *li;
    while (no != NULL && no->dados.codigo != codigo) {
        ant = no;
        no = no->prox;
    }
    if (no == NULL)
        return 0;
    if (ant == NULL)
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int busca_tarefa_pos(ListaTarefas* li, int pos, struct tarefa *t) {
    Elem *no;
    int i = 1;
    if (li == NULL || t == NULL || pos <= 0)
        return 0;
    no = *li;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    *t = no->dados;
    return 1;
}

int busca_tarefa_cod(ListaTarefas* li, int codigo, struct tarefa *t) {
    Elem *no;
    if (li == NULL || t == NULL)
        return 0;
    no = *li;
    while (no != NULL && no->dados.codigo != codigo)
        no = no->prox;
    if (no == NULL)
        return 0;
    *t = no->dados;
    return 1;
}

/* ======================================
 * NOVAS FUNÇÕES 
 * ======================================*/

/* Questão 1 -------------------------------------------*/
int conta_tarefas_prioridade(ListaTarefas* li, int prioridade) {
    int cont = 0;
    Elem *no;
    if (li == NULL)
        return -1;
    for (no = *li; no != NULL; no = no->prox) {
        if (no->dados.prioridade == prioridade)
            cont++;
    }
    return cont;
}

/* Questão 2 --------------------------------------------*/

int tarefa_mais_urgente(ListaTarefas* li, struct tarefa *t) {
    Elem *no, *melhor;
    if (li == NULL || t == NULL || *li == NULL)
        return 0;
    melhor = *li;
    for (no = (*li)->prox; no != NULL; no = no->prox) {
        if (no->dados.prioridade < melhor->dados.prioridade)
            melhor = no;
    }
    *t = melhor->dados;
    return 1;
}

/* Questão 3 ---------------------------------------------*/
int busca_tarefa_desc(ListaTarefas* li, char *texto, struct tarefa *t) {
    Elem *no;
    if (li == NULL || texto == NULL || t == NULL)
        return 0;
    for (no = *li; no != NULL; no = no->prox) {
        if (strstr(no->dados.descricao, texto) != NULL) {
            *t = no->dados;
            return 1;
        }
    }
    return 0;
}

/* Questão 4 ----------------------------------------------*/
int insere_tarefa_final_prioridade(ListaTarefas* li, struct tarefa t) {
    Elem *no, *aux, *ultimo_igual = NULL, *fim = NULL;
    if (li == NULL)
        return 0;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = t;

    for (aux = *li; aux != NULL; aux = aux->prox) {
        if (aux->dados.prioridade == t.prioridade)
            ultimo_igual = aux;
        fim = aux;
    }

    if (ultimo_igual != NULL) {
        no->prox = ultimo_igual->prox;
        ultimo_igual->prox = no;
    } else if (fim == NULL) {    /* lista vazia */
        no->prox = NULL;
        *li = no;
    } else {     /* sem a prioridade: vai pro final */
        no->prox = NULL;
        fim->prox = no;
    }
    return 1;
}

/* Questão 5 ------------------------------------------------*/
int remove_tarefas_prioridade(ListaTarefas* li, int prioridade) {
    Elem *ant = NULL, *no, *rem;
    int removidos = 0;
    if (li == NULL)
        return -1;
    no = *li;
    while (no != NULL) {
        if (no->dados.prioridade == prioridade) {
            rem = no;
            no = no->prox;
            if (ant == NULL)
                *li = no;             
            else
                ant->prox = no;
            free(rem);
            removidos++;
        } else {
            ant = no;
            no = no->prox;
        }
    }
    return removidos;
}

/* Questão 6 --------------------------------------------------*/
int inverte_lista(ListaTarefas* li) {
    Elem *ant = NULL, *atual, *prox;
    if (li == NULL)
        return 0;
    atual = *li;
    while (atual != NULL) {
        prox = atual->prox;
        atual->prox = ant;
        ant = atual;
        atual = prox;
    }
    *li = ant;
    return 1;
}

/* Questão 7 ------------------------------------------------- */
int remove_tarefa_pos(ListaTarefas* li, int pos) {
    Elem *ant = NULL, *no;
    int i = 1;
    if (li == NULL || *li == NULL || pos <= 0)
        return 0;
    no = *li;
    while (no != NULL && i < pos) {
        ant = no;
        no = no->prox;
        i++;
    }
    if (no == NULL)                    /* pos maior que o tamanho */
        return 0;
    if (ant == NULL)
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

/* Questão 8 -------------------------------------------------*/
int mescla_tarefas(ListaTarefas* dst, ListaTarefas* src) {
    Elem *no, *fim;
    int transferidas = 0;
    if (dst == NULL || src == NULL)
        return -1;
    if (dst == src || *src == NULL)
        return 0;
    for (no = *src; no != NULL; no = no->prox)
        transferidas++;
    if (*dst == NULL) {
        *dst = *src;
    } else {
        fim = *dst;
        while (fim->prox != NULL)
            fim = fim->prox;
        fim->prox = *src;
    }
    *src = NULL;
    return transferidas;
}
