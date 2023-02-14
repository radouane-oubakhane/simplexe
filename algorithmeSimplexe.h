//
// Created by Radouane OUBAKHANE on 10/31/22.
//

#ifndef SIMPLEXE_ALGORITHMESIMPLEXE_H
#define SIMPLEXE_ALGORITHMESIMPLEXE_H

#include "table.h"

void test(table* tab, int n, int m);

//initialisation de la base
int* initialerBase(int n, int m);

//Choix de la variable sortante
int variableEntrante(float *c, int m);

//Choix de la variable entrante
int variableSortante(float *b, float *a, int ve, int n, int m);

//nombtr pivot
float nombrePivot(float *a, int vs, int ve, int n, int m);

//changement de la base
int* changementBase(int *base, int vs, int ve);

//transformation de la ligne pivot
void transformationLignePivot(float *b, float *a, float *nextB, float *nextA, int n, int m, int vs, float pivot);

//transformation de la colonne pivot
void transformationColonnePivot(float *c, float *a, float *nextC, float *nextA, int n, int m, int vs, int ve);

//transformation des autres cases
void transformationAutresCases(float *b, float *c, float *a, float *nextB, float *nextC, float *nextA, int vs, int ve, int n, int m, float pivot);

//la valeur de Z
float valeurZ(float z, float *b, float *c, float *a, int vs, int ve, int n, int m, float pivot);

//vérification du condition d'arrêt
int positifCondition(float *c, int m);

//dellocation de la mémoire
void free_table(table tab);
void free_memoire(table tab);

//vérification si le problème admet une solution ou non
void admetPasSolution();

#endif //SIMPLEXE_ALGORITHMESIMPLEXE_H
