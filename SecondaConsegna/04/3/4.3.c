#include <stdio.h>
#include <stdlib.h>
void disp_ripetute(int pos,int n,int k,char *sol,int *mark,int z,int r,int t,int s,int lung);
void leggiFile(char *file,int *n,int **z1,int **r1,int **t1,int **s1);
void displaySol(char *sol,int l);
void wrapper(int n_collane,int *z,int *r,int *t,int *s,int n);
int main(){
    int n,*z,*r,*t,*s;
    leggiFile("very_very_easy_test_set.txt",&n,&z,&r,&t,&s);
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
    int k = 0,i = 0,lung = 0,*mark;
    char sol[k];
    mark = malloc(n*sizeof(int)); 
    //allocazione dinamic
    for(i = 0;i<n_collane;i++){
        k = z[i]+r[i]+t[i]+s[i];
        printf("Collana n: %d \n",i);
        disp_ripetute(0,n,k,sol,mark,z[i],r[i],t[i],s[i],lung);
    }
    //dealloco
    /*
    for(i = 0;i<n;i++){
        free(mark[i]);
    }
    free(mark);
     for(i = 0;i<k;i++){
        free(sol[i]);
    }
    free(sol); 
    */ 
}
void displaySol(char *sol,int l){
    int i = 0;
    printf("Lung: %d",l);
    for(i = 0;i<l;i++) printf(" %c ",sol[i]);
    printf("\n");
}
void disp_ripetute(int pos,int n,int k,char *sol,int *mark,int z,int r,int t,int s,int lung){
    int i = 0;
    //condizione di terminazione
    if(pos>=1){ // oppure non posso piu inserire una pietra
        //check();
        displaySol(sol,lung);
    }
    if(pos == 0){
        sol[pos] = 'z';
        disp_ripetute(pos+1,n,k,sol,mark,z-1,r,t,s,lung+1);
        z++;
        sol[pos] = 'r';
        disp_ripetute(pos+1,n,k,sol,mark,z,r-1,t,s,lung+1);
        r++;
        sol[pos] = 't';
        disp_ripetute(pos+1,n,k,sol,mark,z,r,t-1,s,lung+1);
        t++;
        sol[pos] = 's';
        disp_ripetute(pos+1,n,k,sol,mark,z,r,t,s-1,lung+1);
        s++;
    }
    if(pos>0){
        switch(sol[pos-1]){ // devo inserire la cella precedente
        case 'z':
        case 't':
            // ricorro prendendo uno zaffiro o un rubino
            if(z>0){
                sol[pos] = 'z';
                disp_ripetute(pos+1,n,k,sol,mark,z-1,r,t,s,lung+1);
                // backtrack
                z++;
            }
            if(r>0){
                sol[pos] = 'r';
                disp_ripetute(pos+1,n,k,sol,mark,z,r-1,t,s,lung+1);
                r++;
            }
        case 's':
        case 'r':
            //ricorro prendendo uno smerlado o un topazio
            if(t>0){
                sol[pos] = 't';
                disp_ripetute(pos+1,n,k,sol,mark,z,r,t-1,s,lung+1);
                t++;
            }
            if(s>0){
                sol[pos] = 's';
                disp_ripetute(pos+1,n,k,sol,mark,z,r,t,s-1,lung+1);
                s++;
            }
            //backrack
            
        }
    }
    /*
    for(i = 0;i<n;i++){
        mark[i] = 1;
        sol[pos] = val[i];
        disp_ripetute(pos+1,n,k,val,sol,mark);
        //backtrack
        mark[i] = 0;
    }*/
}