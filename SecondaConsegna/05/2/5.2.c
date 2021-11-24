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
void leggiTiles(tile **tiles2);
void leggiScacchiera(casella_b ***board2);
int main(){
    tile *tiles;
    casella_b **board;
    leggiTiles(&tiles);
    leggiScacchiera(&board);
    // mi impone di avere un punteggio massimo
    //problema di ottimizzazione
    // posso fare pruning quando la cella non è vuota
}
void leggiTiles(tile **tiles2){
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
        fscanf(fp,"%c%d%c%d",tiles[i].coloreT1,&tiles[i].valoreT1,tiles[i].coloreT2,&tiles[i].valoreT2);
        tiles[i].codice = i;
        printf("%d",tiles[i].codice);
        i++;
    }
    *tiles2 = tiles;
    fclose(fp);
}
void leggiScacchiera(casella_b ***board2){
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
    fclose(fp);
}
//inizializzo sol con le tail già inserite

void wrapper(int r,int c,casella_b *sol,tile *val,casella_b ** board){
    int i = 0,n = r*c;
    for(i = 0;i<n;i++){
        if(sol[i].t != -1 && sol[i].r != -1) sol[i].t = val[i].codice;
    }
    permutazioni_semplice(0,sol,val,board,n,r,c,0,0);

}
// ogni tiles ha il codice sia per permettere di trovarla tramite indice sia oer permeyyerle di essere salvata come indice nella soluziion
int permutazioni_semplice(int pos,int riga,casella_b **sol, tile *val,int *mark, int n,int r,int c,int cnt,int sum,casella_b **fin) { 
    int i,j;
    if ((riga*c) >= n) {
        check();//posso sapere alla fine solamente dopo aver visto tutte le caselle
        displaySol();// sol non contiene solamente 0 e 1 ma l'indice di ogni tiles che andrà ricercato per essere stampato
        return cnt+1;
    }
    if(pos == c){ 
        pos = 0; 
        riga++;
    }
    for (i=0; i<n; i++){
        if (mark[i] == 0){ // questa tessera non è stata inserita
            mark[i] = 1; // questa tessera è stat gia presa
            sol[riga][pos].t = val[indice].codice;// inserisco nella mia soluzione la tessera che prendo
            sol[riga][pos].r = 0;// inserisco la rotazione che mi è detta dalla board
            // valuto la somma in teoria devo vedere se è accettabili ovvero se hanno lo stesso colore
            //check per colonne(T2 è verticale)
            if(riga == 0) sum += val[sol[riga][pos].t].valoreT2; // inizializzo alla prima cella
            else if(val[sol[riga][pos].t].coloreT2 == val[sol[riga-1][pos].t].coloreT2) // posso sommare
                sum+=val[sol[riga][pos].t].valoreT2;
            //check per righe(T1 è orizzontale)
            if(pos == 0) sum+ = val[sol[riga][pos].t].valoreT1; // inizializzo alla prima cella 
            if(val[sol[riga][pos].t].coloreT1 == val[sol[riga][pos-1].t].coloreT1) // posso sommare
                sum += val[sol[riga][pos].t].valoreT1;               
            cnt = permutazioni_semplice(pos+1,riga,sol,val,mark,n,r,c,cnt,sum,fin); 
            sol[riga][pos].r = 1; // cambio rotazione
            // invertire le condizioni di controllo

            
            // valuto la somma in teoria devo vedere se è accettabili ovvero se hanno lo stesso colore
            cnt = permutazioni_semplice(pos+1,riga,sol,val,mark,n,r,c,cnt,sum,fin); 
            mark[i] = 0; // backtrack della soluzioni
        }
    }
    return cnt;
    
}