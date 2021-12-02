#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int PT_MAX = 0;
typedef struct {
    char coloreT1;
    int valoreT1;
    char coloreT2;
    int valoreT2;
    int codice; 
}tile;
typedef struct{
    int t;
    int r;
}casella_b;
void perm_sempl(int pos,casella_b **sol,int *mark,casella_b **fin,tile *val,int n,int r,int c);
void leggiTiles(tile **tiles2,int *n_tile);
void leggiScacchiera(casella_b ***board2,int *r1,int *c1);
void wrapper(tile *tiles,int n_tile,casella_b **board,int row,int col); // nel wrapper segno le soluzioni già prese per unificare il controllo
void check_pt(casella_b ** sol,casella_b **fin,tile * val,int r,int c);
void displaySol(casella_b **fin,tile *val,int r,int c);
int main(){
    tile *tiles;
    casella_b **board;
    int row,col,n_tile;
    leggiTiles(&tiles,&n_tile);
    leggiScacchiera(&board,&row,&col);
    wrapper(tiles,n_tile,board,row,col);
}
void wrapper(tile *tiles,int n_tile,casella_b **board,int row,int col){
    //dichiaro mark e fin
    int mark[n_tile],i,j;
    memset(mark,0,n_tile*sizeof(mark[0]));
    // Settare ad 1 gli elementi già inseriti nella board
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            if(board[i][j].t != -1) mark[board[i][j].t] = 1;
        }
    }
    // fin è allocato dinamicamente
    casella_b **fin;
    fin = malloc(row*sizeof(casella_b *));
    for(i = 0;i<row;i++) fin[i] = malloc(col*sizeof(casella_b));
    perm_sempl(0,board,mark,fin,tiles,n_tile,row,col);
    displaySol(fin,tiles,row,col);
    for (i = 0; i < row; i++) free(fin[i]);
    free(fin);
}
void displaySol(casella_b **fin,tile *val,int r,int c){
    int i,j;
    printf("Stampa");
    for(i = 0;i<r;i++){
        printf("\n");
        printf("------");
        for(j = 0;j<c;j++){
            if(fin[i][j].r == 0){
                // stampo normalmente T2 verticale
                printf("\t%c\t\n",val[fin[i][j].t].coloreT2);
                printf("%c\t\t%d\n",val[fin[i][j].t].coloreT1,val[fin[i][j].t].valoreT1);
                printf("\t%d\t\n",val[fin[i][j].t].valoreT2);
            }
            if(fin[i][j].r == 1){
                // stampo girato T2 orizzontale
                printf("\t%c\t\n",val[fin[i][j].t].coloreT1);
                printf("%c\t\t%d\n",val[fin[i][j].t].coloreT2,val[fin[i][j].t].valoreT2);
                printf("\t%d\t\n",val[fin[i][j].t].valoreT1);
            }
            
        }
        printf("Max somma:%d\n", PT_MAX);
    }

}
void check_pt(casella_b ** sol,casella_b **fin,tile * val,int r,int c){
    int i,j,pt_row = 0,pt_col = 0,pt_tot = 0,flag;
    // primo ciclo
    for(i = 0;i<r-1;i++){
        flag = 0;
        pt_row = 0;
        for(j = 0;j<c-1 && flag == 0;j++){
            if(sol[i][j].r == 0 && sol[i][j+1].r ==0) {
                if(val[sol[i][j].t].coloreT1 == val[sol[i][j+1].t].coloreT1) // controllo per righe
                    pt_row += val[sol[i][j].t].valoreT1;
                else flag = 1;
            }else if(sol[i][j].r == 0 && sol[i][j+1].r == 1){
                    if(val[sol[i][j].t].coloreT1 == val[sol[i][j+1].t].coloreT2) // controllo per righe
                    pt_row += val[sol[i][j].t].valoreT1;
                else flag = 1;
            }else if(sol[i][j].r == 1 && sol[i][j+1].r ==0){
                if(val[sol[i][j].t].coloreT2 == val[sol[i][j+1].t].coloreT1) // controllo per righe
                        pt_row += val[sol[i][j].t].valoreT2;
                else flag = 1; 
            }else if(sol[i][j].r == 1 && sol[i][j+1].r ==1){
                if(val[sol[i][j].t].coloreT2 == val[sol[i][j+1].t].coloreT2) // controllo per righe
                        pt_row += val[sol[i][j].t].valoreT2;
                else flag = 1;
            }
        }
        
        if(flag == 0) pt_tot += pt_row;
    }
    //secondo ciclo
    for(i = 0;i<r-1;i++){
        flag = 0;
        pt_col = 0;
        for(j = 0;j<c-1 && flag == 0;j++){
            if(sol[i][j].r == 0 && sol[i+1][j].r == 0) {
                 if(val[sol[i][j].t].coloreT2 == val[sol[i+1][j].t].coloreT2) // controllo per righe
                    pt_col += val[sol[i][j].t].valoreT2;
                else flag = 1;
            }else if(sol[i][j].r == 0 && sol[i+1][j].r == 1){   
                if(val[sol[i][j].t].coloreT2 == val[sol[i+1][j].t].coloreT1) // controllo per righe
                    pt_col += val[sol[i][j].t].valoreT2;
                else flag = 1;
            }else if(sol[i][j].r == 1 && sol[i+1][j].r == 0){
                if(val[sol[i][j].t].coloreT1 == val[sol[i+1][j].t].coloreT2) // controllo per righe
                    pt_col += val[sol[i][j].t].valoreT1;
                else flag = 1;
            }else if(sol[i][j].r == 1 && sol[i+1][j].r == 1){
                if(val[sol[i][j].t].coloreT1 == val[sol[i+1][j].t].coloreT1) // controllo per righe
                    pt_col += val[sol[i][j].t].valoreT1;
                else flag = 1;
            }        
        }
        if(flag == 0) pt_tot += pt_col;
    }
    if(pt_tot > PT_MAX) {
        PT_MAX = pt_tot;
        //copio la soluzione
        for(i = 0;i<r;i++)
            for(j = 0;j<c;j++)
                fin[i][j] = sol[i][j];
    }
    
}
void perm_sempl(int pos,casella_b **sol,int *mark,casella_b **fin,tile *val,int n,int r,int c){
    int i = 0,flag, row, col;
    //condizione di terminazione
    if(pos >= n){
        check_pt(sol,fin,val,r,c);

        return;        
    }
    row = pos/c;
    col = pos % c;
    if (sol[row][col].t != -1)
    {
        perm_sempl(pos+1, sol, mark, fin, val, n, r, c);
        return;
    }
    //aggiorno la riga quando:
    //ciclo per prendere le soluzioni
    for(i = 0;i<n;i++){
        if(mark[i] == 0){
            mark[i] = 1; // marco l'elemento
            sol[row][col].t = val[i].codice;
            sol[row][col].r = 0; // rotazione normale con T2 verticale
            perm_sempl(pos+1,sol,mark,fin,val,n,r,c);// ricorrop sapendo di aver preso quell'elemento in quella poszione
            //sol[row][col].t = val[pos].codice;
            sol[row][col].r = 1; // ricorro un'ALTRA VOLTA sapendo di aver cambiato rotazione in questo modo ripeto le iterazioni anche per tutte le altre rotazioni
            perm_sempl(pos+1,sol,mark,fin,val,n,r,c); // t2 orizzonatale*/
            mark[i] = 0;
            sol[row][col].r = -1;
            sol[row][col].t = -1;
        }
    }
}
void leggiTiles(tile **tiles2,int *n_tile){
    
    FILE *fp;
    tile *tiles;
    int t,i = 0;
    if((fp = fopen("tiles.txt","r")) == NULL){
        printf("Errore nell'apertura del file ");
        exit(1);
    }
    fscanf(fp,"%d",&t);
    tiles = malloc(t*sizeof(tile));
    while(i<t){
        fscanf(fp," %c%d %c%d",&tiles[i].coloreT1,&tiles[i].valoreT1,&tiles[i].coloreT2,&tiles[i].valoreT2);
        tiles[i].codice = i;
        i++;
    }
    *tiles2 = tiles;
    *n_tile = t;
    fclose(fp);
}
void leggiScacchiera(casella_b ***board2,int *r1,int *c1){
    int r,c,i= 0,j=0;
    FILE *fp;
    casella_b **board;
    fp = fopen("board.txt","r");
    if(fp == NULL){
        printf("Errore nell'apertura del file ");
        exit(1);
    }
    fscanf(fp,"%d %d",&r,&c);
    board = malloc(r*sizeof(casella_b*));
    for(i = 0;i<r;i++) board[i] = malloc(c*sizeof(casella_b));
    for(i = 0;i<r;i++){
        for(j = 0;j<c;j++) {
            fscanf(fp,"%d/%d",&board[i][j].t,&board[i][j].r);
        }
    }
    *board2 = board;
    *r1 = r;
    *c1 = c;
    fclose(fp);
}