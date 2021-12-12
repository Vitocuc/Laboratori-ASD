#include <inventario.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *link;
typedef struct tab_l *lista;
struct tab_l{
    link head;
    link tail;
    int n_pg;
}
typedef struct{
    char codice[N];
    char nome[N];
    char classe [N];
    stat statistiche;
    inv equipaggiamento;
}pg;
struct node{
    Item val;
    link next;
};
typedef struct{
    char codice[N];
    pg personaggio;
}Item;
// valutare se fare le wrapper, se dovessi fare le wrapper allora posso scegliere di fare delle funzioni
// di creazione dei due puntatori opachi che mi gestiscono le struct in maniera piu trasparent

void caricaPg_l(link *head,link *tail,int n*){ // fatto
    FILE *fp;
    Item val;
    int i = 0;
    if((fp = fopen("personaggi.txt","r") == NULL)){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    //,&val.personaggio.statistiche.
    while(!feof(fp)){
        if(!feof(fp)){
            fscanf(fp,"%s %s %s %d %d %d %d %d %d",val.personaggio.codice,val.personaggio.nome,val.personaggio.classe); // da inserire le altre statistiche
            //inserimento nel nodo
            inserimentoPersonaggio_l(head,val,tail);
            i++;
        }
    }
    *n = i;
}
void caricaPg(lista l_pg){
    caricaPg_l(&l_pg->head,&l_pg->tail,&l_pg->n_pg)
}
Item inserimentoItem(){ // finire inserimento di item
    Item val;
    return val;
}
void cancellaPersonaggio(lista l_pg){
    char *codice;
    printf("Inserisci il codice del personaggio");
    scanf("%s",codice);
    cancellaPersonaggio_l(&l_pg->head,codice,&l_pg->n_pg)
}
void cancellaPersonaggio_l(link *head,char *codice,int *n){ // fatto
    link x,t;
    for(x = *head;x != NULL && strcmp(x.val.personaggio.codice,codice) != 0 ;x = x->next)
    if(x != NULL){
        if(x == *head){
            t = x;
            *head = x->next;
            free(t);
        }else{
            t = x;
            x = x->next;
            free(t);
        }
        //diminuire la dimensione 
        *n--;
    }else{
        printf("Non è stato trovato alcun personaggio \n");
    }
}
void inserimentoPersonaggio(lista l_pg){ //da finire funzione di inserimento di item
    Item val;
    val = inserimentoItem();
    inserimentoPersonaggio_l(&l_pg->head,val,&l_pg->tail,&l_pg->n_pg);
}
void inserimentoPersonaggio_l(link *head,Item val,link *tail,int *n_pg){ // fatto
    if(*head == *tail){
        *head->next = newNode(NULL,val);
        *tail = *head->next;
    }else{
        *tail->next = newNode(NULL,val)
    }
    *n_pg++;
}
link newNode(link head,Item val){ // fatto
    link x;
    x = malloc(sizeof(link));
    x->val = val;
    x->next = NULL;
    return x;
}
void ricercaPersonaggio(lista l_pg){
    char *codice;
    printf("Inserisci il codice da ricercare:");
    scanf("%s",codice);
    ricercaPersonaggio_l(l_pg->head,codice);
}
void ricercaPersonaggio_l(link head,char *codice){
    link x;
    for(x = head;x != NULL && strcmp(x.val.personaggio.codice,codice) != 0 ;x = x->next)
    if(x != NULL){
        stampaPersonaggio_l(x.val.personaggio);
    }else printf("Non è stato trovato alcun personaggio");

}
void stampaPersonaggio_l(pg personaggio){ // da finire
}
void modificaEqu(lista l_pg){
    char *codice;
    printf("Inserisci il codice del personaggio da ricercare :");
    scanf("%s",codice);
    modificaEqu_l(l_pg->head,codice)
}
void modificaEqu_l(link head,char *codice){
    link x;
    for(x = head;x != NULL && strcmp(x.val.personaggio.codice,codice) != 0 ;x = x->next)
    if(x != NULL){
        //finisco funzione di modifica dell'equipaggiamento
    }else printf("Non è stato trovato alcun personaggio");

}
lista initList(){
    struct tab_l l_pg;
    l_pg.head = NULL;
    l_pg.tail = NULL;
    l_pg.n_pg = 0;
    return pg;
}