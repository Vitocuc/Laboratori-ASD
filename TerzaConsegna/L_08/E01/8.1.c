#include <stdio.h>
#include "titoli.h"
void leggiFile(char *file,List *l1);
void ricercaMinMaxbyDate(List l);
void ricercaQuotazione(List l);
link ricercaTitolo(List l);
void menu(List l,char *file);
int main(int argc,char **argv){
    if(argc>2) return 1;
    List l;
     leggiFile(argv[1],&l);
     ricercaQuotazione(l);
    //menu(l,argv[1]);
    return 0;
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
        if(compareItem(i,ItemSetNull()) != 0) printf("Non e' stata trovata nessuna quotazione giornaliera con questa data");
        else printf("La quotazione giornaliera in data %d/%d/%d è %d",data.aaaa,data.mm,data.gg,i.q.valore);
    }
}
void ricercaMinMaxbyDate(List l){
    Item i;
    link x = ricercaTitolo(l);
    date data1 = inserisciData();
    date data2 = inserisciData();
    
}
void menu(List l,char *file){
    int scelta,flag = 0;
    link x;
    while(flag == 0) {
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
                printf("ciao");
                break;
            /*
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            */
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
    *l1 = l;
    fclose(fp);
}