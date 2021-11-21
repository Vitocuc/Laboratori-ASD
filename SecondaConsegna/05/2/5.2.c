#include <stdlib.h>
#include <stdio.h>
typedef struct {
    char coloreT1;
    int valoreT1;
    char coloreT2;
    int valoreT2; 
}tile;
typedef struct{
    int t;
    int r;
}casella_b;
void leggiTiles(tile **tiles2);
void leggiScacchiera(casella_b ***board2);
int main(){
    tile *tiles;
    casella_b **board;
    leggiTiles(&tiles);
    leggiScacchiera(&board);
    // mi impone di avere un punteggio massimo
    //Posso fare pruning
}
void leggiTiles(tile **tiles2){
    FILE *fp;
    tile *tiles;
    int t,i = 0;
    if((fp = fopen("tiles.txt","r") == NULL)){
        printf("Errore nell'apertura del file ");
        exit(1);
    }
    fscanf(fp,"%d",&t);
    tiles = malloc(t*sizeof(tile));
    while(!feof(fp)){
        fscanf(fp,"%c%d%c%d",tiles[i].coloreT1,&tiles[i].valoreT1,tiles[i].coloreT2,&tiles[i].valoreT2);
        i++;
    }
    *tiles2 = tiles;
}
void leggiScacchiera(casella_b ***board2){
    int r,c,i,j;
    FILE *fp;
    casella_b **board;
    if((fp = fopen("board.txt","r") == NULL)){
        printf("Errore nell'apertura del file ");
        exit(1);
    }
    fscanf(fp,"%d %d",&r,&c);
    board = malloc(r*sizeof(casella_b));
    for(i = 0;i<c;i++) board[i] = malloc(c*sizeof(casella_b));
    while(!feof(fp)){
        for(j=0;j<c;j++) fscanf(fp,"%d/%d",&board[i][j].r,&board[i][j].t); // potrebbe non funzionare
        i++;
    }
    *board2 = board;
}