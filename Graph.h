/*
*  Name: Vanessa Hurtado
*/

//---------------------------------------------------------------------------


#ifndef _GRAPH_H_INCLUDE
#define _GRAPH_H_INCLUDE

#include <stdio.h>
#include "List.h"

#define UNDEF -1
#define NIL 0
#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct graphG* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void insertionSort(List L, int u);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void Visit(Graph G, List L, int u);
void DFS(Graph G, List S);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
