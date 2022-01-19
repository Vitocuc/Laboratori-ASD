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
struct bstNode{
    Item item;
    edge r;
    edge l;
    edge p;
    int n_nodi;
};
struct binarysearchtree{
    edge root; // arco fittizzio che punta alla radice
    edge z; // nodo sentinella
    int n_nodi;
};
//FUNZIONI LISTA
List initLista(int n){
    List l = malloc(sizeof(*l));
    l->head = NULL;
    l->n = n;
    return l;
}
void stampaCodice(Titolo t){
    printf("%s",t->codice);
}
Titolo initTitolo(char *codice,int n_trans){
    Titolo tit = malloc(sizeof(*tit));
    tit->codice = strdup(codice);
    tit->vett_trans = malloc(n_trans*sizeof(transazione));
    tit->n_trans = 0;
    tit->quotazioni = BSTinit();
    return tit;
}
void caricaTransazione(Titolo t,transazione trans){
    Item quotazione;
    t->vett_trans[t->n_trans] = trans;
    t->n_trans+=1;
    inserisciQuotazione(t->quotazioni,trans);
}
link SearchList(List l,char *nome){
    link x;
    for(x = l->head;x!= NULL && strcmp(x->val->codice,nome)!= 0;x = x->next);
    if(x == NULL) return NULL;
    return x;
}
link newNode(Titolo t,link next){
    link x = malloc(sizeof(*x));
    x->val = t;
    x->next = next;
    return x;
}
link inserimento(link h,Titolo t){
    link x,p;
    if(h == NULL || strcmp(t->codice,h->val->codice)<0){
        h = newNode(t,h);
        return h;
    }
    for(p =h,x=h->next;x!=NULL && strcmp(t->codice,x->val->codice)>0;p = x,x = x->next);
    p->next = newNode(t,x);
    return h;
}
List inserimentoOrdinato(List l,Titolo t){
    //calcolaQuotazioni(t->quotazioni);
    l->head = inserimento(l->head,t);
    return l;
}
Titolo setTitoloVoid(){
    Titolo tit = malloc(sizeof(*tit));
    tit->codice = NULL;
    tit->vett_trans = NULL;
    tit->n_trans = -1;
}
void stampaLista(List l){
    link x;
    for(x = l->head;x!=NULL;x = x->next){
        printf("Titolo: %s \n",x->val->codice);
        stampaBst(x->val->quotazioni);
    }
}
void aggiornaLista(List l){
    link x;
    for(x = l->head;x!= NULL;x = x->next){
        aggiornaQuotazioni(x->val->quotazioni);
    }
}
//FUNZIONI BST
static edge New(Item item,edge p,edge l,edge r,int n_nodi){ // creazione di un nuovo nodo
    edge x = malloc(sizeof(*x));
    x->item = item;
    x->l = l;
    x->r = r;
    x->p = p;
    x->n_nodi = n_nodi;
    return x;
}
BST BSTinit(){
    BST bst = malloc(sizeof(*bst));
    bst->root = (bst->z = New(ItemSetNull(),NULL,NULL,NULL,0)); // tutte e due hanno un arco nullo
    bst->n_nodi = 0;
    return bst;
}
static void treeFree(edge h,edge z){ // free tramite ricorsione dai due rami MOLTO PIU INTUITIVA
    if(h == z) return;
    treeFree(h->l,z);
    free(h->l);
    treeFree(h->r,z);
    free(h->r);
}
void BSTfree(BST bst){
    if(bst == NULL) return;
    treeFree(bst->root,bst->z);
    free(bst->z);
    free(bst);
}
int bstCountR(edge h,edge z){
    if(h == z) return 0;
    return bstCountR(h->l,z)+bstCountR(h->r,z)+1;
}
int bstCount(BST bst){
    return bstCountR(bst->root,bst->z);
}
int bstEmpty(BST bst){
    if(bstCount(bst) == 0) return 1;
    return 0;
}
date keyGet(Item item){
    return item.q.data;
}
edge Search(edge x,date key,edge z){
    if(x == z) return z;
    if(dataCompare(keyGet(x->item),key) == 0) return x; // condizione di terminazione della funzione ricorsiva
    if(dataCompare(keyGet(x->item),key)<0) return Search(x->l,key,z);
    else return Search(x->r,key,z);
}
Item BSTSearch(BST bst,date key){
    edge x = Search(bst->root,key,bst->z);
    return x->item;
}
Item BSTSearchperTitolo(link x,date data){
    Item i = BSTSearch(x->val->quotazioni,data);
    return i;
}
edge updateBstR(BST bst,edge h,edge z,Item i){
    if(dataCompare(keyGet(i),keyGet(h->item)) == 0){
        h->item.q.valore += i.q.valore;
        h->item.q.n += i.q.n;
        return h;
    }
    if(dataCompare(keyGet(i),keyGet(h->item))<0)
        h->l = updateBstR(bst,h->l,z,i);
    else h->r =  updateBstR(bst,h->l,z,i);
    return h;
}
void updateBst(BST bst,Item i){
    updateBstR(bst,bst->root,bst->z,i);
}
void inserisciQuotazione(BST bst,transazione trans){
    //controllo se ho gia una quotazione con quella data
    Item i = BSTSearch(bst,trans.data);
    Item tmp;
    tmp.q.valore = trans.valore *trans.numero;
    tmp.q.data = trans.data;
    tmp.q.n = trans.numero;
    if(compareItem(i,ItemSetNull()) == 0){
        inserimentoFoglia(bst,tmp);
    }else{
        updateBst(bst,tmp);
    }
}
Item max(edge h,edge z){ // scendere in profondita come nella lista 
    while(h->r != z){
        h = h->r;
    }
    return h->item;
}
Item BSTmax(BST bst){
    return max(bst->root,bst->z);
}
Item min(edge h,edge z){ // scendere in profondita come nella lista 
    while(h->l != z){
        h = h->l;
    }
    return h->item;
}
Item BSTmin(BST bst){
    return min(bst->root,bst->z);
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
    printf("Inserisci l'anno:");
    scanf("%d",&d.aaaa);
    printf("Inserisci il mese:");
    scanf("%d",&d.mm);
    printf("Inserisci il giorno:");
    scanf("%d",&d.gg);
    return d;
}
edge edgeNULL(){
    edge e;
    e->item = ItemSetNull();
    e->l = NULL;
    e->r = NULL;
    return e;
}
Item ItemSetNull(){
    Item item;
    date data;
    data.aaaa = 0;
    data.mm = 0;
    data.gg = 0;
    item.q.n = 0;
    item.q.valore = 0;
    item.q.data = data; 
    return item;
}
int checkNumero(int n1,int n2){
    if(n1 == n2) return 0;
    else return 1;
}
int checkValore(int n1,int n2){
    if(n1 == n2) return 0;
    else return 1;
}
int compareItem(Item i1,Item i2){
    if(checkNumero(i1.q.n,i2.q.n) == 0 && checkValore(i1.q.valore,i2.q.valore) == 0 && dataCompare(i1.q.data,i2.q.data) == 0) return 0;
    else return 1;
}
edge inserimentoLeafR(BST bst,edge h,edge z,Item i){
    if(h == z) {
        bst->n_nodi+=1;
        return New(i,z,z,z,1);
    }
    if(dataCompare(keyGet(i),keyGet(h->item))<0){ // ricorro nella parte sinistra
        h->l = inserimentoLeafR(bst,h->l,z,i);
        h->l->p = h;
    }
    else {
        h->r = inserimentoLeafR(bst,h->r,z,i);
        h->r->p = h;
    }
    (h->n_nodi)++;
    return h;
}
void inserimentoFoglia(BST bst,Item item){
    bst->root = inserimentoLeafR(bst,bst->root,bst->z,item); // potrei modificare il bst proprio come nelle liste
}
void stampa(edge x,edge z){
    if(x == z) return;
    printf("Data: %d/%d/%d Valore: %d Numero di nodi: %d \n",x->item.q.data.gg,x->item.q.data.mm,x->item.q.data.aaaa,x->item.q.valore,x->n_nodi);
    stampa(x->l,z);
    stampa(x->r,z);
}
void stampaBst(BST bst){
    edge x = bst->root;
    stampa(x,bst->z);
}
void aggiorna(edge x,edge z){ 
    if(x == z) return;
    x->item.q.valore = x->item.q.valore/x->item.q.n;
    aggiorna(x->l,z);
    aggiorna(x->r,z);
}
void aggiornaQuotazioni(BST bst){
    edge x = bst->root;
    aggiorna(x,bst->z);
}
int getValue(Item i){
    return i.q.valore;
}
void ricercaMinR(edge h,edge z,date data1,date data2,int *min){
    if(h == z) return;
    ricercaMinR(h->l,z,data1,data2,min);
    if(dataCompare(keyGet(h->item),data1)>=0 && dataCompare(keyGet(h->item),data2)<=0){ // chiave compresa tra due date
        if(getValue(h->item)<(*min)) (*min) = getValue(h->item);
        //if(getValue(h->item)>max) max = getValue(h->item);
    }
    ricercaMinR(h->r,z,data1,data2,min);
}
void ricercaMaxR(edge h,edge z,date data1,date data2,int *max){
    if(h == z) return;
    ricercaMaxR(h->l,z,data1,data2,max);
    if(dataCompare(keyGet(h->item),data1)>=0 && dataCompare(keyGet(h->item),data2)<=0){ // chiave compresa tra due date
        if(getValue(h->item)>(*max)) (*max) = getValue(h->item);
    }
    ricercaMaxR(h->r,z,data1,data2,max);
}
void ricercaMin(BST bst,date data1,date data2,int *min){
    ricercaMinR(bst->root,bst->z,data1,data2,min);
}
void ricercaMax(BST bst,date data1,date data2,int *max){
    ricercaMaxR(bst->root,bst->z,data1,data2,max);
}
void ricercaMinMaxBST(link x,int *min,int *max,date data1,date data2){
    (*min) = (*max) = getValue(x->val->quotazioni->root->item);
    ricercaMin(x->val->quotazioni,data1,data2,min);
    ricercaMax(x->val->quotazioni,data1,data2,max);
}
date minInBst(link x){
    Item i = BSTmin(x->val->quotazioni);
    return keyGet(i);
}
date maxInBst(link x){
    Item i = BSTmax(x->val->quotazioni);
    return keyGet(i);
}