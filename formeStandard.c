//
// Created by radouane on 11/19/22.
//

#include "formeStandard.h"
#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "algorithmeSimplexe.h"


//Construction du tableau initial
void initialisationStandard(table* tab, int* n, int* m)
{
    int type = 1;
    tab->z = 0;
    tab->base = initialerBase(*n, *m);

    do {
        printf("\nVeuillez entrer le type d'optimisation (Max = 1, Min = 2) : ");
        scanf("%d", &type);
    } while (type < 1 || type > 2 );

    if (type == 2)
    {
        type = -1;
    }



    printf("\nVeuillez entrer le nombre des varaibles : ");
    scanf("%d", m);

    printf("\nVeuillez entrer le nombre des contraintes : ");
    scanf("%d", n);

    printf("\nVeuillez entrer les coefficients de la fonction objectif : ");
    tab->c = initialerCStandard(*m, type);

    printf("\nLes contraintes du programme\n");


    tab->b = (float*) malloc(*n * sizeof(float));
    tab->a =  (float*) malloc(*m * *n * sizeof(float));

    int i;
    for (i = 0; i < *n; i++)
    {
        printf("\nVeuillez entrer la contrainte numero %d : \n", i + 1);
        initialerAStandard(tab->a, *n, *m, i);

        printf("\nVeuillez entrer le second membre du contrainte  numero %d : ", i + 1);
        initialerBStandard(tab->b, *n, i);
    }
}

//initialisation de la vecteur c
float* initialerCStandard(int m, int type)
{
    int i;
    float *c, temp;
    c = (float*) malloc(m * sizeof(float));
    for (i = 0; i < m; i++)
    {
        printf("\nx%d * ",i+1);
        scanf("%f", &temp);

        *(c+i) = type * temp;
    }
    return c;
}

//initialisation de la vecteur b
void initialerBStandard(float* b, int n, int i)
{
    scanf("%f", b+i);
}

//initialisation de la matrice a
void initialerAStandard(int* a, int n, int m, int i)
{
    int j;
    for (j = 0; j < m; j++)
    {
        printf("\nx%d = ", j+1);
        scanf("%f", (a+i*m+j));
    }

}

