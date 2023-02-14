//
// Created by radouane on 10/31/22.
//

#ifndef SIMPLEXE_METHODEDUAL_H
#define SIMPLEXE_METHODEDUAL_H
#include "table.h"

//Construction du tableau initial
void methodeDual(table* tab, int *n, int *m);

//initialisation de la vecteur c
float* initialerCDual(int n, int m, int type);

//initialisation de la vecteur b
void initialerBDual(float* b, int n, int i, int* signeTab);

//initialisation de la matrice a
void initialerADual(float * a, int n, int m, int i, int* signeTab);

//la ajout des Variable Écarts
void ajouterVariableEcartsDual(float * a, int n, int m, int* typeTab);

#endif //SIMPLEXE_METHODEDUAL_H
