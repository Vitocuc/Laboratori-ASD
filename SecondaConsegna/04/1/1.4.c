#include <stdio.h>
typedef struct{
    int u;
    int v;
}arco;
void wrapper(arco *archi,int n,int k);
void leggiFile(arco ** archi2,int *n1,int *e1);
void powerset_r(int *val,int k,int *sol,int n,int pos,int start,arco *archi,int e);
int check(int *sol,int n,arco *archi,int k);
int *convert(arco *archi,int e,int k);
int *merge(int *v1,int *v2,int e);
int main(){
    int n_nodi,e;
    arco *archi;
    leggiFile(&archi,&n_nodi,&e);
    wrapper(archi,e,n_nodi);
}
void leggiFile(arco ** archi2,int *n1,int *e1){
    FILE *fp;
    int n,e,i=0,c;
    arco *archi;
    if((fp = fopen("grafo.txt","r"))== NULL){
        printf("errore nell'apertura del file");
        exit(1);
    }
    fscanf(fp,"%d%d",&n,&e);
    archi = malloc(e*sizeof(arco));
    while(i<e){
        fscanf(fp,"%d %d",archi[i].u,archi[i].v);
        i++;
    }
    fclose(fp);
    *archi2 = archi;

}
int check(int *sol,int n,arco *archi,int k){
    int i,j,flag;
    //ciclo che mi controlla
    for(i = 0;i<k;i++){
        flag = 1;
        for(j = 0;j<n;j++) {
            if(sol[j] == archi[i].u || sol[j] == archi[i].v) // allora archi[i] fa parte di W
                flag = 0;
        }
        if(flag == 1) return 1;// allora non appartiene e quidi sol non è un vertex cover
    }
    return 0;

}
int *convert(arco *archi,int e,int k){
    // da finire questa funzione
    int v1[k],v[k],i;
    for(i = 0;i<e;i++) v[i] = archi[i].u;
    for(i = 0;i<e;i++){
        v[i] = archi[i].u;
    }
    //ordinare e unire i due vettori v1 e v2
    v = merge(v1,e);
    return v;
}
void wrapper(arco *archi,int e,int k){
    int sol[k],*val,i = 0,flag,j;
    val = convert(archi,e,k);
    for(i = 2;i<=k;i++){// n = 2 perchè è il numero minimo per un sottoinsiemte dato che un arco per definzione esiste solo tra due nodi
        powerset_r(val,k,sol,i,0,0,archi,e); // questo for mi permette di stampare una partizione per volta
    } 
}
void powerset_r(int *val,int k,int *sol,int n,int pos,int start,arco *archi,int e){
    //condizione di terminazione
    int i;
    if(pos>=n) {// n modificato nel for
        // check se questo sottoinsieme è un vertex cover
        if(check(sol,n,archi,e) == 0){ // stampa soluzione trovata finora
            printf("(");
            for(i = 0;i<n;i++){
                printf("%d ",sol[i]);
            }
            printf("),");
        }
    }
    //ciclo per cvostruzione della soluzione
    for(i = start;i<k;i++){ // i = start evito le ripetizione
        sol[pos] = val[i];
        powerset_r(val,k,sol,n,e,pos+1,i+1,archi);
    } 

}