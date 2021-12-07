#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int inizio;
    int fine;
}att;
void displaySol(att *v,int *dp,int n);
int intersezione(att v1,att v2);
void dp_lis(att *v, int n);
int max(int *dp,int n);
void swap(att *v,int i,int j);
void ord_v(att *v,int n);
void ord_v2(att *v,int n);
void leggiFile(att **v,int *n,char *s);
void greedy(att *v,int n);
void inv_greedy(att *v,int n);
int main(){
    int n;
    att *v;
    leggiFile(&v,&n,"att.txt");
    //greedy(v,n);
    /*
    printf("\n");
    inv_greedy(v,n);*/
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
void dp_lis(att *v, int n){
    int dif[n+1],dp[n+2]; // inserisco n+1 per poter stampare la soluzione
    int i,j = 0;
    ord_v2(v,n);
    memset(dp,0,(n+2)*sizeof(int));
    dp[0] = 0; // stato fittizio per stampare la soluzione
    dp[1] = v[0].fine - v[0].inizio;//suppongo primo elemento gia preso
    for(i = 1;i<=n;i++){ 
        dp[i] = v[i-1].fine - v[i-1].inizio;
        for(j = 1;j<=n;j++){
            if((intersezione(v[i-1],v[j-1]) == 0) && dp[i]<dp[j]+1) dp[i] += dp[j]+1; 
            else if(dp[i]<=dp[j]) dp[i] = dp[j]; // non ha senso verificare se ha intersezione
        }
    }
    displaySol(v,dp,n);
    
}
void displaySol(att *v,int *dp,int n){
        int i;
        for(i = n;i>=1;i--)
            if(dp[i] != dp[i-1]) printf("(%d,%d) ",v[i-1].inizio,v[i-1].fine);
}
int intersezione(att v1,att v2){
    if(v1.inizio<v2.fine && v2.inizio<v1.fine) return 1;
    return 0;
}
void inv_greedy(att *v,int n){
    int i = 0,diff = 0;
    ord_v(v,n);
    att x = v[n-1];
    diff = v[n-1].fine -v[n-1].inizio;
    int dp[n]; // la riempio con le differenze degli intervalli
    printf("\n(%d,%d)",x.inizio,x.fine);
    for(i = 0;i<n;i++){
        dp[i] = v[i].fine - v[i].inizio;
    }
    // tolgo le intersezioni degli intervalli
    for(i = n-2;i>=0;i--){
        //suppongo di prendere x come primo intervallo
        if(v[i].fine <= x.inizio){
            // allora non ha intersezione
            diff += dp[i];
            printf("\n(%d,%d)",v[i].inizio,v[i].fine);
            x = v[i];
        }
    }
    printf("Diff: %d",diff);
}
void swap(att *v,int i,int j){
    att appo;
    appo = v[i];
    v[i] = v[j];
    v[j] = appo;
}
void ord_v(att *v,int n){
    int i,j;
    //ordino
    for(i = 0;i<n;i++){
        for(j = i+1;j<n;j++)
            if(v[j].fine<v[i].fine) swap(v,i,j);
    }
    for(i = 0;i<n-1;i++){
        if(v[i].fine == v[i+1].fine){
            if(v[i].inizio < v[i+1].inizio) swap(v,i,i+1);
        }
    }
}
void ord_v2(att *v,int n){
    int i,j;
    for(i = 0;i<n;i++){
        for(j = i+1;j<n;j++)
            if(v[j].inizio<v[i].inizio) swap(v,i,j);
    }
    for(i = 0;i<n-1;i++){
        if(v[i].inizio == v[i+1].inizio){
            if(v[i].fine < v[i+1].fine) swap(v,i,i+1);
        }
    }
}
void greedy(att *v,int n){
    int i = 0,diff = 0;
    ord_v2(v,n);
    att x = v[0];
    diff = v[0].fine - v[i].inizio;
    int dp[n]; // la riempio con le differenze degli intervalli
    printf("\n(%d,%d)",x.inizio,x.fine);
    for(i = 0;i<n;i++){
        dp[i] = v[i].fine - v[i].inizio;
    }
    // tolgo le intersezioni degli intervalli
    for(i = 1;i<n;i++){
        //suppongo di prendere x come primo intervallo
        if(v[i].inizio >= x.fine){
            // allora non ha intersezione
            diff += dp[i];
            printf("\n(%d,%d)",v[i].inizio,v[i].fine);
            x = v[i];
        }
    }
    printf("Diff: %d",diff);
}