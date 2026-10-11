#ifndef LISTA_H
#define LISTA_H

#define MAX 100

struct produto {
    int codigo;
    char nome[30];
    float preco;
};

typedef struct lista Lista;

/* ja implementadas na aula 05  */
Lista* cria_lista(void);
void libera_lista(Lista* li);
int busca_lista_pos(Lista* li, int pos, struct produto *p);
int busca_lista_cod(Lista* li, int cod, struct produto *p);
int insere_lista_final(Lista* li, struct produto p);
int insere_lista_inicio(Lista* li, struct produto p);
int insere_lista_ordenada(Lista* li, struct produto p);
int remove_lista(Lista* li, int cod);
int remove_lista_otimizado(Lista* li, int cod);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);
int lista_vazia(Lista* li);

/* novas funções da lista 04 */
int   lista_tem_espaco(Lista* li, int n);
float soma_precos(Lista* li);
int   busca_por_nome(Lista* li, char *nome, struct produto *p);
int   insere_lista_decrescente(Lista* li, struct produto p);
int   remove_mais_caro(Lista* li, struct produto *removido);
int   conta_faixa_preco(Lista* li, float min, float max);
int   remove_abaixo_de(Lista* li, float precoMinimo);
int   mescla_listas(Lista* destino, Lista* origem);

#endif 
