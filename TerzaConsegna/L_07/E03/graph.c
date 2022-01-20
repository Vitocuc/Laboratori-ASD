#include "graph.h"
struct graph{
    int **madj;
    link *ladj;
    ST tab;
    link z;
    int V;
    int E;
};
static link newEdge(int v,int wt,link next){
    link x= malloc(sizeof(*x));
    x->a.v = v;
    x->a.wt = wt;
    x->next = next;
    return x;
}
Graph GraphInit(int V){
    Graph g = malloc(sizeof(*g));
    //alloco la matrice di adiacenze
    g->madj = allocMadj(V);
    g->V = V;
    g->E = 0;
    g->z = newEdge(-1,-1,NULL);
    g->tab = STinit(V);
    return g;
}
int **allocMadj(int V){
    int **madj,i;
    madj = calloc(V,sizeof(int *));
    for(i = 0;i<V;i++) madj[i] = calloc(V,sizeof(int));
    // azzerro tutta la matrice
    return madj;
}
static Edge EdgeCreate(int v,int w,int wt){
    Edge e;
    e.v = v;e.w = w;e.wt = wt;
    return e;
}
static void removeE(Graph G,Edge e){
    int v = e.v,w = e.w,wt = e.wt;
    if(G->madj[v][w] != 0) G->E--; // controllo di archi gia inseriti
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}
static void insertE(Graph G,Edge e){
    int v = e.v,w = e.w,wt = e.wt;
    if(G->madj[v][w] == 0) G->E++; // controllo di archi gia inseriti
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;

}
void GraphInsertE(Graph g,int id1,int id2,int wt){
    insertE(g,EdgeCreate(id1,id2,wt));
}
void GraphRemoveE(Graph g,int id1,int id2){ // si rimuove in una matrice di adiacenze dando peso 0
    removeE(g,EdgeCreate(id1,id2,0));
}
void GraphFree(Graph G){
    int i = 0;
    for(i = 0;i<G->V;i++) free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}
void displayGraph(Graph g){
    int i,j;
    elab e1,e2;
    for(i = 0;i<g->E;i++)
        for(j = 0;j<g->E;j++){
            if(g->madj[i][j] != 0){
                // uso l'indice per trovare la 
                e1 = STselect(g->tab,i);
                e2 = STselect(g->tab,j);
                printf("v: %s%s , w:%s%s , wt %d",e1.id_elab,e1.id_rete,e2.id_elab,e2.id_rete,g->madj[i][j]);
            }       
        }
}
int GraphgetIndexST(Graph G,char *key){
    return getIndex(G->tab,key);
}
void GSTinsert(Graph G,elab e){
    STinsert(G->tab,e );
}
static void insertE2(Graph G,Edge e){
    int v = e.v,w = e.w,wt = e.wt;
    G->ladj[v] = newEdge(w,wt,G->ladj[v]);
    G->ladj[w] = newEdge(v,wt,G->ladj[w]);
}
void insertELadj(Graph G,int v,int w,int wt){
    insertE2(G,EdgeCreate(v,w,wt));
}
void inLadj(Graph G){
    int i,j;
    for(i = 0;i<G->V;i++){
        for(j = 0;j<G->V;j++){
            if(G->madj[i][j] != 0){
                insertELadj(G,i,j,G->madj[i][j]);
            }
        }
    }
}
void ordineAlfabetico(){

}