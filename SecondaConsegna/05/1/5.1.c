#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int inizio;
    int fine;
}att;
int diff_curr = 0;
void leggiFile(att **v,int *n,char *s);
void attSel(int n, att *v);
void check(int *sol,int *fin,att *val,int k);
void displaySol(int *sol,att *val,int k);
void powerset(int pos,att *val,int *sol,int k,int *fin);
int promising(att* val,int pos,int *sol);
int main(){
    int n;
    att *v;
    printf("File 1");
    leggiFile(&v,&n,"att.txt");
    attSel(n,v);
    free(v);
}
void displaySol(int *sol,att *val,int k){
        int j = 0;
        printf("{"); 
        for (j=0; j<k; j++) if (sol[j]!=0) printf("%d,%d ", val[j].inizio,val[j].fine); 
        printf("}\n");
}
void check(int *sol,int *fin,att *val,int k){
    int j,diff = 0;
    //calcolo della differenza
    for (j=0; j<k; j++) if (sol[j]==1) {
        diff += val[j].fine - val[j].inizio;
    };
    printf("La differenza e' :%d",diff);
    if(diff>diff_curr){
        printf("Per ora la soluzione migliore e':");
        diff_curr = diff;
        //aggiorno la soluzione
        for (j=0; j<k; j++) fin[j] = sol[j]; /// dovevo copiare
    }
}
void powerset(int pos,att *val,int *sol,int k,int *fin){
    int i = 0;
    if(pos>= k){
        // condizione di terminazione
        check(sol,fin,val,k);
        displaySol(sol,val,k);
        return;
    }
    if(!promising(val,pos,sol)){ // se l'elemento non è promettente lo las
        sol[pos] = 0;
        powerset(pos+1,val,sol,k,fin);
        return;
    }
    sol[pos] = 1;
    powerset(pos+1,val,sol,k,fin);
    sol[pos] = 0;
    powerset(pos+1,val,sol,k,fin);
}
int promising(att* val,int pos,int *sol){
    int i ;
    for(i = 0;i<pos;i++){
        if(sol[i] == 1) if(val[i].inizio < val[pos].fine && val[pos].inizio < val[i].fine)// se almeno un valore non va bene allora lo devo escludere
                    return 0 ;
    } 
    return 1;

}
void attSel(int n, att *v){
    int sol[n];
    int i;
    int fin[n]; // devo ricordarmi di renderlo tutto zero prima
    memset(fin,0,n*sizeof(fin[0]));
    powerset(0,v,sol,n,fin);
    printf("La soluzione migliore con differenza %d e':",diff_curr);
    displaySol(fin,v,n);
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