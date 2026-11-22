/**
 * @file algoritmos.c
 * @brief Kruskal (arvore geradora de custo minimo) e Dijkstra (menores
 *        distancias a partir de um vertice).
 */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "algoritmos.h"
#include "particao.h"
#include "bitvet.h"

/** @brief Valor usado como "infinito" (simbolo ∞ dos slides). */
#define INFINITO FLT_MAX

/**
 * @brief Compara duas arestas para o qsort.
 *
 * Ordena pelo menor peso; em caso de empate, ordena por (u, v) para que
 * a saida seja sempre a mesma.
 *
 * @param a ponteiro para a primeira Aresta
 * @param b ponteiro para a segunda Aresta
 * @return valor negativo, zero ou positivo, como exige o qsort
 *
 * @note Origem: Adicionado.
 */
static int comparaArestas(const void* a, const void* b) {
   const Aresta* x = (const Aresta*)a;
   const Aresta* y = (const Aresta*)b;
   if (x->peso < y->peso) return -1;
   if (x->peso > y->peso) return 1;
   if (x->u != y->u) return x->u - y->u;
   return x->v - y->v;
}

/**
 * @brief Calcula a arvore geradora de custo minimo pelo algoritmo de
 *        Kruskal.
 *
 * Passos do algoritmo:
 *  1. Considere cada no em V como uma arvore separada (floresta).
 *  2. Examine a aresta de menor custo. Se ela unir duas arvores na
 *     floresta, inclua-a.
 *  3. Repita o passo 2 ate todos os nos estarem conectados.
 *
 * As arestas sao extraidas das listas de adjacencias e ordenadas por peso,
 * e a floresta e mantida com Union-Find: uma aresta e incluida apenas se
 * suas extremidades estiverem em arvores diferentes.
 *
 * @param g grafo nao dirigido e ponderado
 * @param arvore vetor de saida com espaco para g->nv - 1 arestas
 * @param custo saida: soma dos pesos das arestas incluidas
 * @return numero de arestas incluidas (g->nv - 1 se o grafo for conexo)
 *
 * @note Origem: passos do PDF 10, slide 38, e uso de Union-Find do PDF 9,
 *       slide 55. Os slides nao trazem codigo C; o codigo foi Adicionado.
 */
int kruskal(Grafo* g, Aresta* arvore, float* custo) {
   int i, k = 0, na = 0, incluidas = 0;
   Viz* p;
   Aresta* arestas;
   Particao* floresta;

   /* Monta o vetor de arestas a partir das listas de adjacencias. Cada
    * aresta {i,j} aparece nas duas listas, entao so e pega quando i < j. */
   arestas = (Aresta*)malloc(g->na * sizeof(Aresta));
   for (i = 0; i < g->nv; i++)
      for (p = g->viz[i]; p != NULL; p = p->prox)
         if (i < p->noj) {
            arestas[na].u = i;
            arestas[na].v = p->noj;
            arestas[na].peso = p->peso;
            na++;
         }

   /* Ordena para que "examinar a aresta de menor custo" seja percorrer
    * o vetor em ordem. */
   qsort(arestas, na, sizeof(Aresta), comparaArestas);

   /* Passo 1: cada no e uma arvore separada (MakeSet, PDF 9). */
   floresta = partCria(g->nv);

   *custo = 0;
   /* Passos 2 e 3: partUnion faz os Finds e devolve 0 quando u e v ja
    * estao na mesma arvore (a aresta formaria ciclo). Para quando ha
    * nv-1 arestas, ou seja, todos os nos conectados. */
   for (k = 0; k < na && incluidas < g->nv - 1; k++) {
      if (partUnion(floresta, arestas[k].u, arestas[k].v)) {
         arvore[incluidas++] = arestas[k];
         *custo += arestas[k].peso;
      }
   }

   partLibera(floresta);
   free(arestas);
   return incluidas;
}

/**
 * @brief Calcula a menor distancia de origem ate cada vertice do grafo
 *        pelo algoritmo de Dijkstra.
 *
 * Usa o vetor dist[] ao lado das listas de adjacencias e guarda o conjunto
 * de vertices visitados em um vetor de bits. O proximo vertice corrente e
 * o nao visitado de menor distancia, escolhido por busca linear, o que da
 * complexidade O(V^2). Em caso de empate e escolhido o de menor indice.
 * Os passos do algoritmo estao como comentarios no corpo da funcao.
 *
 * @param g grafo com pesos nao negativos
 * @param origem vertice de partida
 * @param dist saida: dist[i] = menor distancia de origem ate i
 *             (FLT_MAX se i nao for alcancavel)
 * @param ant saida: ant[i] = vertice anterior a i no menor caminho,
 *            ou -1 para a origem e para vertices nao alcancaveis
 *
 * @note Origem: passos do PDF 11, slides 19-20; estrutura dist[] + listas
 *       do PDF 11, slides 22-30; conjunto de visitados com o BitVector do
 *       PDF EDA_07_Conjuntos. O codigo C e o vetor ant[] foram Adicionados.
 */
void dijkstra(Grafo* g, int origem, float* dist, int* ant) {
   int i, corrente;
   Viz* p;
   BitVector* visitados = bvInit(g->nv);

   /* 1. Defina o no de origem  (parametro "origem")
    * 2. Atribua a todos os nos um valor de distancia ao no de origem:
    *    valor zero ao no de origem, e infinito para todos os outros nos. */
   for (i = 0; i < g->nv; i++) {
      dist[i] = INFINITO;
      ant[i] = -1;
   }
   dist[origem] = 0;

   /* 3. Marque todos os demais nos como nao visitados e o no origem como
    *    corrente (A). (bvInit ja deixou todos os bits em 0 = nao visitado) */
   corrente = origem;

   while (corrente != -1) {
      /* 4. Considere a distancia de todos os nos vizinhos nao visitados ao
       *    no corrente e calcule uma distancia deles ao no origem atraves
       *    do no corrente.
       *    4.1 se o no atual A tiver distancia 6 e houver uma aresta de peso
       *        2 conectando-o com B, a distancia de B atraves de A sera 8.
       *    4.2 Se essa distancia for menor do que a registrada
       *        anteriormente, sobrescreva a distancia de B. */
      for (p = g->viz[corrente]; p != NULL; p = p->prox) {
         int b = p->noj;
         float nova;
         if (bvGet(visitados, b))
            continue;                     /* vizinho ja visitado: ignora */
         nova = dist[corrente] + p->peso;                         /* 4.1 */
         if (nova < dist[b]) {                                    /* 4.2 */
            dist[b] = nova;
            ant[b] = corrente;            /* guarda o caminho */
         }
      }

      /* 5. Ao terminar de considerar todos os vizinhos do no atual A,
       *    marque-o como visitado. Um no visitado nao sera mais verificado;
       *    sua distancia registrada agora e final e minima. */
      bvSet(visitados, corrente);

      /* 6. Se todos os nos tiverem sido visitados, termine.
       *    Caso contrario, marque o no nao visitado com a menor distancia
       *    (ao no de origem) como o proximo "no corrente", e repita a
       *    partir do passo 4.
       *    Se so restarem nos com distancia infinita (grafo desconexo),
       *    tambem termina. */
      corrente = -1;
      for (i = 0; i < g->nv; i++)
         if (!bvGet(visitados, i) && dist[i] != INFINITO &&
             (corrente == -1 || dist[i] < dist[corrente]))
            corrente = i;
   }
   bvFree(visitados);
}

/**
 * @brief Imprime o caminho da origem ate destino usando o vetor ant[].
 *
 * Segue ant[] do destino ate a origem de forma recursiva, para que o
 * caminho saia na ordem origem -> ... -> destino.
 *
 * @param ant vetor de anteriores preenchido por dijkstra()
 * @param destino vertice final do caminho
 *
 * @note Origem: Adicionado.
 */
void mostraCaminho(int* ant, int destino) {
   if (ant[destino] != -1) {
      mostraCaminho(ant, ant[destino]);
      printf(" -> ");
   }
   printf("%d", destino);
}
