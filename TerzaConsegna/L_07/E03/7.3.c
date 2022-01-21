#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
void leggiFile(Graph *G,char *file);
void menu(Graph G);
int main(char argc,char **argv){
    if(argc <2){
        return 1;
    }
    Graph G;
    leggiFile(&G,argv[1]);
    displayGraph(G);
    menu(G);
}
void menu(Graph G){
    int scelta = 0,flag = 0;
    char nome1[MAXLEN],nome2[MAXLEN],nome3[MAXLEN];
    while(flag == 0){
        printf("[1] Trasforma in lista di adiacenza");
    printf("[2] Elenca in ordine alfabetico");
    printf("[3] Verifica se 3 vertici formano un sottografo completo(con lista di adiacenze)");
    printf("[4] Verifica se 3 vertici formano un sottografo completo(con matrice di adiacenze)");
    printf("[5] Termina");
    printf("Inserisci la scelta: ");
    scanf("%d",&scelta);
    switch (scelta){
        case 1:
            inLadj(G);
            break;
        case 2:
            ordineAlfabeticoMadj(G);
            break;
        case 3:
            printf("Inserisci il primo nome:");
            scanf("%s",nome1);
            printf("Inserisci il secondo nome:");
            scanf("%s",nome2);
            printf("Inserisci il terzo nome:");
            scanf("%s",nome3);
            sgCompletoLadj(G,nome1,nome2,nome3);
            break;
        case 4:
            printf("Inserisci il primo nome:");
            scanf("%s",nome1);
            printf("Inserisci il secondo nome:");
            scanf("%s",nome2);
            printf("Inserisci il terzo nome:");
            scanf("%s",nome3);
            sgCompletoMadj(G,nome1,nome2,nome3);
            break;
        case 5:
            flag = 1;
            break;
        default:
            printf("Errore nell'inserimento,riprova");
            break;
    }
    } 
} 
void leggiFile(Graph *G,char *file){
    FILE *fp;
    Item ingressi;
    Graph g1;
    int i = 0;
    int ind1,ind2;
    if((fp = fopen(file,"r")) == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    while (!feof(fp)){
        fscanf(fp,"%s %s %s %s %d",ingressi.elab1.id_elab,ingressi.elab1.id_rete,ingressi.elab2.id_elab,ingressi.elab2.id_rete,&ingressi.flusso);
        i++;
    }
    fclose(fp);
     // sovrastimo il numero di vertici come 2E
    g1 = GraphInit((2*i));
    if((fp = fopen(file,"r")) == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    i = 0;
    while (!feof(fp)){
         fscanf( fp,"%s %s %s %s %d",ingressi.elab1.id_elab,ingressi.elab1.id_rete,ingressi.elab2.id_elab,ingressi.elab2.id_rete,&ingressi.flusso);
         GSTinsert(g1,ingressi.elab1);
         GSTinsert(g1,ingressi.elab2);
         ind1 = GraphgetIndexST(g1,ingressi.elab1.id_elab);
         ind2 = GraphgetIndexST(g1,ingressi.elab2.id_elab);
         GraphInsertE(g1,ind1,ind2,ingressi.flusso);
    }
    fclose(fp);
    *G = g1;   
}