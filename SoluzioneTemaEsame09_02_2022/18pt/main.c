#include <stdio.h>
#include <stdlib.h>
void leggi_griglia(int ***M, int *nr,int *nc);
void leggi_proposta(int ***M2,int nr,int nc);
void saveSolution(int **sol,int nr,int nc,int **bestsol);
void trova_cammS(int **griglia,int dir,int i,int j,int **sol,int **bestsol,int *passi,int nr,int nc,int celle_libere,int *cambi);
int check_cammino(int **griglia,int nr,int nc,int *n_passi,int **proposte,int *n_cambi,int celle_libere);
int check_2(int **sol,int *i,int *j,int **griglia,int nr,int nc);
void stampaSolution(int **sol,int nr,int nc);
int main(){
    int **griglia,**proposte,nc,nr,**sol,**bestsol;
    int i,j,celle_libere = 0;
    int n_cambi = 0,dir = 5,n_passi = 0; // dir numero di pass;i possibili
    leggi_griglia(&griglia,&nr,&nc);
    for(i = 0;i<nr;i++){
        for(j = 0;j<nc;j++){
            printf("%d ",griglia[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    leggi_proposta(&proposte,nr,nc);
    for(i = 0;i<nr;i++){
        for(j = 0;j<nc;j++){
            printf("%d ",proposte[i][j]);
        }
        printf("\n");
    }
    //calcolo del numero di celle libere in griglia
    for(i = 0;i<nr;i++){
        for(j = 0;j<nc;j++){
            if(griglia[i][j] == 0) celle_libere ++;
        }
    }
    if(check_cammino(griglia,nr,nc,&n_passi,proposte,&n_cambi,celle_libere) == 1){
        printf("Il cammino e' valido con numero di passi: %d \n",n_passi);
        printf("Il cammino ha %d cambi \n",n_cambi);
    }
    n_cambi = 0;
    n_passi = 0;
    sol = malloc(nr*sizeof(int *));
    bestsol = malloc(nr*sizeof(int *));
    for(i = 0;i<nr;i++){
        sol[i] = malloc(nc*sizeof(int));
        bestsol[i] = malloc(nc*sizeof(int)); 
    }
    for(i = 0;i<nr;i++){
        for(j = 0;j<nc;j++){
            sol[i][j] = -1;        
        }
    }
    n_cambi = 0;
    trova_cammS(griglia,dir,0,0,sol,bestsol,&n_passi,nr,nc,celle_libere,&n_cambi);
    printf("Soluzione ottima con numero di cambi: %d \n",n_cambi);
    stampaSolution(bestsol,nr,nc);
    for(i = 0;i<nr;i++){
        free(bestsol[i]);
        free(sol[i]);
        free(griglia[i]);
        free(proposte[i]);
    }
    free(bestsol);
    free(sol);
    free(griglia);
    free(proposte);

}
void leggi_griglia(int ***M, int *nr,int *nc){
    int nr2,nc2,**mat,i,j,val;
    FILE *fp;
    if((fp = fopen("griglia.txt","r")) == NULL){
        printf("errore nell'apertura del file");
        exit(1);
    }
    fscanf(fp,"%d %d",&nr2,&nc2);
    // allocazione della matrice
    mat = malloc(nr2*sizeof(int*));
    for( i = 0 ; i< nr2;i++){
        mat[i] = malloc(nc2*sizeof(int));
    }
    i = 0;
    j = 0;
    while(!feof(fp)){
        fscanf(fp,"%d",&mat[i][j]);
        if(j == nc2-1) {
            i++;
            j = 0;
        }else j++;
    }
    *nr = nr2;
    *nc = nc2;
    *M = mat;
    fclose(fp);
}
void leggi_proposta(int ***M2,int nr,int nc){
    int **mat,i,j,dir = 0;
    mat = malloc(nr*sizeof(int*));
    FILE *fp;
    if((fp = fopen("proposte.txt","r")) == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    for(i = 0;i<nr;i++){
        mat[i] = malloc(nc*sizeof(int));
    }
    while (!feof(fp)){
        fscanf(fp,"%d %d %d",&i,&j,&dir);
        mat[i][j] = dir;
    }
    *M2 = mat;
    fclose(fp);
}
int check_cammino(int **griglia,int nr,int nc,int *n_passi,int **proposte,int *n_cambi,int celle_libere){
    int i = 0,j = 0,flag = 1,dir = 0,passi = 1,cambi = 0;
    while(flag == 1){
        dir = proposte[i][j];
        if(dir == 1  && i+1<nr) i++;
        else if(dir == 2 && j+1<nc) j++;
        else if(dir == 3 && j-1>= 0) j--;
        else if(dir == 4 && i-1>= 0) i--;
        if(proposte[i][j] == 0) flag = 0;
        else if(proposte[i][j] != dir) cambi++;
        passi++;
    }
    if(passi == celle_libere){
        *n_passi = passi;
        *n_cambi = cambi;
        return 1;
    }
    return 0;
}
void trova_cammS(int **griglia,int dir,int i,int j,int **sol,int **bestsol,int *passi,int nr,int nc,int celle_libere,int *cambi){
    int n_passi = 0,k,n_cambi = 0,temp_i,temp_j,h;
    if(sol[i][j] == 0){
        if(check_cammino(griglia,nr,nc,&n_passi,sol,&n_cambi,celle_libere) == 1){
            if(*cambi == 0){ // prima soluzione trovata
                (*cambi) = n_cambi;
                saveSolution(sol,nr,nc,bestsol);
            }
            if(n_cambi<(*cambi)){
                (*cambi) = n_cambi;
                saveSolution(sol,nr,nc,bestsol);
            }
        }
        return;
    }
    for(k = 0;k<dir;k++){
        if(griglia[i][j] == 0){
            griglia[i][j] = 1;
            sol[i][j] = k;
            temp_i = i;
            temp_j = j;
            if(check_2(sol,&i,&j,griglia,nr,nc) == 1){
                trova_cammS(griglia,dir,i,j,sol,bestsol,passi,nr,nc,celle_libere,cambi);
                //backtrack degli indici
                i = temp_i;
                j = temp_j;
            }
            griglia[i][j] = 0;
        }
    }

}
void saveSolution(int **sol,int nr,int nc,int **bestsol){
    int i,j;
    for(i = 0;i<nr;i++){
        for(j = 0;j<nc;j++){
            bestsol[i][j] = sol[i][j];
        }
    }
}
int check_2(int **sol,int *i,int *j,int **griglia,int nr,int nc){
    if(sol[*i][*j] == 1){
        if((*i)+1<nr ) (*i)++;
        else return 0;
    }else{
        if(sol[*i][*j] == 2 ){
            if((*j)+1<nc ) (*j)++;
            else return 0;
        }else{
            if(sol[*i][*j] == 3 ){
                if((*j)-1>=0) (*j)--;
                else return 0;
            }else{
                if(sol[*i][*j] == 4 ){
                    if((*i)-1>=0 ) (*i)--;
                    else return 0;
                }
            }
        }
    }
    return 1;
}
void stampaSolution(int **sol,int nr,int nc){
    int i,j;
    for(i = 0;i<nr;i++){
        for( j = 0;j<nc;j++){
            printf("%3.d ",sol[i][j]);
        }
        printf("\n");
    }

}