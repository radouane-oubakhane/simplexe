//
// Created by radouane on 11/19/22.
//

#ifndef SIMPLEXE_METHODEM_H
#define SIMPLEXE_METHODEM_H

#include "table.h"
//Construction du tableau initial
void initialisationMethodeM(table* tab, int* n, int* m);

//initialisation de la vecteur c
float* initialerCMethodeM(int n, int m, int type);

//initialisation de la vecteur b
void initialerBMethodeM(float* b, int n, int i, int* signeTab);

//initialisation de la matrice a
void initialerAMethodeM(float * a, int n, int m, int i, int* signeTab);

//la ajout des Variable Écarts
void ajouterVariableEcartsMethodeM(float * a, int n, int m, int* typeTab);



#endif //SIMPLEXE_METHODEM_H
