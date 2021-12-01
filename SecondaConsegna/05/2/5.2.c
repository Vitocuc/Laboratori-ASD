#include <stdlib.h>
#include <stdio.h>
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
void perm_sempl(int pos, int row,int col,casella_b **sol,int *mark,casella_b **fin,tile *val,int n,int r,int c);
void leggiTiles(tile **tiles2,int *n_tile);
void leggiScacchiera(casella_b ***board2,int *r1,int *c1);
void wrapper(tile *tiles,int n_tile,casella_b **board,int row,int col); // nel wrapper segno le soluzioni già prese per unificare il controllo
int check_pt(casella_b ** sol,casella_b **fin,tile * val,int r,int c);
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
    int mark[n_tile],i;
    // fin è allocato dinamicamente
    casella_b **fin;
    fin = malloc(row*sizeof(casella_b *));
    for(i = 0;i<row;i++) fin[i] = malloc(col*sizeof(casella_b));
    perm_sempl(0,0,0,board,mark,fin,tiles,n_tile,row,col);
}
void displaySol(casella_b **fin,tile *val,int r,int c){
    int i,j;
    for(i = 0;i<r;i++){
        for(j = 0;j<c;j++){
            if(fin[i][j].r == 0){
                // stampo normalmente T2 verticale
                printf("\t%c\t",val[fin[i][j].t].coloreT2);
                printf("%c\t%d",val[fin[i][j].t].coloreT1,val[fin[i][j].t].valoreT1);
                printf("\t%d\t",val[fin[i][j].t].valoreT2);
            }
            if(fin[i][j].r == 1){
                // stampo girato T2 orizzontale
                printf("\t%c\t",val[fin[i][j].t].coloreT1);
                printf("%c\t%d",val[fin[i][j].t].coloreT2,val[fin[i][j].t].valoreT2);
                printf("\t%d\t",val[fin[i][j].t].valoreT1);
            }
            
        }
    }

}
int check_pt(casella_b ** sol,casella_b **fin,tile * val,int r,int c){
    int i,j,pt_row = 0,pt_col = 0,pt_tot;
    for(i = 0;i<r;i++){
        for(j = 0;j<c;j++){
            if(sol[i][j].r == 0) { // non ruotata
                if(j+1 == c){
                    if(val[sol[i][j].t].coloreT1 == val[sol[i][j-1].t].coloreT1) // controllo per righe
                        pt_row += val[sol[i][j].t].valoreT1;
                }else if(val[sol[i][j].t].coloreT1 == val[sol[i][j+1].t].coloreT1) // controllo per righe
                        pt_row += val[sol[i][j].t].valoreT1;
                if(i+1 == r){
                    if(val[sol[i][j].t].coloreT2 == val[sol[i-1][j].t].coloreT2) // coontrollo per colonne
                        pt_col += val[sol[i+1][j].t].valoreT2;
                }else if(val[sol[i][j].t].coloreT2 == val[sol[i+1][j].t].coloreT2) // coontrollo per colonne
                    pt_col += val[sol[i+1][j].t].valoreT2;
            }else{ // ruotata
                if(i+1 == r){
                    if(val[sol[i][j].t].coloreT1 == val[sol[i-1][j].t].coloreT1) // coontrollo per colonne
                        pt_col += val[sol[i+1][j].t].valoreT1;
                }else if(val[sol[i][j].t].coloreT1 == val[sol[i+1][j].t].coloreT1) // coontrollo per colonne
                    pt_col += val[sol[i+1][j].t].valoreT1;
                if(j+1 == c){
                    if(val[sol[i][j].t].coloreT2 == val[sol[i][j-1].t].coloreT2) // controllo per righe
                        pt_row += val[sol[i][j].t].valoreT2;
                }else if(val[sol[i][j].t].coloreT2 == val[sol[i][j+1].t].coloreT2) // controllo per righe
                        pt_row += val[sol[i][j].t].valoreT2;
            } 
        }
    }
    pt_tot = pt_row + pt_col;
    if(pt_tot > PT_MAX) {
        PT_MAX = pt_tot;
        //copio la soluzione
        for(i = 0;i<r;i++)
            for(j = 0;j<c;j++)
                fin[i][j] = sol[i][j];

        return 1;
    }
    return 0;
}
void perm_sempl(int pos, int row,int col,casella_b **sol,int *mark,casella_b **fin,tile *val,int n,int r,int c){
    int i = 0,flag;
    //condizione di terminazione
    if(row == r-1 && col == c-1){
        flag = check_pt(sol,fin,val,r,c);
        if (flag) displaySol(fin,val,r,c);
    }
    // aggiorno la riga quando:
    if(col == c-1){//aggiorno la riga e resetto la colonna
        row++;
        col = 0;
    }
    //ciclo per prendere le soluzioni
    for(i = 0;i<n;i++){
        if(mark[i] == 0){
            mark[i] = 1; // marco l'elemento
            sol[row][col].t = val[pos].codice;
            sol[row][col].r = 0; // rotazione normale con T2 verticale
            perm_sempl(pos+1,row,col+1,sol,mark,fin,val,n,r,c);// ricorrop sapendo di aver preso quell'elemento in quella poszione
            sol[row][col].t = val[pos].codice;
            sol[row][col].r = 1; // ricorro un'ALTRA VOLTA sapendo di aver cambiato rotazione in questo modo ripeto le iterazioni anche per tutte le altre rotazioni
            perm_sempl(pos+1,row,col+1,sol,mark,fin,val,n,r,c); // t2 orizzonatale
            mark[i] = 0;
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
    printf("%d",t);
    while(!feof(fp)){
        fscanf(fp," %c%d %c%d",tiles[i].coloreT1,&tiles[i].valoreT1,tiles[i].coloreT2,&tiles[i].valoreT2);
        tiles[i].codice = i;
        printf("%d",tiles[i].codice);
        i++;
    }
    *tiles2 = tiles;
    *n_tile = t;
    fclose(fp);
}
void leggiScacchiera(casella_b ***board2,int *r1,int *c1){
    int r,c,i= 0,j;
    FILE *fp;
    casella_b **board;
    if((fp = fopen("board.txt","r")) == NULL){
        printf("Errore nell'apertura del file ");
        exit(1);
    }
    fscanf(fp,"%d %d",&r,&c);
    board = malloc(r*sizeof(casella_b));
    for(i = 0;i<c;i++) board[i] = malloc(c*sizeof(casella_b));
    while(!feof(fp)){
        for(j=0;j<c;j++) {fscanf(fp,"%d/%d",&board[i][j].r,&board[i][j].t);printf("%d/%d",board[i][j].r,board[i][j].t);} // potrebbe non funzionare
        i++;
    }
    *board2 = board;
    *r1 = r;
    *c1 = c;
    fclose(fp);
}