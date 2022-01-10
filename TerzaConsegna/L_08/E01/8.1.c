#include <stdio.h>
#include "titoli.h"
void leggiFile(char *file,List *l1);
void menu(List l,char *file);
int main(int argc,char **argv){
    if(argc>1) return 1;
    List lista;
    leggiFile(argv[1],&lista);
    return 0;
}
int ricercaTitolo(List l){
    char titolo[MAXLEN],flag = 0;
    scanf("Inserisci il nome di un titolo:  %s",titolo);
    return SearchList(l,titolo);
}
/*
void ricercaQuotazione(List l){
    int flag = ricercaTitolo(l);
    date data;
    Item i;
    if(flag == 0){
        data = inserisciData();
        i = BSTSearch(l->quotazioni,data);
        if(i == ItemSetNull()) printf("Non è stata trovata nessuna quotazione giornaliera con questa data");
        else printf("La quotazione giornaliera in data %d/%d/%d è %d",data.aaaa,data.mm,data.gg,i.q.valore);
    }
}*/
void ricercaMinMaxbyDate(List l){
    int flag = ricercaTitolo(l);
    date data1 = inserisciData();
    date data2 = inserisciData();
    Item i;
}
void menu(List l,char *file){
    int scelta,flag = 0,ris;
    while(flag = 0) {
        printf("[1] leggi da file \n");
        printf("[2] ricerca un titolo \n");
        printf("[3] ricerca la quotazione di un titolo \n");
        printf("[4] ricerca quotazione massima e minima tra due date \n");
        printf("[5] ricerca della quotazione massima e minima lungo tutto il periodo registrato \n");
        printf("[6] bilanciare un albero dato un  titolo \n");
        printf("[0] fine\n");
        scanf("Inserisci un comando: %d",scelta);
        switch (scelta){
            case(1):
                leggiFile(file,&l);
                break;
            case(2):
                ris = ricercaTitolo(l);
                if(ris == 0)
                    printf("E' stato trovato questo titolo");
                else
                    printf("Non e' stato trovato nessun titolo");
                break;
            case(3):
                ricercaQuotazione(l);
                break;
            case(4):
                break;
            case(5):
                break;
            case(6):
                break;
            case(0):
                flag = 1;
                break;
            default:
                break;
        }
    }
}
void leggiFile(char *file,List *l1){
    FILE *fp;
    char *codice;
    int n,i = 0;
    transazione t;
    Titolo titolo;
    List l;
    if((fp = fopen(file,"r")) == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    l = initLista();
    while(!feof(fp)){
        fscanf(fp,"%s %d",codice,&n);
        titolo = initTitolo(codice,n);
        while(i<n){
            fscanf(fp,"%s %s %d %d",t.data,t.ora,t.valore,t.numero);
            caricaTransazione(titolo,t);
            i++;
        }
        inserimentoOrdinato(l,titolo); 
        titolo = setTitoloVoid();
        i = 0;
    }
    *l1 = l;
}