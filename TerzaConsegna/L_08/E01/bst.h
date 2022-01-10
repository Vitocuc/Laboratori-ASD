#ifndef BS
#define BS
#include <stdio.h>
#include <stdlib.h>
#include "quotazioni.h"
typedef struct binarysearchtree *BST;
typedef struct bstNode *edge;
typedef struct {
    //quotazioni giornaliere in base alla data
    quotazione_giorn q;
}Item;
BST BSTinit();
static edge New(Item item,edge l,edge r);
static Item ItemSetNull();
void BSTfree(BST bst);
int bstCount(BST bst);
int bstEmpty(BST bst);
Item BSTSearch(BST bst,date key);
Item BSTmax(BST bst);
Item BSTmin(BST bst);
void inserimentoFoglia(BST bst,Item item);
void aggiornaQuotazioneBST(BST bst,transazione trans);
//inserimento della quotazione all'interno del bst
void visitInOrder(edge root);
void calcolaQuotazioni(BST bst);
#endif