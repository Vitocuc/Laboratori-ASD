#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
//impostazione algoritmo ricorsivo
int main(int argc,char **argv){
    if(argc>2) return 1;
    Graph G;
    Edge *vett;
    FILE *fp;
    if((fp = fopen(argv[1],"r"))== NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    G = GRAPHload(fp);
    fclose(fp);
    GRAPHedges(G,vett);

}