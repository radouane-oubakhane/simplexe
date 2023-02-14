#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "algorithmeSimplexe.h"
#include "methodeM.h"
#include "formeStandard.h"
#include "methodeDual.h"


int main(int argc, char const *argv[])
{
    table tab, nextTab;
    int type;
    float pivot = 0;
    int n = 0;
    int m = 0;
    int ve = 0;
    int vs = 0;

    printf("-*******************************- Logiciel de résolution du Programme Linéaire par Simplexe -*******************************-\n");


    //Cas simple PL Standard
    //initialisationStandard(&tab, &n, &m);



    //le votre choix entre la méthode primal et la méthode dual
    do {
        printf("\nVeuillez entrer le votre choix : la méthode primal = 1 ou la méthode dual = 2 : ");
        scanf("%d", &type);
    } while (type < 1 || type > 2 );

    if (type == 2)
    {
        //la méthode dual
        methodeDual(&tab, &n, &m);
    }
    else
        //la méthode primal
        initialisationMethodeM(&tab, &n, &m);


    //vérification si le problème admet une solution ou non
    if (positifCondition(tab.c, m) == 0)
    {
        admetPasSolution();
        return 0;
    }






    do {
        //Allocation de la mémoire
        nextTab.a = (float*) malloc(m * n * sizeof(float));
        nextTab.b = (float*) malloc(n * sizeof(float));
        nextTab.c = (float*) malloc(m * sizeof(float));

        //Choix de la variable entrante
        ve = variableEntrante(tab.c, m);

        //Choix de la variable sortante
        vs = variableSortante(tab.b, tab.a, ve, n, m);

        //nombre pivot
        pivot = nombrePivot(tab.a, vs, ve, n, m);

        //changement de base
        nextTab.base = changementBase(tab.base, vs, ve);

        nextTab.z = valeurZ(tab.z, tab.b, tab.c, tab.a, vs, ve, n, m, pivot);

        //Transformation de la ligne pivot
        transformationLignePivot(tab.b, tab.a, nextTab.b, nextTab.a, n, m, vs, pivot);

        // Transformation de la colonne pivot
        transformationColonnePivot(tab.c, tab.a, nextTab.c, nextTab.a, n, m, vs, ve);

        //Transformation des autres cases du tableau
        transformationAutresCases(tab.b, tab.c, tab.a, nextTab.b, nextTab.c, nextTab.a, vs, ve, n, m, pivot);

        //Passage au tableau suivant
        free_table(tab);
        tab = nextTab;

    //vérification du condition d'arrêt
    } while (positifCondition(nextTab.c, m));


    //Affichage
    printf("\n-*******************************- La solution optimale -*******************************-\n");
    printf("\nZ = %f", tab.z);

    for (int i = 0; i < n; ++i)
    {
        if (*(tab.base + i) <= (m - n))
        {
            printf("\nx%d = %f", *(tab.base + i), *(tab.b + *(tab.base + i)));
        }
    }

    free_memoire(tab);

    printf("\n-**************************************************************- Réalisé par : Radouane OUBAKHANE.\n");

    return 0;
}



