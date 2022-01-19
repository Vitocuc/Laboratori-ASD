#include <stdio.h>
#include "titoli.h"
void leggiFile(char *file,List *l1);
void ricercaMinMaxbyDate(List l);
void ricercaMinMaxinTitolo(List l);
void ricercaQuotazione(List l);
link ricercaTitolo(List l);
void menu(List l,char *file);
int main(int argc,char **argv){
    if(argc>2) return 1;
    List l;
    menu(l,argv[1]);
    return 0;
}
void ricercaMinMaxinTitolo(List l){
    Item i;
    link x = ricercaTitolo(l);
    date data1,data2;
    int min = 0,max = 0;
    if(x != NULL){
        //ricerco elemento minimo ed elemento massimo nel bst
        data1 = minInBst(x);
        data2 = maxInBst(x);
        if(dataCompare(data1,data2)<=0) ricercaMinMaxBST(x,&min,&max,data1,data2);
        else ricercaMinMaxBST(x,&min,&max,data2,data1);
    }
    printf("Il minimo e': %d",min);
    printf("Il massimo e': %d",max);

}
link ricercaTitolo(List l){
    char titolo[MAXLEN];
    link x;
    printf("Inserisci il nome di un titolo:");
    scanf("%s",titolo);
    x =  SearchList(l,titolo);
    return x;
}
void ricercaQuotazione(List l){
    char titolo[MAXLEN];
    link x;    
    Item i;
    date data;
    printf("Inserisci il nome di un titolo:");
    scanf("%s",titolo);
    x = SearchList(l,titolo);
    if(x != NULL){
        data = inserisciData();
        i = BSTSearchperTitolo(x,data);
        if(compareItem(i,ItemSetNull()) == 0) printf("Non e' stata trovata nessuna quotazione giornaliera con questa data \n");
        else printf("La quotazione giornaliera in data %d/%d/%d e' %d",data.aaaa,data.mm,data.gg,i.q.valore);
    }
}
void ricercaMinMaxbyDate(List l){
    Item i;
    link x = ricercaTitolo(l);
    date data1,data2;
    int min = 0,max = 0;
    if(x != NULL){
        printf("\nInserisci la data 1:\n");
        data1 = inserisciData();
        printf("\nInserisci la data 2: \n");
        data2 = inserisciData();
        if(dataCompare(data1,data2)<=0) ricercaMinMaxBST(x,&min,&max,data1,data2);
        else ricercaMinMaxBST(x,&min,&max,data2,data1);
    }
    printf("Il minimo e': %d \n",min);
    printf("Il massimo e': %d \n",max);  
}
void menu(List l,char *file){
    int scelta,flag = 0;
    link x;
    while(flag == 0) {
        printf("\n");
        printf("[1] leggi da file \n");
        printf("[2] ricerca un titolo \n");
        printf("[3] ricerca la quotazione di un titolo \n");
        printf("[4] ricerca quotazione massima e minima tra due date \n");
        printf("[5] ricerca della quotazione massima e minima lungo tutto il periodo registrato \n");
        printf("[6] bilanciare un albero dato un  titolo \n");
        printf("[0] fine\n");
        printf("Inserisci il comando:");
        scanf("%d",&scelta);
        switch(scelta){
            case 1:
                leggiFile(file,&l);
                break;
            case 2:
                x = ricercaTitolo(l);
                if(x != NULL)
                    printf("E' stato trovato questo titolo\n");
                else
                    printf("Non e' stato trovato nessun titolo\n");
                break;
            case 3:
                ricercaQuotazione(l);
                break;
            case 4:
                ricercaMinMaxbyDate(l);
                break;
            case 5:
                ricercaMinMaxinTitolo(l);
                break;
            case 6:
                break;
            case 0:
                flag = 1;
                
                break;
            default:
                printf("Errore nell'inserimento del comando,ripetere \n");
                break;
        }
    }
}
void leggiFile(char *file,List *l1){
    FILE *fp;
    char codice[MAXLEN];
    int n,i = 0,n_titoli,j= 0;
    transazione t;
    Titolo titolo;
    List l;
    if((fp = fopen(file,"r")) == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    fscanf(fp,"%d",&n_titoli);
    l = initLista(n_titoli);
    while(j<n_titoli){
        fscanf(fp,"%s %d",codice,&n);
        titolo = initTitolo(codice,n);
        while(i<n){
            fscanf(fp,"%d/%d/%d %d:%d %d %d",&t.data.aaaa,&t.data.mm,&t.data.gg,&t.ora.hh,&t.ora.mm,&t.valore,&t.numero);
            caricaTransazione(titolo,t);
            i++;    
        }
        l = inserimentoOrdinato(l,titolo); 
        titolo = setTitoloVoid();
        i = 0;
        j++;
    }
    //stampaLista(l);
    aggiornaLista(l);
    stampaLista(l);
    *l1 = l;
    fclose(fp);
}