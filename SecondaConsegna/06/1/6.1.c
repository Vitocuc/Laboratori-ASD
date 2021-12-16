#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int inizio;
    int fine;
}att;
void displaySol(att *val,int n,int *cont,int *dp);
void displaySol_R(att *val,int *cont,int max,int *dp);
int intersezione(att v1,att v2);
void dp_lis(att *v, int n);
void swap(att *v,int i,int j);
void ord_v(att *v,int n);
void leggiFile(att **v,int *n,char *s); 
int main(int argc,char **argv){
    int n;
    att *v;
    if(argc<2) return 1;
    leggiFile(&v,&n,argv[1]);
    dp_lis(v,n);
}
void leggiFile(att **v,int *n,char *s){
    FILE *fp; 
    att *vett;
    int i = 0,n1 = 0;
    if((fp = fopen(s,"r"))== NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    fscanf(fp,"%d",&n1);
    vett = malloc(n1* sizeof(att));
    while(!feof(fp)){
        fscanf(fp,"%d%d",&vett[i].inizio,&vett[i].fine);
        i++;
    }
    *v = vett;
    *n = n1;
    fclose(fp);
}
void dp_lis(att *v,int n){
    int i,j,*dp,*cont;
    dp = malloc(n*sizeof(int));
    cont = malloc(n*sizeof(int));
    ord_v(v,n);
    dp[0] = v[0].fine-v[0].inizio;
    cont[0] = -1;
    for(i = 1;i<n;i++){
        dp[i] = v[i].fine-v[i].inizio;
        for(j = i-1;j>=0;j--){
            if((intersezione(v[j],v[i]) == 0)){
                if(dp[j]+v[i].fine-v[i].inizio>dp[i]){
                    dp[i] = dp[j]+ v[i].fine-v[i].inizio;
                    cont[i] = j;
                }  
            }
            if(dp[i] == v[i].fine-v[i].inizio) cont[i] = -1;
        }
    }
    displaySol(v,n,cont,dp);
    free(dp);
    free(cont);
}
void displaySol(att *val,int n,int *cont,int *dp){
    int i = 0, max = 0;
    for(i = 0;i<n;i++){
        if(dp[i]>dp[max]) max = i;
    }
    displaySol_R(val,cont,max,dp);
}
void displaySol_R(att *val,int *cont,int max,int *dp){
    if(max == -1){
        return;
    }
    displaySol_R(val,cont,cont[max],dp);
    printf("(%d,%d) ",val[max].inizio,val[max].fine);
}
int intersezione(att v1,att v2){
    if(v1.inizio<v2.fine && v2.inizio<v1.fine) return 1;
    return 0;
}
void swap(att *v,int i,int j){
    att appo;
    appo = v[i];
    v[i] = v[j];
    v[j] = appo;
}
void ord_v(att *v,int n){
    int i,j;
    for(i = 0;i<n;i++){
        for(j = i+1;j<n;j++)
            if(v[j].fine<v[i].fine) swap(v,i,j);
    }
}
