#ifndef GRAP
#define GRAP 1
#include <stdio.h>
#include <stdlib.h>
#include <st.h>
typedef struct edge{ 
    int v; 
    int w;
    int wt;
}Edge;
typedef struct{
    elab elab1;
    elab elab2;
    int flusso;
}Item;
typedef struct graph *Graph;
Graph GraphInit(int V);
static void allocMadj(int V,int ***madj);
static Edge EdgeCreate(int v,int w,int wt);
static void removeE(Graph G,Edge e);
static void insertE(Graph g,Edge e);
void GraphInsertE(Graph g,int id1,int id2,int wt);
void GraphRemoveE(Graph g,int id1,int id2);
void GraphFree(Graph g);
#endif