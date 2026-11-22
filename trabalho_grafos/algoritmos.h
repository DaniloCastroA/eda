/**
 * @file algoritmos.h
 * @brief Algoritmos de Kruskal e Dijkstra sobre o grafo de listas de
 *        adjacencias.
 */
#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "grafo.h"

/**
 * @brief Aresta {u,v} com peso, usada para ordenar as arestas no Kruskal
 *        e para devolver a arvore geradora.
 */
typedef struct {
   int u;       /**< uma extremidade da aresta */
   int v;       /**< a outra extremidade */
   float peso;  /**< peso da aresta */
} Aresta;

/** @brief Calcula a arvore geradora de custo minimo pelo algoritmo de Kruskal. */
int kruskal(Grafo* g, Aresta* arvore, float* custo);

/** @brief Calcula as menores distancias a partir de origem (Dijkstra). */
void dijkstra(Grafo* g, int origem, float* dist, int* ant);

/** @brief Imprime o caminho da origem ate destino usando o vetor ant[]. */
void mostraCaminho(int* ant, int destino);

#endif
