#include <stdio.h>
// N vertici da 0 a N-1,con E archi come coppie di vertici
// il grafo è non orientato quindi ogni nodo è collegato con tutti gli altri
//ogni arco è nellòa forma u v -> lo definisco come una struct
//utilizzo un powerset per utilizzare ogni sottoinsieme;
//Il vertex cover impone:
//ogni arco,quindi ogni coppia di vertici deve avere un vertice nell'insieme del vertex cover
// lo spazio delle soluzioni è indipendente dall'ordine quindi uso una combinazone
typedef struct{
    int u;
    int v;
}arco;
int main(){
    FILE *fp;
    int n,e,i=0,c;
    if((fp = fopen("grafo.txt","r"))== NULL){
        printf("errore nell'apertura del file");
        exit(1);
    }
    fscanf(fp,"%d%d",&n,&e);
    arco archi[e];
    while(!feof(fp)){
        fscanf(fp,"%d %d",archi[i].u,archi[i].v);
        i++;
    }int *sol;
    c = powerset(archi,sol,n);
    printf("Il numero degli insiemi è %d",c);
}
int powerset(arco *val,int *sol,int k){ // k è la cardinalità dell'insieme
    // caso terminale
    int j,count = 0,n;
    printf(":;\n");
    count++;
    for(n = 1;n<=k;n++){
        count+= powerset_r(val,k,sol,n,0,0);
    }
}
int powerset_r(arco *val,int k,int *sol,int n,int pos,int start){
    int count = 0;
    int i;
    if(pos>=n){
        printf(":");
        for(i= 0;i<n;i++){
            printf("%d",sol[i]);
        }
        printf(";\n");
        return 1;
    }
    for(i = start;i<k;i++){
        sol[pos] = val[i].u;  // oppure .v devo mettere un controllo
        count += powerset_r(val,k,sol,n,pos+1,i+1);
    }
}