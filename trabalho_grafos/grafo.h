/**
 * @file grafo.h
 * @brief Representacao de grafo nao dirigido e ponderado por listas de
 *        adjacencias.
 */
#ifndef GRAFO_H
#define GRAFO_H

/**
 * @brief No de uma lista de adjacencias (um vizinho do vertice).
 */
typedef struct _viz Viz;
struct _viz {
   int noj;     /**< indice do vertice vizinho */
   float peso;  /**< peso da aresta ate o vizinho */
   Viz* prox;   /**< proximo vizinho da lista */
};

/**
 * @brief Grafo representado por um vetor de listas de adjacencias.
 */
struct _grafo {
   int nv;    /* numero de nos ou vertices */
   int na;    /* numero de arestas */
   Viz** viz; /* viz[i] aponta para a lista de arestas incidindo em i */
};

/**
 * @brief Nome curto para a struct _grafo do slide.
 */
typedef struct _grafo Grafo;

/** @brief Cria um grafo com nv vertices e nenhuma aresta. */
Grafo* grafoCria(int nv);

/** @brief Insere a aresta nao dirigida {a,b} com o peso informado. */
void grafoInsereAresta(Grafo* g, int a, int b, float peso);

/** @brief Imprime as listas de adjacencias de todos os vertices. */
void grafoMostraListas(Grafo* g);

/** @brief Imprime a matriz de adjacencias (1 = ha aresta, 0 = nao ha). */
void grafoMostraMatriz(Grafo* g);

/** @brief Libera toda a memoria ocupada pelo grafo. */
void grafoLibera(Grafo* g);

#endif
