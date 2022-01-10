#include "bst.h"
typedef struct bstNode{
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
edge edgeNULL(){
    edge e;
    e->item = ItemSetNull();
    e->l = NULL;
    e->r = NULL;
    return e;
}
static Item ItemSetNull(){
    Item item;
    return item;
}
BST BSTinit(){
    BST bst = malloc(sizeof(*bst));
    bst->root = (bst->z = New(ItemSetNull(),NULL,NULL)); // tutte e due hanno un arco nullo
    bst->n_nodi = 0;
    return bst;
}
void BSTfree(BST bst){
    if(bst == NULL) return;
    treeFree(bst->root,bst->z);
    free(bst->z);
    free(bst);
}
static void treeFree(edge h,edge z){ // free tramite ricorsione dai due rami MOLTO PIU INTUITIVA
    if(h == z) return;
    treeFree(h->l,z);
    treefree(h->r,z);
}
static int bstCountR(edge h,edge z){
    if(h == z) return 0;
    return countR(h->l,z)+countR(h->r,z)+1;
}
int bstCount(BST bst){
    return bstCountR(bst->root,bst->z);
}
int bstEmpty(BST bst){
    if(bstCount(bst) == 0) return 1;
    return 0;
}
Item BSTSearch(BST bst,date key){
    edge x = Search(bst->root,key,bst->z);
    return x->item
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
int aggiornaValore(edge x,date key,edge z,transazione trans){
    if(x == z) return 1;
    if(dateCompare(keyGet(x->item),key) == 0) {
        x->item.q.valore += trans.valore;
        x->item.q.n += 1;
        return 0;
    }
    if(dateCompare(keyGet(x->item),key)<0) return aggiornaValore(x->l,key,z);
    else return aggiornaValore(x->r,key,z);
}
edge Search(edge x,date key,edge z){
    if(x == z) return ItemSetNull();
    if(dateCompare(keyGet(x->item),key) == 0) return x; // condizione di terminazione della funzione ricorsiva
    if(dateCompare(keyGet(x->item),key)<0) return Search(x->l,key,z);
    else return Search(x->r,key,z);
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
void inserimentoFoglia(BST bst,Item item){
    bst->root = inserimentoLeafR(bst->root,bst->z,item); // potrei modificare il bst proprio come nelle liste
    bst->n_nodi+=1;
}
edge inserimentoLeafR(edge h,edge z,Item i){
    if(h == z) return New(i,z,z);
    if(dateCompare(keyGet(i),keyGet(h->item))<0) // ricorro nella parte sinistra
        h->l = inserimentoLeaf(h->l,z,i);
    else h->r = inserimentoLeaf(h->r,z,i);
    return h;
}
// funzione di bilanciamento dell'albero utilizzando la mediana