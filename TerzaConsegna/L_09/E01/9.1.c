#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
//impostazione algoritmo ricorsivo
void stampa(Graph G,Edge *A,int *sol,int n);
void rimuoviArchi(Graph G,Edge *A, int *sol,int n);
void aggiungiArchi(Graph G,Edge *A, int *sol,int n);
int check(Graph G);
void powerset(int pos,Edge *A, int *sol,int n,int k,int *stop,Graph G);
void wrapper(Graph G,Edge *A,int n);
int main(int argc,char **argv){
    if(argc>2) return 1;
    Graph G;
    Edge *vett;
    int i = 0;
    FILE *fp;
    if((fp = fopen(argv[1],"r"))== NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    G = GRAPHload(fp);
    fclose(fp);
    vett = malloc(getE(G)*sizeof(Edge));
    GRAPHedges(G,vett);
    //for(i = 0;i<getE(G);i++) printf("V:%d W:%d WT:%d",vett[i].v,vett[i].w,vett[i].wt);
    wrapper(G,vett,getE(G));
}
void stampa(Graph G,Edge *A,int *sol,int n){
  int i;
  printf("__________ \n");
  for(i = 0;i<n;i++){
        if(sol[i] == 1) printf("V: %s W: %s \n",STsearchByIndex(getSt(G),A[i].v),STsearchByIndex(getSt(G),A[i].w));
      }
}
void rimuoviArchi(Graph G,Edge *A, int *sol,int n){
   int i ;
   for(i = 0;i<n;i++){
      if(sol[i] == 1) GRAPHremoveE(G,A[i].v,A[i].w);
    }
}
void aggiungiArchi(Graph G,Edge *A, int *sol,int n){
   int i ;
   for(i = 0;i<n;i++){
      if(sol[i] == 1) GRAPHinsertE(G,A[i].v,A[i].w,A[i].wt);
    }
}
int check(Graph G){
  int flag = 0;
  GRAPHdfs(G,&flag);
  if(flag == 0) {
      printf("Ciao");
      return 0;
      }
  return 1;
}
void powerset(int pos,Edge *A, int *sol,int n,int k,int *stop,Graph G){
  int i;
  //condizione di terminazione
  if(pos>= k){
    rimuoviArchi(G,A,sol,n);//rimuovo gli archi
    if(check(G) == 0){
      //stampa(G,A,sol,n); //stampa e aggiorno la variabile
      (*stop) = 1;
    }
    aggiungiArchi(G,A,sol,n);// reinserisco gli archi
  }
  sol[pos] = 1;
  powerset(pos+1,A,sol,n,k,stop,G);
  sol[pos] = 0;
  powerset(pos+1,A,sol,n,k,stop,G);
}
void wrapper(Graph G,Edge *A,int n){
  int stop = 0,k,flag = 0,*sol;
  sol = malloc(n*sizeof(int));
  for(k = 1;k<=n && flag == 0;k++){
      powerset(0,A,sol,n,k,&stop,G);
      if(stop == 1) flag = 1;
  } 
}