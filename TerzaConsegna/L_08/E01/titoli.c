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
};
struct binarysearchtree{
    edge root; // arco fittizzio che punta alla radice
    edge z; // nodo sentinella
    int n_nodi;
};
//prima di definire una qualunque funzioni di init ricordartsi della funzione che crea un nuovo nodo
static edge New(Item item,edge l,edge r){ // creazione di un nuovo nodo
    edge x = malloc(sizeof(*x));
    x->item = item;
    x->l = l;
    x->r = r;
    return x;
}
List initLista(int n){
    List l = malloc(sizeof(*l));
    l->head = NULL;
    l->n = n;
    return l;
}
void stampaCodice(Titolo t){
    printf("%s",t->codice);
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
BST BSTinit(){
    BST bst = malloc(sizeof(*bst));
    bst->root = (bst->z = New(ItemSetNull(),NULL,NULL)); // tutte e due hanno un arco nullo
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
    return BSTSearch(x->val->quotazioni,data);
}
int aggiornaValore(edge x,date key,edge z,transazione trans){
    if(x == z) return 1;
    if(dataCompare(keyGet(x->item),key) == 0) {
        x->item.q.valore += trans.valore;
        x->item.q.n += 1;
        return 0;
    }
    if(dataCompare(keyGet(x->item),key)<0) return aggiornaValore(x->l,key,z,trans);
    else return aggiornaValore(x->r,key,z,trans);
}
void aggiornaQuotazioneBST(BST bst,transazione trans){
    int flag = aggiornaValore(bst->root,trans.data,bst->z,trans);
    Item i;
    if(flag == 1){
        i.q.data = trans.data;
        i.q.n = 1;
        i.q.valore = trans.valore;
        inserimentoFoglia(bst,i);
    }
}
void visitInOrder(edge root){
    if(root == edgeNULL()) return;
    visitInOrder(root->l);
    printf("%d/%d/%d",root->item.q.data.aaaa,root->item.q.data.mm,root->item.q.data.gg);
    visitInOrder(root->r);
}
void calcolaQuotazioniR(edge root,int n_nodi){
    if(root == edgeNULL()) return;
    visitInOrder(root->l);
    root->item.q.valore = (root->item.q.valore*root->item.q.n)/n_nodi;
    visitInOrder(root->r);
}
void calcolaQuotazioni(BST bst){
    calcolaQuotazioniR(bst->root,bst->n_nodi);
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
edge inserimentoLeafR(edge h,edge z,Item i){
    if(h == z) return New(i,z,z);
    if(dataCompare(keyGet(i),keyGet(h->item))<0) // ricorro nella parte sinistra
        h->l = inserimentoLeafR(h->l,z,i);
    else h->r = inserimentoLeafR(h->r,z,i);
    return h;
}
void inserimentoFoglia(BST bst,Item item){
    bst->root = inserimentoLeafR(bst->root,bst->z,item); // potrei modificare il bst proprio come nelle liste
    bst->n_nodi+=1;
}
// funzione di bilanciamento dell'albero utilizzando la mediana
link SearchList(List l,char *nome){
    link x;
    for(x = l->head;x!= NULL && strcmp(x->val->codice,nome)!= 0;x = x->next);
    if(x == NULL) return NULL;
    else return x;
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
    aggiornaQuotazioneBST(t->quotazioni,trans);
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
// funzioni free