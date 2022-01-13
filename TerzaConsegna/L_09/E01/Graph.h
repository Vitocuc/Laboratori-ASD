#ifndef GRAPH
#define GRAPH
#include <stdio.h>
#include <stdlib.h>
#include "ST.h"
#define MAXL 31
typedef struct edge{
    int v;
    int w;
    int wt;
}Edge;
//puntatori opachi
typedef struct grafo *Graph;
Graph GraphInit(int V);
void Graphfree(Graph G);
Graph GraphLoad(char *in_file);
//FUNZIONI DI CUI HA BISOGNO LA GRAPHLOAD
static link NEW(int v,link next);
static Edge EdgeCreate(int v,int w,int wt);
void insertE(Graph G,Edge e);
void GraphInsertE(Graph G,int id1,int id2,int wt);
#endif
