#ifndef PG
#define PG 
#include "inventario.h"
typedef struct node *link;
typedef struct tab_l *lista;
typedef struct equip *tab_eq;
struct tab_l{
    link head;
    link tail;
    int n_pg;
};
struct equip {
    int inUso;
    ogg *vett_equ;
};
typedef struct{
    char codice[N];
    char nome[N];
    char classe [N];
    stat statistiche;
    tab_eq e; // è un'altra struct che deve contenere dei riferimenti a sdegli oggeti preosenti all'interno 
}pg;
typedef struct{
    pg personaggio;
}Item;
struct node{
    Item val;
    link next;
};
link newNode(link h,Item val);
void stampaPersonaggi(lista l_pg);
void stampaPersonaggio_l(pg personaggio);
void stampaPersonaggio(lista l_pg);
void inserimentoEqu_l(pg personaggio,char *nome,tabInv_t tabInv);
void eliminaEqu_l(pg personaggio,char *nome,tabInv_t tabInv);
void eliminaEq(lista l_pg,tabInv_t tabInv);
void inserimentoEqu(lista l_pg,tabInv_t tabInv);
void inserimentoPersonaggio_l(link *head,Item val,link *tail,int *n_pg);
void caricaPg_l(link *head,link *tail,int *n);
void caricaPg(lista l_pg);
Item inserimentoItem();
void cancellaPersonaggio_l(link *head,char *codice,int *n);
void cancellaPersonaggio(lista l_pg);
void ricercaPersonaggio_l(link head,char *codice);
void inserimentoPersonaggio(lista l_pg);
void ricercaPersonaggio(lista l_pg);
void modificaEqu_l(link head,char *codice,char *nome_equ);
void modificaEqu(lista l_pg);
lista initList();
#endif