#ifndef LIST
#define LIST
#define MAXLEN 21
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
typedef struct lista *List;
typedef struct node *link;
typedef struct titolo *Titolo;
typedef struct{
    date data;
    time ora;
    int valore;
    int numero;
}transazione;
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
    int valore;
    date data;
    int n;
} quotazione_giorn;
date inserisciData();
int SearchList(List l,char *nome);
date keyGet(Item item);
List initLista();
int dataCompare(date data1,date data2);
Titolo initTitolo(char *codice,int n_trans);
void caricaTransazione(Titolo t,transazione trans);
link newNode(Titolo t,link next);
List inserimentoOrdinato(List l,Titolo t);
Titolo setTitoloVoid();
#endif