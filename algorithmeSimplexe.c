//
// Created by OUBAKHANE Radouane on 10/31/22.
//

#include <stdlib.h>
#include <stdio.h>
#include "algorithmeSimplexe.h"

void test(table* tab, int n, int m) {

    tab->base = initialerBase(n, m);
    tab->z = 0;

    int i,j;

    float cTest[5] = {4, 5, 0, 0, 0};

    tab->c = (float*) malloc(m * sizeof(float));
    for (i = 0; i < m; i++)
    {
        *(tab->c + i) = cTest[i];
    }

    float bTest[3] = {8, 7, 3};

    tab->b = (float*) malloc(n * sizeof(float));
    for (i = 0; i < n; i++)
    {
        *(tab->b + i) = bTest[i];
    }

    float aTest[3][5] = {{2, 1, 1, 0, 0},
                         {1, 2, 0, 1, 0},
                         {0, 1, 0, 0, 1}
                        };

    tab->a = (float*) malloc(m * n * sizeof(float));
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            *(tab->a + i * m + j) = aTest[i][j];
        }
    }
}

//initialisation de la base
int* initialerBase(int n, int m)
{
    int i, *base;
    base = (int*) malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        *(base+i) = (i + m - n + 1);
    }
    return base;
}

//Choix de la variable sortante
int variableEntrante(float *c, int m)
{
    int i, ve = 0;
    float temp = *c;
    for (i = 0; i < m; i++)
    {
        if (*(c+i) > temp)
        {
            temp = *(c+i);
            ve = i;
        }
    }
    return ve;
}

//Choix de la variable entrante
int variableSortante(float *b, float *a, int ve, int n, int m)
{
    int i, vs = NULL, j = 0, *temp2;
    float *temp1, min;
    temp1 = (float*) malloc(n * sizeof(float));
    temp2 = (int*) malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        if (*(a+i*m+ve) > 0)
        {
            *(temp1 + i) = *(b + i) / *(a + i * m + ve);
            *(temp2 + i) = 1;
        }
        else
        {
            *(temp1 + i) = 0;
            *(temp2 + i) = 0;
        }
    }



    min = *temp1;
    for (i = 1; i < n; i++)
    {
        if (*(temp2 + i) == 1)
        {
            if (min > *(temp1 + i))
            {
                min = *(temp1 + i);
                vs = i;
            }
        }
    }
    return vs;
}

//nombtr pivot
float nombrePivot(float *a, int vs, int ve, int n, int m)
{
    int i, j;
    float pivot;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (i == vs && j == ve)
            {
                pivot = *(a+i*m+j);
                return pivot;
            }
            else
            {
                continue;
            }
        }
    }
}

//changement de la base
int* changementBase(int *base, int vs, int ve)
{
    *(base+vs) = ve + 1;
    return base;
}

//transformation de la ligne pivot
void transformationLignePivot(float *b, float *a, float *nextB, float *nextA, int n, int m, int vs, float pivot)
{
    int i;
    *(nextB + vs) = *(b + vs) / pivot;
    for (i = 0; i < m; i++)
    {
        *(nextA + vs * m + i) = *(a + vs * m + i) / pivot;
    }
}

//transformation de la colonne pivot
void transformationColonnePivot(float *c, float *a, float *nextC, float *nextA, int n, int m, int vs, int ve)
{
    int i;
    *(nextC + ve) = 0;
    for (i = 0; i < n; i++)
    {
        if (i != vs)
        {
            *(nextA + i * m + ve) = 0;
        }
    }
}

//transformation des autres cases
void transformationAutresCases(float *b, float *c, float *a, float *nextB, float *nextC, float *nextA, int vs, int ve, int n, int m, float pivot)
{

    int i, j;
    float aaaa;
    aaaa = *(nextB + 2);
    aaaa = *(b + 2);
    for (i = 0; i < m; i++)
    {
        if (i != ve)
        {
            *(nextC + i) = *(c + i) - ((*(c + ve) * (*(a + vs * m + i))) / pivot);

            aaaa = *(nextC + i);
        }
    }


    aaaa = *(nextB + 2);
    aaaa = *(b + 2);

    for (i = 0; i < n; i++)
    {
        if (i != vs)
        {
            for (j = 0; j < m; j++)
            {
                if (j != ve)
                {
                    *(nextA + i * m + j) = *(a + i * m + j) - ((*(a + i * m + ve) * (*(a + vs * m + j)) / pivot));
                    aaaa = *(nextB + 2);
                    aaaa = *(b + 2);
                }
            }
        }
    }
    aaaa = *(nextB + 2);
    aaaa = *(b + 2);


    for (i = 0; i < n; i++)
    {
        if (i != vs)
        {
            *(nextB + i) = *(b + i) - ((*(b + vs) * (*(a + i * m + ve))) / pivot);
            aaaa = *(nextB + 2);
            aaaa = *(b + 2);
        }
    }
    aaaa = *(nextB + 2);
    aaaa = *(b + 2);

    // *(nextB+vs) = *(b+vs) / pivot;
}

//la valeur de Z
float valeurZ(float z, float *b, float *c, float *a, int vs, int ve, int n, int m, float pivot)
{
    float tt;
    z += ((*(b+vs) * (*(c+ve))) / pivot);
    tt = *(b+vs);
    tt = (*(c+ve));
    tt = pivot;
    tt = ((*(b+vs) * (*(c+ve))) / pivot);
    return z;
}

//vérification du condition d'arrêt
int positifCondition(float *c, int m)
{
    float sdf;
    int i;
    for (i = 0; i < m; i++)
    {
        sdf = *(c+i);
        if (*(c+i) > 0)
        {
            return 1;
        }
    }
    return 0;
}

//dellocation de la mémoire
void free_table(table tab)
{
    free(tab.a);
    free(tab.b);
    free(tab.c);
}
void free_memoire(table tab)
{
    free_table(tab);
    free(tab.base);
}

//vérification si le problème admet une solution ou non
void admetPasSolution() {
    printf("\n-*******************************- Il n\'y a pas de solution optimale -*******************************-\n");
    printf("\n-**************************************************************- Réalisé par : Radouane OUBAKHANE.\n");
}


