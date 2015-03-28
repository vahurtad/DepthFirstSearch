/*
*  Name: Vanessa Hurtado
*/

//---------------------------------------------------------------------------

#include <stdlib.h>
#include "List.h"
#include "Graph.h"

// Private Structs -----------------------------------------------------------
typedef struct graphG
{
    List* a;
    int* color;
    int* parent;
    int* discover;
    int* finish;
    int vertices, edges, time;
    ////order  -- size --
} graphG;

// Constructors-Destructors ---------------------------------------------------
/* Creates a new Graph object reference with initialized fields */
Graph newGraph(int n)
{
    if( n < 0)
    {
        printf("Size is a negative number");
        exit(1);
    }

    Graph g = malloc(sizeof(struct graphG));
    g->vertices = n;
    g->edges = 0;
    g->time = 0;
    g->color = calloc(n+1, sizeof(int));
    g->parent = calloc(n+1, sizeof(int));
    g->discover = calloc(n+1, sizeof(int));
    g->finish = calloc(n+1, sizeof(int));
    g->a = calloc(n+1, sizeof(List));

    int i;
    for(i = 0; i <= n; i++)
    {
        g->color[i] = WHITE;
        g->discover[i] = UNDEF;
        g->finish[i] = UNDEF;
        g->parent[i] = NIL;
        g->a[i] = newList();
    }
    return g;
}
/* Frees all memory associated with the graph then sets it to null*/
void freeGraph(Graph* pG)
{
    if(!(pG == NULL) && !(*pG == NULL))
    {
        free((*pG)->color);
        free((*pG)->discover);
        free((*pG)->finish);
        free((*pG)->parent);
        int i;
        for(i = 1; i <= (*pG)->vertices; i++)
            freeList(&(*pG)->a[i]);
    }
    free((*pG)->a);
    (*pG)->a = NULL;
    free((*pG)->color);
    (*pG)->color = NULL;
    free((*pG)->parent);
    (*pG)->parent = NULL;
    free((*pG)->discover);
    (*pG)->discover = NULL;
    free((*pG)->finish);
    (*pG)->finish = NULL;
    free(*pG);
    *pG = NULL;
}

// Access functions -----------------------------------------------------------
/* Returns corresponding field values. */
int getOrder(Graph G)
{
    if(G == NULL)
    {
        printf("Empty Graph.");
        exit(1);
    }
    return G->vertices;
}

int getSize(Graph G)
{
    if(G == NULL)
    {
        printf("Empty Graph.");
        exit(1);
    }
    return G->edges;
}

int getParent(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Empty Graph.");
        exit(1);
    }

    if(u < 1 || u > getOrder(G))
        exit(1);
    return G->parent[u];
}

int getDiscover(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Empty Graph.");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
        exit(1);
    return G->discover[u];
}

int getFinish(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Empty Graph.");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
        exit(1);
    return G->finish[u];
}

// Manipulation procedures ----------------------------------------------------
/* Inserts new edge joining u to v. */
void addEdge(Graph G, int u, int v)
{
    if(G == NULL)
    {
        printf("Empty Graph.");
        exit(1);
    }

    if(u < 1 || u > getOrder(G))
    {
        printf("Edge is out of bound.");
        exit(1);
    }

    if(v < 1 || v > getOrder(G))
    {
        printf("Edge is out of bound.");
        exit(1);
    }

    List U = G->a[u];
    List V = G->a[v];

    insertionSort(U, v);
    insertionSort(V, u);
    G->edges++;
}
/* Helper function to add vertices into the adjacency list*/
void insertionSort(List L, int u)
{
    if(length(L) == 0)
    {
        append(L, u);
        return;
    }

    for(moveTo(L,0); getIndex(L) != -1; moveNext(L))
    {
        if(getElement(L) > u)
        {
            insertBefore(L,u);
            break;
        }
    }
    if(getIndex(L) == -1)
        append(L, u);
}

/* Inserts a new directed edge from u to v. */
void addArc(Graph G, int u, int v)
{
    if(G == NULL)
    {
        printf("Empty Graph.");
        exit(1);
    }

    if(u < 1 || u > getOrder(G))
    {
        printf("Edge is out of bound.");
        exit(1);
    }

    if(v < 1 || v > getOrder(G))
    {
        printf("Edge is out of bound.");
        exit(1);
    }
    insertionSort(G->a[u], v);
    G->edges++;
}

/* Discovers the connected components of the graph*/
void Visit(Graph G, List L, int u)
{
    int v;
    G->time++;
    G->discover[u] = G->time;
    G->color[u] = GRAY;

    List adj = G->a[u];

    for(moveTo(adj, 0); getIndex(adj) != -1; moveNext(adj))
    {
        v = getElement(adj);
        if(G->color[v] == WHITE)
        {
            G->parent[v] = u;
            Visit(G, L, v);
        }
    }
    G->color[u] = BLACK;
    G->time++;
    G->finish[u] = G->time;
    prepend(L, u);
}
/* Depth-First Search algorithm. Runs DFS on graph G*/
void DFS(Graph G, List S)
{
    List stackList = copyList(S);
    clear(S);

    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        G->color[i]	= WHITE;
        G->parent[i] = NIL;
    }
    G->time = 0;
    int u;
    for(moveTo(stackList, 0); getIndex(stackList) != -1; moveNext(stackList))
    {
        u = getElement(stackList);
        if(G->color[u] == WHITE)
            Visit(G, S, u);
    }
    freeList(&stackList);
}

// Other operations -----------------------------------------------------------
/* Adjacency list of Graph G is reversed and returns the transpose*/
Graph transpose(Graph G)
{
    Graph t = newGraph(getOrder(G));

    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        List temp = G->a[i];
        moveTo(temp, 0);
        if(length(temp) == 0)
            continue;
        else
        {
            while(getIndex(temp) != -1)
            {
                addArc(t, getElement(temp), i);
                moveNext(temp);
            }
        }
    }
    return t;
}

/* Makes a copy of Graph G*/
Graph copyGraph(Graph G)
{
    Graph copy = newGraph(getOrder(G));

    int i;
    for(i = 1; i <= getOrder(G); i ++)
    {
        if((G->a[i]) != NULL)
            copy->a[i] = copyList(G->a[i]);
    }
    return copy;
}

/* Prints the adjacency list of G */
void printGraph(FILE *out, Graph G)
{
    int i;
    for(i = 1; i <= G->vertices; i++)
    {
        fprintf(out, "%d:", i);
        printList(out, G->a[i]);
        fprintf(out, "\n");
    }
}
