/*
*  Name: Vanessa Hurtado
*/

//---------------------------------------------------------------------------

#include <stdio.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[])
{
    int size = 8;

    List L = newList();
    Graph G = newGraph(size);
    Graph gT = NULL;

    int i;
    for(i = 1; i <= size; i++)
        append(L, i);

    printf("\nGraph Adjacency List: \n");
    addArc(G, 1,2);
    addArc(G, 2,3);
    addArc(G, 2,5);
    addArc(G, 2,6);
    addArc(G, 3,4);
    addArc(G, 3,7);
    addArc(G, 4,3);
    addArc(G, 4,8);
    addArc(G, 5,1);
    addArc(G, 5,6);
    addArc(G, 6,7);
    addArc(G, 7,6);
    addArc(G, 7,8);
    addArc(G, 8,8);

    printGraph(stdout, G);

    //Run depth-first search on graph G
    DFS(G, L);

    printf("\n");
    printf("x:  d  f  p\n");
    for(i = 1; i <= size; i++){
        printf("%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }
    printf("\nStack: \n");
    printList(stdout, L);
    printf("\n");
    printf("\nTranspose of G: \n");
    gT = transpose(G);
    printGraph(stdout, gT);

    //Run depth-first search on graph G
    DFS(gT, L);

    printf("\n");
    printf("x:  d  f  p\n");
    for(i = 1; i <= size; i++){
        printf("%d: %2d %2d %2d\n", i, getDiscover(gT, i), getFinish(gT, i), getParent(gT, i));
    }
    printf("\nStack: \n");
    printList(stdout, L);
    printf("\n");

    int scc = 0;
    for (i = 1; i <= getOrder(G); i++) {
        if (getParent(gT, i) == NIL)
            scc++;
    }
    printf("\n");
    printf("G contains %d strongly connected components:", scc);

    List S[scc];
    int j = scc;
    for (moveTo(L, 0); getIndex(L) >= 0; moveNext(L))
    {
        if (getParent(gT, getElement(L)) == NIL)
        {
            j--;
            S[j] = newList();
        }

        if (j == scc)
            break;
        append(S[j], getElement(L));
    }

    for (i = 0; i < scc; i++)
    {
        printf("\nComponent %d:", i + 1);
        printList(stdout, S[i]);
        freeList(&(S[i]));
    }

    freeGraph(&G);
    freeGraph(&gT);

    freeList(&L);
    return 0;
}
