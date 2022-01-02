#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
typedef struct node* link;
struct node {
    Item a;
    link next;
};
int main(char argc,char **argv){
    if(argc <2){
        return 1;
    }
    Graph g;
    leggiFile(&g,argv[1]);
    //menu(g);
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
        fscanf( fp,"%s %s %s %s %d",ingressi.elab1.id_elab,ingressi.id_rete,ingressi.elab2.id_elab,ingressi.id_rete,&ingressi.flusso);
        i++;
    }
    fclose(fp);
     // sovrastimo il numero di vertici come 2E
    g1 = GraphInit(2*i);
    //riempio la matrice di adiacenze
    if((fp = fopen(file,"r")) == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    while (!feof(fp)){
         //leggo ed imnserisco nella tabella di simboli
         fscanf( fp,"%s %s %s %s %d",ingressi.elab1.id_elab,ingressi.id_rete,ingressi.elab2.id_elab,ingressi.id_rete,&ingressi.flusso);
         STinsert(g1->tab,ingressi.elab1);
         STinsert(g1->tab,,ingressi.elab2);
         ind1 = STsearch(g1->tab,ingressi.id_elab1);
         ind2 = STsearch(g1->tab,ingressi.id_elab2);
         GraphInsertE(g1,ind1,ind2,ingressi.flusso);
    }
    fclose(fp);
    *G = g1;   
}