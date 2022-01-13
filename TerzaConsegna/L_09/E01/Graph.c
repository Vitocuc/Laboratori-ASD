#include "Graph.h"
typedef struct node *link;
struct node{
    int v;
    link next;
};
struct grafo{
    //rappresentazione con lista di adiacenze
    link ladj;
    int V;
    int E;
    ST table;
    link z;//Nodo fittizio di fine
};

Graph GraphInit(int V){
    Graph G = malloc(sizeof(*G));
    G->E = 0;
    G->V = V;
    G->ladj = malloc(G->V * sizeof(link));
    G->z = NEW(-1,NULL);
    G->table = STinit(V);
    return G;
}

void Graphfree(Graph G){
    int i;
    link t;
    for(i = 0;i<G->V;i++){
        for(t = G->ladj[i];t!= NULL;t = t->next) free(t);
    }
    free(G->table);
    free(G->z);
    free(G->ladj);
    free(G);
}

Graph GraphLoad(char *in_file){
    FILE *fp;
    Graph G;
    int V,i,id1,id2,wt;
    char label1[MAXL],label2[MAXL];
    if((fp = fopen(in_file,"r")) == NULL){
        printf("errore nell'apertura del file");
        exit(1);
    }
    fscanf(fp,"%d",&V);
    G = GraphInit(V);
    for(i = 0;i<G->V;i++){
        fscanf(fp,"%s",label1);
        STinsert(G->table,label1,i);
    }
    while(fscanf(fp,"%s %s %d",label1,label2,&wt) == 3){
        id1 = STsearch(G->table,label1); //ritorna -1 se sbaglia
        id2 = STsearch(G->table,label2);
        if(id1>= 0 && id2>=0  && wt>0){
            GraphInsertE(G,id1,id2,wt);
        }
    }
    return i;
}

//FUNZIONI DI CUI HA BISOGNO LA GRAPHLOAD
static link NEW(int v,link next){
    link x = malloc(sizeof(*x));
    if(x == NULL){
        return NULL;
    } 
    x->v = v;
    x->next = next;
}

static Edge EdgeCreate(int v,int w,int wt){
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

void insertE(Graph G,Edge e){
    int v = e.v,w = e.w,wt = e.wt;
    G->ladj[v] = NEW(w,G->ladj[v]); // inserimento in lista
    G->E++;
}

void GraphInsertE(Graph G,int id1,int id2,int wt){
    insertE(G,EdgeCreate(id1,id2,wt));
}
//fine funzioni di cui ha bisgno GraphLoad

