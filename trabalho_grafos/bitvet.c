/**
 * @file bitvet.c
 * @brief Implementacao do conjunto como vetor de bits.
 *
 * Observacao: o slide usa sizeof(int) (= 4) como quantidade de bits por
 * int, embora um int tenha 32 bits. O codigo continua correto, pois a
 * mesma conta e usada em bvInit, bvGet e bvSet; so aproveita 4 bits de
 * cada int. Foi mantido igual ao slide.
 */
#include <stdio.h>
#include <stdlib.h>
#include "bitvet.h"

/**
 * @brief Conjunto de ate max elementos guardado em um vetor de ints.
 * @note Origem: PDF EDA_07_Conjuntos, slide 16. Copiado do slide.
 */
struct _bitvector {
       int max;
       int *vector;
};

/**
 * @brief Cria um conjunto vazio com capacidade para max elementos.
 *
 * Calcula quantos ints sao necessarios e zera todos os bits.
 *
 * @param max quantidade maxima de elementos (0 a max-1)
 * @return conjunto alocado, inicialmente vazio
 *
 * @note Origem: PDF EDA_07_Conjuntos, slide 16. Copiado do slide.
 */
BitVector* bvInit(int max) {
       int i,size = sizeof(int);
       int num =((max-1)/size)+1; /* numero de ints para max bits */

         BitVector* bv=(BitVector*)malloc(sizeof(BitVector));
         bv->max=max;
         bv->vector=(int *)malloc(num*sizeof(int));
         for (i=0; i<num; i++)
                bv->vector[i]=0;
         return bv;
}

/**
 * @brief Informa se o elemento i pertence ao conjunto.
 *
 * Testa o bit i com uma mascara (1 << posicao).
 *
 * @param bv conjunto
 * @param i elemento consultado
 * @return 1 se i pertence ao conjunto, 0 caso contrario
 *
 * @note Origem: PDF EDA_07_Conjuntos, slide 17. Copiado do slide.
 */
int bvGet(BitVector* bv,int i){
  int res=(bv->vector[i/sizeof(int)])&(1 << i%sizeof(int));
       return (res!=0);
}

/**
 * @brief Insere o elemento i no conjunto, ligando o bit correspondente.
 *
 * @param bv conjunto
 * @param i elemento a inserir
 *
 * @note Origem: PDF EDA_07_Conjuntos, slide 17. Copiado do slide.
 */
void bvSet(BitVector* bv,int i){
       bv->vector[i/sizeof(int)] |= 1 << i%sizeof(int);
}

/**
 * @brief Imprime os elementos do conjunto precedidos de um titulo.
 *
 * @param bv conjunto
 * @param title texto impresso antes da lista de elementos
 *
 * @note Origem: declarada na interface do PDF EDA_07_Conjuntos, slide 15;
 *       a implementacao, que nao aparece no slide, foi Adicionada.
 */
void bvShow(BitVector* bv, char* title) {
       int i;
       printf("%s{", title);
       for (i = 0; i < bv->max; i++)
              if (bvGet(bv, i)) printf(" %d", i);
       printf(" }\n");
}

/**
 * @brief Libera a memoria do conjunto.
 *
 * @param bv conjunto (nao deve ser usado depois desta chamada)
 *
 * @note Origem: Adicionado.
 */
void bvFree(BitVector* bv) {
       free(bv->vector);
       free(bv);
}
