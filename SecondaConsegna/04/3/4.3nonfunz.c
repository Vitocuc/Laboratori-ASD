#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// mi salta delle chiamate ricorsive, devo ricontrollare l'algoritmo
static int **n_pietre;
static int lung_max = 0;
int disp_ripetute(int pos,int n,int k,char *sol,int *mark,int z,int r,int t,int s,int lung,int i,int flag);
void leggiFile(char *file,int *n,int **z1,int **r1,int **t1,int **s1);
void wrapper(int n_collane,int *z,int *r,int *t,int *s,int n);
void saveSolution(char *sol,int lung,int *mark,int j);
int main(int argc,char **argv){
    int n,*z,*r,*t,*s;
    if(argc<2) return 1;
    leggiFile(argv[1],&n,&z,&r,&t,&s);
    wrapper(n,z,r,t,s,4);
    return 0;
}
void leggiFile(char *file,int *n,int **z1,int **r1,int **t1,int **s1){
    FILE *fp;
    int n_collane = 0,i = 0;
    if((fp = fopen(file,"r")) == NULL){
        printf("Errore nella lettura del file");
        exit(1);
    }
    fscanf(fp,"%d",&n_collane);
    // alloco dinamicamente
    int *z,*t,*r,*s;
    z = malloc(n_collane * sizeof(int));
    r = malloc(n_collane * sizeof(int));
    t = malloc(n_collane * sizeof(int));
    s = malloc(n_collane * sizeof(int));
    while(i<n_collane){
        fscanf(fp,"%d %d %d %d",&z[i],&r[i],&t[i],&s[i]); // problema con t => SEPARARE SEMORE GLI SPAZI!!!!S
        i++;
    }
    // aggiornamento delle variabili
    *n = n_collane;
    *z1 = z;
    *r1 = r;
    *t1 = t;
    *s1 = s;
}
void wrapper(int n_collane,int *z,int *r,int *t,int *s,int n){
    int k = 0,i = 0,lung = 0,*mark,flag;
    char sol[k];
    mark = malloc(n_collane*sizeof(int)); 
    n_pietre = calloc(n_collane,sizeof(int*));
    for(i=0;i<n_collane;i++) n_pietre[i] = calloc(4,sizeof(int));
    for(i = 0;i<n_collane;i++){
        k = z[i]+r[i]+t[i]+s[i];
        printf("TEST: %d \n",i+1);
        lung_max = 0;
        flag = disp_ripetute(0,n,k,sol,mark,z[i],r[i],t[i],s[i],lung,i,0); // devo salvare il numero di pietre
        printf("La collana di lunghezza massima : %d \n Zaffiri:%d Rubini:%d Topazi:%d Smeraldo:%d",mark[i],n_pietre[i][0],n_pietre[i][1],n_pietre[i][2],n_pietre[i][3]);
        printf("\n");
        //azzerro la soluzione
        //memset(sol,0,k*sizeof(char));
    }
    //ricerca su mark che contiene le lunghezze e ricerca attraverso la dicotomica trovare la lunghezza piu lunga e stamparla
    //deallocazione
    free(mark);
}
void saveSolution(char *sol,int lung,int *mark,int j){
    int i = 0;
    mark[j] = lung;
    //azzero n_pietre
    n_pietre[j][0] = n_pietre[j][1] = n_pietre[j][2] = n_pietre[j][3] = 0;
    for(i = 0;i<lung;i++){
        if(sol[i] == 'z')  n_pietre[j][0]+=1;
        else if(sol[i] == 'r') n_pietre[j][1]+=1;
        else if(sol[i] == 't') n_pietre[j][2]+=1;
        else n_pietre[j][3]+=1;
    }
}
int disp_ripetute(int pos,int n,int k,char *sol,int *mark,int z,int r,int t,int s,int lung,int i,int flag){
    //condizione di terminazione // oppure non posso piu inserire una pietre
    if(pos >=1) {
            //salvo la soluzione
            if(lung>lung_max) lung_max = lung;
            saveSolution(sol,lung,mark,i);
            if(lung == k)return 1;
            return 0;
    }
        if(pos == 0){
            sol[pos] = 'z';
            flag = disp_ripetute(pos+1,n,k,sol,mark,z-1,r,t,s,lung+1,i,flag);
            sol[pos] = 'r';
            flag = disp_ripetute(pos+1,n,k,sol,mark,z,r-1,t,s,lung+1,i,flag);
            sol[pos] = 't';
            flag = disp_ripetute(pos+1,n,k,sol,mark,z,r,t-1,s,lung+1,i,flag);
            sol[pos] = 's';
            flag = disp_ripetute(pos+1,n,k,sol,mark,z,r,t,s-1,lung+1,i,flag);
        }
        if(pos>0){
            switch(sol[pos-1]){ // devo inserire la cella precedente
            case 'z':
            case 't':
                // ricorro prendendo uno zaffiro o un rubino
                if(z>0){
                    sol[pos] = 'r';
                    flag = disp_ripetute(pos+1,n,k,sol,mark,z-1,r,t,s,lung+1,i,flag);
                    // backtrack
                }
                if(r>0){
                    sol[pos] = 'r';
                    flag = disp_ripetute(pos+1,n,k,sol,mark,z,r-1,t,s,lung+1,i,flag);
                }
            case 's':
            case 'r':
                //ricorro prendendo uno smerlado o un topazio
                if(t>0){
                    sol[pos] = 't';
                    flag = disp_ripetute(pos+1,n,k,sol,mark,z,r,t-1,s,lung+1,i,flag);
                }
                if(s>0){
                    sol[pos] = 's';
                    flag = disp_ripetute(pos+1,n,k,sol,mark,z,r,t,s-1,lung+1,i,flag);
                }
                //backrack    
            }
    }
    return flag; 
}