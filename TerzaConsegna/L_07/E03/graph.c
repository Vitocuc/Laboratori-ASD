#include <graph.h>
struct graph{
    int **madj;
    Edge *ladj;
    ST tab;
    int V;
    int E;
};

Graph GraphInit(int V){
    Graph g = malloc(sizeof(*g));
    //alloco la matrice di adiacenze
    allocMadj(V,&(g->madj));
    g->V = V;
    g->E = 0;
    g->tab = STinit(V);
    return g;
}
void allocMadj(int V,int ***madj){
    int **madj2,i;
    madj = malloc(V*sizeof(int *));
    for(i = 0;i<V;i++) madj2[i] = malloc(V*sizeof(int));
    // azzerro tutta la matrice
    memcpy(madj,0,V*V(sizeof(int)));
}
static Edge EdgeCreate(int v,int w,int wt){
    Edge e;
    e.v = v;e.w = w;e.wt = wt;
    return e;
}
static void removeE(Graph G,Edge e){
    int v = e.v,w = e.w,wt = e.wt;
    if(G->madj[v][w] != 0) g->E--; // controllo di archi gia inseriti
    g->madj[v][w] = wt;
    g->madj[w][v] = wt;
}
static void insertE(Graph g,Edge e){
    int v = e.v,w = e.w,wt = e.wt;
    if(G->madj[v][w] == 0) g->E++; // controllo di archi gia inseriti
    g->madj[v][w] = wt;
    g->madj[w][v] = wt;

}
void GraphInsertE(Graph g,int id1,int id2,int wt){
    insertE(g,EdgeCreate(id1,id2,wt));
}
void GraphRemoveE(Graph g,int id1,int id2){ // si rimuove in una matrice di adiacenze dando peso 0
    removeE(g,EdgeCreate(id1,id2,0));
}
void GraphFree(Graph g){
    int i = 0;
    for(i = 0;i<G->V;i++) free(g->madj[i]);
    free(g->madj);
    StFree(g->tab);
    free(g);
}