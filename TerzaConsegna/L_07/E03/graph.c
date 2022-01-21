#include "graph.h"
struct graph{
    int **madj;
    link *ladj;
    ST tab;
    link z;
    int V;
    int E;
};
typedef struct {
    int v;
    int wt;
}Item_node;
struct node {
    Item_node a;
    link next;
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
void Merge(Edge *A, Edge*B, int l, int q, int r,ST st) {
  int i, j, k;
  elab e1,e2;
  i = l;
  j = q+1;
  for(k = l; k <= r; k++)
    if (i > q)
      B[k] = A[j++];
    else if (j > r)
      B[k] = A[i++];
    else {
        e1 = STselect(st,A[i].v);
        e2 = STselect(st,A[j].v);
        if (Keycmp(Keyget(e1), Keyget(e2))<0 || Keycmp(Keyget(e1), Keyget(e2)) == 0) 
            B[k] = A[i++];
        else
            B[k] = A[j++];
    }
  for ( k = l; k <= r; k++ )
    A[k] = B[k];
  return;
}

void MergeSortR(Edge *A, Edge *B, int l, int r,Graph G) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  MergeSortR(A, B, l, q,G);
  MergeSortR(A, B, q+1, r,G);
  Merge(A, B, l, q, r,G->tab);
}
void MergeSort(Edge *A, int N,Graph G) {
  int l=0, r=N-1;
  Edge *B = (Edge *)malloc(N*sizeof(Edge));
  if (B == NULL) {
    printf("Memory allocation error\n");
    exit(1);
  }
  MergeSortR(A, B, l, r, G);
}
void  GraphEdges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->madj[v][w] != 0)
        a[E++] = EdgeCreate(v, w, G->madj[v][w]);
}
void ordineAlfabeticoMadj(Graph G){
    int i;
    Edge *vett;
    GraphEdges(G,vett);
    MergeSort(vett,G->V,G);
    printf("Archi che incidono su di esso:");
    for(i = 0;i<G->E;i++){
        printf("(V:%d W:%d WT:%d) ",vett[i].v,vett[i].w,vett[i].wt);
    }
}
void sgCompletoLadj(Graph G,char *nome1,char *nome2 , char *nome3){
    int ind1,ind2,ind3,flag = 0;
    link t;
    ind1 = getIndex(G->tab,nome1);
    ind2 = getIndex(G->tab,nome2);
    ind3 = getIndex(G->tab,nome3);
    for(t = G->ladj[ind1];t!= NULL ;t = t->next)
        if(t->a.v == ind2 || t->a.v == ind3) flag ++;
    for(t = G->ladj[ind2];t!=NULL;t = t->next)
        if(t->a.v == ind3) flag ++;
    if(flag == 3) printf("\n Formano un triangolo \n");
    else printf("\n Non formano un triangolo \n");
}

void sgCompletoMadj(Graph G,char *nome1,char *nome2 , char *nome3){
    int ind1,ind2,ind3,flag = 0;
    ind1 = getIndex(G->tab,nome1);
    ind2 = getIndex(G->tab,nome2);
    ind3 = getIndex(G->tab,nome3);
    if(G->madj[ind1][ind2] != 0 && G->madj[ind1][ind2] != 0 && G->madj[ind2][ind3] != 0)
        printf("\n Formano un triangolo \n");
    else printf("\n Non formano un triangolo \n");

}