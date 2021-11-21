#include <oggetti.h>
typedef struct node *link;
typedef struct{
    char codice[N];
    pg personaggio;
}Item;
struct node{
    Item val;
    link next;
};
// definiscop la lista qui dentro
typedef struct{
    char codice[N];
    char nome[N];
    char classe [N];
    stat statistiche;
    inv inventario;
}pg;
void caricaPg();
link aggiungiPg();
link deletePg();
void calcolaStatistiche(); // del personaggio