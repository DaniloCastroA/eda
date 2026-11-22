/**
 * @file particao.c
 * @brief Implementacao do Union-Find por vetor, com uniao por altura e
 *        compressao de trajetoria.
 *
 * O PDF 9 descreve as operacoes, mas nao traz codigo C; todo o codigo
 * deste arquivo foi escrito a partir das regras dos slides indicados.
 */
#include <stdio.h>
#include <stdlib.h>
#include "particao.h"

/**
 * @brief Particao de U = {0..n-1} guardada em vetores.
 *
 * Cada elemento aponta para o seu pai; a raiz (representante) tem -1.
 */
struct _particao {
   int n;       /**< tamanho do universo U = {0..n-1} */
   int* pai;    /**< pai[i] = -1 se i e raiz (representante) */
   int* posto;  /**< altura da arvore (valido para as raizes) */
};

/**
 * @brief Cria n conjuntos unitarios {0}, {1}, ..., {n-1}.
 *
 * Equivale a aplicar MakeSet(x) a todos os elementos: a configuracao
 * inicial e uma floresta de n nos isolados, cada um raiz de si mesmo.
 *
 * @param n quantidade de elementos
 * @return particao alocada
 */
Particao* partCria(int n) {
   int i;
   Particao* p = (Particao*)malloc(sizeof(Particao));
   p->n = n;
   p->pai = (int*)malloc(n * sizeof(int));
   p->posto = (int*)malloc(n * sizeof(int));
   for (i = 0; i < n; i++) {
      p->pai[i] = -1;   /* cada no e raiz de si mesmo */
      p->posto[i] = 0;  /* altura 0 */
   }
   return p;
}

/**
 * @brief Devolve o representante do conjunto que contem x.
 *
 * Sobe pelos pais ate a raiz e, em seguida, aplica a compressao de
 * trajetoria: todo no do caminho de x ate a raiz passa a apontar
 * diretamente para a raiz, encurtando as proximas buscas.
 *
 * @param p particao
 * @param x elemento consultado
 * @return raiz da arvore que contem x
 */
int partFind(Particao* p, int x) {
   int raiz = x, j, prox;
   /* 1a passada: sobe ate a raiz (pai == -1) */
   while (p->pai[raiz] != -1)
      raiz = p->pai[raiz];
   /* 2a passada: cada no do caminho passa a apontar para a raiz */
   j = x;
   while (j != raiz) {
      prox = p->pai[j];
      if (prox != raiz) p->pai[j] = raiz;
      j = prox;
   }
   return raiz;
}

/**
 * @brief Une os conjuntos que contem x e y.
 *
 * Encontra as raizes com Find (union seguro) e pendura a arvore mais
 * baixa na mais alta, para a altura nao crescer. Em caso de empate a
 * escolha e indiferente e a altura da nova raiz cresce de 1.
 *
 * @param p particao
 * @param x elemento do primeiro conjunto
 * @param y elemento do segundo conjunto
 * @return 1 se uniu dois conjuntos diferentes, ou 0 se x e y ja estavam
 *         no mesmo conjunto (no Kruskal, isso indica que formaria ciclo)
 */
int partUnion(Particao* p, int x, int y) {
   int rx = partFind(p, x);
   int ry = partFind(p, y);
   if (rx == ry)
      return 0;                       /* mesmo conjunto: nada a fazer */
   if (p->posto[rx] < p->posto[ry]) {
      p->pai[rx] = ry;                /* rx (mais baixo) pendurado em ry */
   } else if (p->posto[rx] > p->posto[ry]) {
      p->pai[ry] = rx;                /* ry (mais baixo) pendurado em rx */
   } else {
      p->pai[ry] = rx;                /* empate: indiferente... */
      p->posto[rx]++;                 /* ...e a altura cresce de 1 */
   }
   return 1;
}

/**
 * @brief Libera a memoria da particao.
 *
 * @param p particao (nao deve ser usada depois desta chamada)
 */
void partLibera(Particao* p) {
   free(p->pai);
   free(p->posto);
   free(p);
}
