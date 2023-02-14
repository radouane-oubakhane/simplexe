//
// Created by radouane on 11/19/22.
//

#ifndef SIMPLEXE_FORMESTANDARD_H
#define SIMPLEXE_FORMESTANDARD_H

#include "table.h"

//Construction du tableau initial
void initialisationStandard(table* tab, int* n, int* m);

//initialisation de la vecteur c
float* initialerCStandard(int m, int type);

//initialisation de la vecteur b
void initialerBStandard(float* b, int n, int i);

//initialisation de la matrice a
void initialerAStandard(int* a, int n, int m, int i);



#endif //SIMPLEXE_FORMESTANDARD_H
