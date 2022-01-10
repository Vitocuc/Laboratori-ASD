#include "titoli.h"
struct lista{
    link head;
    int n;
};
struct titolo{
    char *codice;
    transazione *vett_trans;
    int n_trans;
    BST quotazioni;
};
struct node{
    Titolo val;
    link next;
};
List initLista(){
    List l = malloc(sizeof(*l));
    l->head = NULL;
    l->n = 0;
    return l;
}
int dataCompare(date data1,date data2){
    int diff = data1.aaaa-data2.aaaa;
    if(diff!=0) return diff;
    diff = data1.mm-data2.mm;
    if(diff!=0) return diff;
    diff = data1.gg-data2.gg;
    if(diff!=0) return diff;
    return 0;
}
date inserisciData(){
    date d;
    scanf("Inserisci l'anno %d",&d.aaaa);
    scanf("Inserisci il mese %d",&d.mm);
    scanf("Inserisci il giorno %d",&d.gg);
    return d;
}
int SearchList(List l,char *nome){
    link x;
    //ricerca dicotomica nella lista
    for(x = l->head;x!= NULL && strcmp(x->val->codice,nome)!= 0;x = x->next);
    if(x == NULL) return 1;
    else return 0;
}
Titolo initTitolo(char *codice,int n_trans){
    Titolo tit = malloc(sizeof(*tit));
    tit->codice = strdup(codice);
    tit->vett_trans = malloc(n_trans*sizeof(transazione));
    tit->n_trans = 0;
    tit->quotazioni = BSTinit();
}
void caricaTransazione(Titolo t,transazione trans){
    Item quotazione;
    t->vett_trans[t->n_trans] = trans;
    t->n_trans+=1;
    // inserisco la quotazione nel bst
    aggiornaQuotazioneBST(t->quotazioni,trans);
}
link newNode(Titolo t,link next){
    link x = malloc(sizeof(*x));
    x->val = t;
    x->next = next;
    return x;
}
date keyGet(Item item){
    return item.q.data;
}
List inserimentoOrdinato(List l,Titolo t){
    link x,p;
    calcolaQuotazioni(t->quotazioni); // calcolo tutte le quotazini giornaliere e poi inserisco in maniera ordinata
    if(l->head == NULL || strcmp(t->codice,l->head->next->val->codice)<0){
        l->head = newNode(t,l->head->next);
        return l;
    }
    for(p =l->head,x=l->head->next;x!=NULL && strcmp(t->codice,x->val->codice)>0;p = x,x = x->next);
    p->next = newNode(t,x);
    return l;
}
Titolo setTitoloVoid(){
    Titolo tit = malloc(sizeof(*tit));
    tit->codice = NULL;
    tit->vett_trans = NULL;
    tit->n_trans = -1;
}
// funzioni free