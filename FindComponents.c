/*
*  Name: Vanessa Hurtado
*/

//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    int size = 0;
    int v1, v2;

    if (argc != 3) {
        printf("Wrong Usage: input file output file");
        exit(1);
    }
    FILE *p;
    p = fopen("here.txt", "w");

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if (in == NULL || out == NULL) {
        printf("File does not exist.");
        exit(1);
    }

    //Reads first line and gets size for graph
    fscanf(in, "%d", &size);
    Graph G = newGraph(size);
    List L = newList();

    while (fgetc(in) != EOF) {
        fscanf(in, "%d", &v1);
        fscanf(in, "%d", &v2);

        if (v1 == 0 && v2 == 0)
            break;
        addArc(G, v1, v2);
    }

    //Append list with vertex numbers in order
    int i;
    for (i = 1; i <= size; i++)
        append(L, i);

    fprintf(out, "Adjacency list representation of G: \n");
    printGraph(out, G);

    DFS(G, L);
    Graph T = transpose(G);
    DFS(T, L);

    int scc = 0;

    for (i = 1; i <= getOrder(G); i++) {
        if (getParent(T, i) == NIL)
            scc++;
    }
    fprintf(out, "\n");
    fprintf(out, "G contains %d strongly connected components:", scc);
    
    //finding stringly connected components
    List S[scc];
    int j = scc;
    for (moveTo(L, 0); getIndex(L) >= 0; moveNext(L))
    {
        if (getParent(T, getElement(L)) == NIL)
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
        fprintf(out, "\nComponent %d:", i + 1);
        printList(out, S[i]);
        freeList(&(S[i]));
    }

    fclose(in);
    fclose(out);

    freeGraph(&G);
    freeGraph(&T);

    freeList(&L);
    return 0;
}
