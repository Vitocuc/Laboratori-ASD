#ifndef TITOLI
#define TITOLI
#define MAXLEN 21
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ADT 1 LIVELLO BST
typedef struct lista *List;
typedef struct binarysearchtree *BST;
typedef struct bstNode *edge;
typedef struct node *link;
//ADT 1 LIVELLO TITOLO
typedef struct titolo *Titolo;
//QUASI ADT LISTA
typedef struct{
    int aaaa;
    int mm;
    int gg;
}date;
typedef struct {
    int hh;
    int mm;
}time;
typedef struct{
    date data;
    time ora;
    int valore;
    int numero;
}transazione;
//QUASI ADT BST
typedef struct{ 
    int valore;
    date data;
    int n;
}quotazione_giorn;
typedef struct {
    //quotazioni giornaliere in base alla data
    quotazione_giorn q;
}Item;
//FUNZIONi LISTA
List initLista(int n);
date inserisciData();
link SearchList(List l,char *nome);
date keyGet(Item item);
int dataCompare(date data1,date data2);
Titolo initTitolo(char *codice,int n_trans);
void caricaTransazione(Titolo t,transazione trans);
link newNode(Titolo t,link next);
List inserimentoOrdinato(List l,Titolo t);
Titolo setTitoloVoid();
//FUNZIONI BST
BST BSTinit();
static edge New(Item item,edge l,edge r);
Item ItemSetNull();
int compareItem(Item i1,Item i2);
void BSTfree(BST bst);
int bstCount(BST bst);
int bstEmpty(BST bst);
Item BSTSearch(BST bst,date key);
Item BSTmax(BST bst);
Item BSTSearchperTitolo(link x,date data);
Item BSTmin(BST bst);
void inserimentoFoglia(BST bst,Item item);
void aggiornaQuotazioneBST(BST bst,transazione trans);
void visitInOrder(edge root);
void calcolaQuotazioni(BST bst);
#endif