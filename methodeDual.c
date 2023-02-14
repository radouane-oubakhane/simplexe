//
// Created by radouane on 10/31/22.
//

#include <stdlib.h>
#include <stdio.h>
#include "methodeDual.h"
#include "algorithmeSimplexe.h"

//Construction du tableau initial
void methodeDual(table* tab, int *n, int *m)
{
    int type = 1;
    int* signeTab;
    int* typeTab;

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
    *m += *n;

    printf("\nVeuillez entrer les coefficients de la fonction objectif : ");
    tab->c = initialerCDual(*n, *m, type);


    printf("\nLes contraintes du programme\n");


    tab->b = (float*) malloc(*n * sizeof(float));
    tab->a =  (float*) malloc(*m * *n * sizeof(float));
    signeTab = (int*) malloc(*n * sizeof(int));
    typeTab = (int*) malloc(*n * sizeof(int));

    int i;
    for (i = 0; i < *n; i++)
    {
        do {
            printf("\nVeuillez entrer le typtab->e du contrainte  numero %d (= : 1, <= : 2, >= : 3) : ", i + 1);
            scanf("%d", (typeTab + i));
        } while (*(typeTab + i) < 1 || *(typeTab + i) > 3);

        printf("\nVeuillez entrer le second membre du contrainte  numero %d : ", i + 1);
        initialerBDual(tab->b, *n, i, (signeTab + i));

        printf("\nVeuillez entrer la contrainte numero %d : \n", i + 1);
        initialerADual(tab->a, *n, *m, i, (signeTab + i));
    }

    table dualTab;

    int temp = *n;
    *n = *m;
    *m = temp;

    dualTab.z = 0;
    dualTab.base = initialerBase(*n, *m);

    dualTab.a =  (float*) malloc((*m) * (*n) * sizeof(float));
    dualTab.b = (float*) malloc(*n * sizeof(float));
    dualTab.c = (float*) malloc(*m * sizeof(float));

    for (i = 0; i < *n; ++i)
    {
        *(dualTab.b + i) = *(tab->c + i);
    }

    for (i = 0; i < *m; ++i)
    {
        *(dualTab.c + i) = *(tab->b + i);
    }


    int j;
    for (i = 0; i < *m; ++i)
    {
        for (j = 0; j < *n; j++)
        {
            *(dualTab.a + i * *m + j) = *(tab->a + i * *m + j);

        }
    }
    ajouterVariableEcartsDual(dualTab.a, *n, *m, typeTab);
    *tab = dualTab;

}

//initialisation de la vecteur c
float* initialerCDual(int n, int m, int type)
{
    int i;
    float *c, temp;
    c = (float*) malloc(m * sizeof(float));
    for (i = 0; i < m; i++)
    {
        if (i < (m - n))
        {
            printf("\nx%d * ",i+1);
            scanf("%f", &temp);
            *(c+i) = temp * (float) type;
        }
        else
        {
            *(c+i) = 0;
        }
    }
    return c;
}

//initialisation de la vecteur b
void initialerBDual(float* b, int n, int i, int* signeTab)
{
    float temp;
    scanf("%f", &temp);

    *signeTab = temp < 0 ? -1 : 1;
    *(b+i) = temp * (float) (*signeTab);
}

//initialisation de la matrice a
void initialerADual(float * a, int n, int m, int i, int* signeTab)
{
    int j;
    float temp;
    for (j = 0; j < (m - n); j++)
    {
        printf("\nx%d = ", j+1);
        scanf("%f", &temp);
        *(a+i*m+j) = temp * (float) (*signeTab);
    }

}

//la ajout des Variable Écarts
void ajouterVariableEcartsDual(float * a, int n, int m, int* typeTab) {
    int temp = m - n;
    for (int i = 0; i < n; ++i) {
        for (int j = temp; j < m; ++j) {
            if (j == temp + i)
                if (*(typeTab + i) == 1)
                    *(a+i*m+j) = 0;
                else if (*(typeTab + i) == 2)
                    *(a+i*m+j) = 1;
                else if (*(typeTab + i) == 3)
                    *(a+i*m+j) = -1;
        }
    }
}

