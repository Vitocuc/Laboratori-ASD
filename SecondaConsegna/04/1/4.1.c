#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int u;
    int v;
}arco;
void wrapper(arco *archi,int n,int k);
void leggiFile(arco ** archi2,int *n1,int *e1);
void vertexCover(arco *archi,int e,int *sol,int n_nodi,int pos);
int check(int *sol,int n_nodi,arco *archi,int e);
int main(){
    int n_nodi,e;
    arco *archi;
    leggiFile(&archi,&n_nodi,&e);
    wrapper(archi,e,n_nodi);
    free(archi);
}
void leggiFile(arco ** archi2,int *n1,int *e1){
    FILE *fp;
    int n,e,i=0,j;
    arco *archi;
    if((fp = fopen("grafo.txt","r"))== NULL){
        printf("errore nell'apertura del file");
        exit(1);
    }
    fscanf(fp,"%d%d",&n,&e);
    archi = malloc(e*sizeof(arco));
    while(i<e){
        fscanf(fp,"%d %d",&archi[i].u,&archi[i].v);
        i++;
    }
    fclose(fp);
    *archi2 = archi;
    *n1 = n;
    *e1 = e;

}
int check(int *sol,int n_nodi,arco *archi,int e){
    int i,j,cont = 0;
    int *mark = calloc(e,sizeof(int));
    for( i = 0;i<e;i++){
            for(j = 0;j<n_nodi;j++){
            if(mark[i] == 0){
                if(sol[j] && (j == archi[i].u || j == archi[i].v)){
                    mark[i] = 1;
                    cont++;
                }
            }       
        }
    }
    free(mark);
    if(cont>= e) return 1;
    return 0;
    
}
void vertexCover(arco *archi,int e,int *sol,int n_nodi,int pos){
    int i ;
    if(pos>=n_nodi){
        if(check(sol,n_nodi,archi,e)){
            printf("(");
            for(i = 0;i<n_nodi;i++){
                if(sol[i]) printf("%d",i);
            }
            printf(")\n");
        } 
        return;
    }
    sol[pos] = 1;
    vertexCover(archi,e,sol,n_nodi,pos+1);
    sol[pos] = 0;
    vertexCover(archi,e,sol,n_nodi,pos+1);  
}
void wrapper(arco *archi,int e,int n_nodi){
    int *sol;
    sol = malloc(n_nodi*sizeof(int));
    vertexCover(archi,e,sol,n_nodi,0);
    free(sol);
}