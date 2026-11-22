/**
 * @file particao.h
 * @brief Particao dinamica de conjuntos (Union-Find) representada por
 *        vetor, com uniao por altura e compressao de trajetoria.
 *
 * Usada pelo Kruskal para saber se uma aresta une duas arvores diferentes
 * da floresta ou se formaria um ciclo.
 */
#ifndef PARTICAO_H
#define PARTICAO_H

typedef struct _particao Particao;

/** @brief Cria n conjuntos unitarios {0}, {1}, ..., {n-1} (MakeSet). */
Particao* partCria(int n);

/** @brief Devolve o representante do conjunto que contem x (Find). */
int partFind(Particao* p, int x);

/** @brief Une os conjuntos de x e y (Union); devolve 0 se ja eram o mesmo. */
int partUnion(Particao* p, int x, int y);

/** @brief Libera a memoria da particao. */
void partLibera(Particao* p);

#endif
