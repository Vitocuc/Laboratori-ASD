#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    int inizio;
    int fine;
}att;
int diff_curr = 0;
// mi sembra che l'algortimo del power set con le disposizioni ripetute non siano buono quabdo dobbiamo utilizzare queste differenze
int powerset(int pos,att *val,int *sol,int k,int cnt,int diff,int *fin);
// è un problema di ottimizzazione
void leggiFile(att **v,int *n,char *s);
void attSel(int n, att *v);
// due attivita sono incompatibili se e solo se si intersecano e sovrappongono quindi semplice
// utilizzo i powerset perchè sono sottoinsiemki 
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
void check(int *sol,int *fin,int k,int diff){
    int j;
    if(diff>diff_curr){
        printf("Per ora è la soluzione migliore:");
        diff_curr = diff;
        //aggiorno la soluzione
        for (j=0; j<k; j++) if (sol[j]!=0) fin[j] = 1;
    }
}
int powerset(int pos,att *val,int *sol,int k,int cnt,int diff,int *fin) { 
    int j;
    if (pos >= k){
        check(sol,fin,k,diff);
        displaySol(sol,val,k);
        return cnt+1; // non devo pensare di vucare la ricorsione
    }
    // devo controllare che con lo spazio di soluzioni successivo la data e fine non siano comprese
    sol[pos] = 0;
    cnt = powerset(pos+1, val, sol, k, cnt,diff,fin);
    //quando posso avere un controllo sulla soluzione. Se non ho inserito nessun elemento nella soluzioni allora posso inserirlo senza controllo
    //se ne ho inserito almeno uno devo controllare che il precedente a wuesto punto, rispetti i criteri di 
    if(sol[pos+1] != 0 && pos+1<k){if(val[pos].inizio>val[pos+1].inizio && val[pos].fine<val[pos+1].fine){
        sol[pos] = 1;
        diff+=val[pos].fine - val[pos].inizio;
        cnt = powerset(pos+1, val, sol, k, cnt,diff,fin);
        }
    }else{
        sol[pos] = 1;
        diff+=val[pos].fine - val[pos].inizio;
        cnt = powerset(pos+1, val, sol, k, cnt,diff,fin);

    }
return cnt;
}
// in un insieme ho piu sottoinsiemi
void attSel(int n, att *v){
    int sol[n];
    int i;
    int fin[n]; // devo ricordarmi di renderlo tutto zero prima
    memset(fin,0,n*sizeof(fin[0]));
    int count = powerset(0,v,sol,n,0,0,fin);
    printf("La soluzione migliore con differenza %d e':",diff_curr);
    displaySol(fin,v,n);
    printf("Il numero di sottoinsiemi e' %d",count);
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