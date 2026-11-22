/**
 * @file particao.h
 * @brief Particao dinamica de conjuntos (Union-Find) representada por
 *        vetor, com uniao por altura e compressao de trajetoria.
 *
 * Usada pelo Kruskal para saber se uma aresta une duas arvores diferentes
 * da floresta ou se formaria um ciclo.
 *
 * @note Origem: regras do PDF 9 (Particao de conjuntos): operacoes basicas
 *       (slide 5), representacao por vetor (slides 14-15), union seguro
 *       (slide 18), uniao por altura (slides 23-30), compressao de
 *       trajetoria (slide 35) e uso no Kruskal (slides 52-55). O PDF nao
 *       traz codigo C; a implementacao foi Adicionada seguindo essas regras.
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
