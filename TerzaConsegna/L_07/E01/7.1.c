#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 101
#define dim_diag 5
#define file "elementi.txt"
typedef struct {
    char nome[MAXLEN];
    int tipo;
    int ingresso;
    int uscita;
    int precedenza;
    int finale;
    float valore;
    int diff;
}elemento;
elemento **fin;
int DD,DP;
int i_fin = 3;
int flag_acrob_1 = 0; // acrobatico avanti
int flag_acrob_2 = 0; // acrobatico indietro
int flag_sequenza = 0;
int somma_pro = 0;
void leggiFile(elemento ** vett2,int *n2);
int promising(int i,elemento *val,int pos,int k,elemento *sol);
int checkAcrob(elemento *sol,int k,int *acrob2,int *acrob1,int *sequenza);
void saveSolFin(elemento *sol,int k);
void wrapper(elemento *val,int n);
void displaySol(elemento *sol,int k,int somma);
int powerset(int pos,int n,int k,elemento *sol,elemento *val,int start,int cnt,int somma,int somma_pro);
int main(){
    int n;
    elemento *v;
    leggiFile(&v,&n);
    wrapper(v,n);   
}
void leggiFile(elemento ** vett2,int *n2){
    FILE *fp;
    int n,i;
    elemento *vett;
    if((fp = fopen(file,"r")) == NULL){
        printf("errore nella lettura del file");
        exit(1);
    }
    fscanf(fp,"%d",&n);
    vett = malloc(n*sizeof(elemento));
    while(i<n){
        fscanf(fp,"%s%d%d%d%d%d%f%d",vett[i].nome,&vett[i].tipo,&vett[i].ingresso,&vett[i].uscita,&vett[i].precedenza,&vett[i].finale,&vett[i].valore,&vett[i].diff);
        i++;
    }
    *n2 = n;
    *vett2 = vett;
    fclose(fp);
}
int promising(int i,elemento *val,int pos,int k,elemento *sol){
    if(pos == 0){
        if (val[i].precedenza == 0 && val[i].ingresso == 1) return 1;
    }
    else if(pos == k-1){
        if(val[i].finale == 1) return 1;
    }
    else if(val[i].precedenza == 1 && sol[pos-1].uscita == val[i].ingresso) return 1;
    return 0;
}
int checkAcrob(elemento *sol,int k,int *acrob2,int *acrob1,int *sequenza){
    int i,flag = 0;
    for(i = 0;i<k;i++){
        if(sol[i].tipo == 2){
            flag = 1;
            *acrob_2 = 1;
        }
        else if(sol[i].tipo == 1){
            flag = 1;
            *acrob_1 = 1;
        }
        if(i<k-1){
            if((sol[i].tipo == 1 || sol[i].tipo == 2) && (sol[i+1].tipo == 1 || sol[i+1].tipo == 1)) *sequenza = 1;
        }
    }
    if(flag == 0) return 0;
    else return 1;
}
void saveSolFin(elemento *sol,int k){
    int i = 0;
    for(i = 0;i<k;i++)
        fin[i_fin][i] = sol[i];
    i_fin--;
}
void wrapper(elemento *val,int n){
    int i,cnt;
    elemento *sol;
    sol = malloc(dim_diag*sizeof(elemento));
    fin = malloc(i_fin*sizeof(elemento *));
    printf("Inserisci DD:");
    scanf("%d",&DD);
    printf("Inserisci DP:");
    scanf("%d",&DP);
    for(i = 0;i<i_fin;i++){
        fin[i] = malloc(dim_diag*sizeof(elemento));
    }
    for(i = 0;i<dim_diag;i++){
        cnt = powerset(0,n,i,sol,val,0,0,0,0);
    }
    
    //sol fin e val allocati dinamicamente
}
void displaySol(elemento *sol,int k,int somma){
    int i = 0;
    for(i = 0;i<k;i++) printf("%s ",sol[i].nome);
    printf("Somma: %d",somma);
    printf("  A_1: %d  A_2:%d  Seq=%d",flag_acrob_1,flag_acrob_2,sequenza);
    printf("\n");
}
int powerset(int pos,int n,int k,elemento *sol,elemento *val,int start,int cnt,int somma,int somma_pro){
    int i,acrob_2,acrob_1,sequenza;
    if(pos>=k){ // devo cambiare condizione di terminazinoe?
        if(checkAcrob(sol,k,&acrob_2,&acrob_1,&sequenza)){//almeno un ele. acrob //saveSolFin(sol,k);
            //displaySol(sol,k,somma);
            accettab(pos,n,sol,val,0,0,somma,somma_pro,acrob_2,acrob_1,sequenza);
        }
        return somma;
    }
    for(i = start;i<n;i++){
        if(promising(i,val,pos,k,sol) && somma+val[i].diff<= DD){
            sol[pos] = val[i];
            somma += val[i].diff;
            somma += powerset(pos+1,n,k,sol,val,start,cnt,somma,somma_pro);
            somma -= val[i].diff;
        }
        start++;
    }
    return somma;
}
void accettab(int pos,int n,elemento*sol,elemento *val,int start,int cnt,int somma,int acrob_2,int acrob_1,int sequenza){
    int i = 0;
    //ho una diagonale valida, decido se aggiungerla alla soluzione
    if(somma+somma_pro < DP){
        if(flag_acrob_2 == 0)flag_acrob_2 = acrob_2; // devo controllare se nella mia soluzione corrente è presente qualche elemento che rispetta sto vincolo
        if(flag_acrob_1 == 0) flag_acrob_2 = acrob_1;
        if(flag_sequenza == 0) flag_sequenza = sequenza;
    }
    if(flag_sequenza == 1 && flag_acrob_2 == 1 && flag_acrob_1 == 1 && diag == 3){
        //ho un programma
    }
    

}