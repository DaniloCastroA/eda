/**
 * @file bitvet.h
 * @brief Conjunto representado como vetor de bits: o elemento i pertence
 *        ao conjunto se o bit i estiver ligado.
 *
 * Usado no Dijkstra para guardar o conjunto de vertices ja visitados.
 *
 * @note Origem: PDF EDA_07_Conjuntos, slide 15, "Uma interface para
 *       conjuntos quaisquer". A interface foi copiada do slide; bvFree foi
 *       Adicionada. bvIntrsec existe no slide, mas nao e usada aqui.
 */
/* EDA: bitvet.h */
/* ADT: Sets, where pertinence is related to a bit in a Bit Vector */

#ifndef _bitvet
#define _bitvet

typedef struct _bitvector BitVector;

/** @brief Cria um conjunto vazio com capacidade para mx elementos. */
BitVector* bvInit(int mx);

/** @brief Informa se o elemento i pertence ao conjunto (1) ou nao (0). */
int bvGet(BitVector* v,int i);

/** @brief Insere o elemento i no conjunto. */
void bvSet(BitVector* v,int i);

/** @brief Imprime os elementos do conjunto precedidos de um titulo. */
void bvShow(BitVector* v, char* title);

/** @brief Libera a memoria do conjunto. @note Origem: Adicionado. */
void bvFree(BitVector* v);

#endif
