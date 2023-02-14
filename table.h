//
// Created by radouane on 11/7/22.
//

#ifndef SIMPLEXE_TABLE_H
#define SIMPLEXE_TABLE_H

#include <limits.h>
#define M INT_MAX

//structure qui représente le table de l'algorithme de Simplex
typedef struct {
    float *b, *c, *a, z;
    int *base;
} table;









#endif //SIMPLEXE_TABLE_H