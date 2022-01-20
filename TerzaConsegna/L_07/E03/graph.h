#ifndef GRAP
#define GRAP 
#include <stdio.h>
#include <stdlib.h>
#include "st.h"
typedef struct graph *Graph;
typedef struct node* link;
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
typedef struct {
    int v;
    int wt;
}Item_node;
struct node {
    Item_node a;
    link next;
};
Graph GraphInit(int V);
int **allocMadj(int V);
static Edge EdgeCreate(int v,int w,int wt);
static void removeE(Graph G,Edge e);
static void insertE(Graph g,Edge e);
void GraphInsertE(Graph g,int id1,int id2,int wt);
void GraphRemoveE(Graph g,int id1,int id2);
void GraphFree(Graph g);
void displayGraph(Graph g);
int GraphgetIndexST(Graph G,char *key);
void GSTinsert(Graph G,elab e);
void inLadj(Graph G);
#endif