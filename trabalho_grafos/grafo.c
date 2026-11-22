/**
 * @file grafo.c
 * @brief Operacoes sobre o grafo: criacao, insercao de arestas, impressao
 *        da matriz e das listas de adjacencias, e liberacao.
 */
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/**
 * @brief Cria um grafo com nv vertices e nenhuma aresta.
 *
 * Aloca a struct _grafo do slide e deixa todas as listas vazias
 * (viz[i] = NULL). Encerra o programa se faltar memoria.
 *
 * @param nv numero de vertices (numerados de 0 a nv-1)
 * @return ponteiro para o grafo criado
 */
Grafo* grafoCria(int nv) {
   int i;
   Grafo* g = (Grafo*)malloc(sizeof(Grafo));
   if (g == NULL) { printf("Memoria insuficiente\n"); exit(1); }
   g->nv = nv;
   g->na = 0;
   g->viz = (Viz**)malloc(nv * sizeof(Viz*));
   if (g->viz == NULL) { printf("Memoria insuficiente\n"); exit(1); }
   for (i = 0; i < nv; i++)
      g->viz[i] = NULL;
   return g;
}

/**
 * @brief Cria um no da lista de vizinhos.
 *
 * @param noj vertice vizinho
 * @param peso peso da aresta
 * @return no alocado, com prox = NULL
 */
static Viz* criaViz(int noj, float peso) {
   Viz* v = (Viz*)malloc(sizeof(Viz));
   if (v == NULL) { printf("Memoria insuficiente\n"); exit(1); }
   v->noj = noj;
   v->peso = peso;
   v->prox = NULL;
   return v;
}

/**
 * @brief Insere um no no final de uma lista de vizinhos.
 *
 * Inserir no final mantem a lista na mesma ordem em que as arestas foram
 * informadas, o que facilita a leitura da saida.
 *
 * @param lista endereco do ponteiro para o inicio da lista
 * @param v no a ser inserido
 */
static void insereNoFinal(Viz** lista, Viz* v) {
   Viz* p;
   if (*lista == NULL) { *lista = v; return; }
   for (p = *lista; p->prox != NULL; p = p->prox)
      ;
   p->prox = v;
}

/**
 * @brief Insere a aresta nao dirigida {a,b} com o peso informado.
 *
 * Em um grafo nao dirigido a aresta e um conjunto de 2 vertices (PDF 10,
 * slide 4), entao ela e colocada na lista de a e na lista de b, como nas
 * listas de adjacencias do PDF 10, slides 24-25.
 *
 * @param g grafo
 * @param a uma das extremidades da aresta
 * @param b a outra extremidade
 * @param peso peso da aresta
 */
void grafoInsereAresta(Grafo* g, int a, int b, float peso) {
   insereNoFinal(&g->viz[a], criaViz(b, peso));
   insereNoFinal(&g->viz[b], criaViz(a, peso));
   g->na++;
}

/**
 * @brief Imprime as listas de adjacencias de todos os vertices.
 *
 * Formato: [i]-> (vizinho, peso) -> ... -> NULL, inspirado no desenho
 * "[0]-> 1 28 -> 5 10 -> NULL" do PDF 11, slides 22-30.
 *
 * @param g grafo
 */
void grafoMostraListas(Grafo* g) {
   int i;
   Viz* p;
   for (i = 0; i < g->nv; i++) {
      printf("  [%d]->", i);
      for (p = g->viz[i]; p != NULL; p = p->prox)
         printf(" (%d, %2.0f) ->", p->noj, p->peso);
      printf(" NULL\n");
   }
}

/**
 * @brief Imprime a matriz de adjacencias do grafo.
 *
 * Monta a matriz a partir das listas de adjacencias, seguindo a definicao
 * mat[i][j] = 1 se houver aresta entre i e j, e 0 caso contrario. Como o
 * grafo e nao dirigido, a matriz resultante e simetrica.
 *
 * @param g grafo
 */
void grafoMostraMatriz(Grafo* g) {
   int i, j;
   Viz* p;
   int** mat = (int**)malloc(g->nv * sizeof(int*));
   for (i = 0; i < g->nv; i++) {
      mat[i] = (int*)calloc(g->nv, sizeof(int)); /* tudo 0 */
      for (p = g->viz[i]; p != NULL; p = p->prox)
         mat[i][p->noj] = 1;                      /* existe aresta i-j */
   }
   printf("     ");
   for (j = 0; j < g->nv; j++) printf("%3d", j);
   printf("\n");
   for (i = 0; i < g->nv; i++) {
      printf("  %d |", i);
      for (j = 0; j < g->nv; j++) printf("%3d", mat[i][j]);
      printf("\n");
      free(mat[i]);
   }
   free(mat);
}

/**
 * @brief Libera toda a memoria ocupada pelo grafo.
 *
 * @param g grafo (nao deve ser usado depois desta chamada)
 */
void grafoLibera(Grafo* g) {
   int i;
   Viz *p, *t;
   for (i = 0; i < g->nv; i++) {
      p = g->viz[i];
      while (p != NULL) { t = p->prox; free(p); p = t; }
   }
   free(g->viz);
   free(g);
}
