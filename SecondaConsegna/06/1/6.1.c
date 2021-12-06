#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int inizio;
    int fine;
}att;
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
    greedy(v,n);
    printf("\n");
    inv_greedy(v,n);
    
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
    diff = v[0].fine -v[i].inizio;
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