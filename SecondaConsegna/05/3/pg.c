#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// valutare se fare le wrapper, se dovessi fare le wrapper allora posso scegliere di fare delle funzioni
// di creazione dei due puntatori opachi che mi gestiscono le struct in maniera piu trasparent
link newNode(link h,Item val){ // fatto
    link x;
    x = malloc(sizeof(link));
    x->val = val;
    x->next = h;
    return x;
}

void stampaPersonaggio_l(pg personaggio){//fatto
    int i = 0;
    printf("%s %s %s %d %d %d %d %d %d \n",personaggio.codice,personaggio.nome,personaggio.classe,personaggio.statistiche.hp,personaggio.statistiche.mp,personaggio.statistiche.atk,personaggio.statistiche.def,personaggio.statistiche.mag,personaggio.statistiche.spr);
    for(i = 0;i<personaggio.e->inUso;i++)
        stampaOggetto_i(personaggio.e->vett_equ[i]);
}
void stampaPersonaggio(lista l_pg){
    link x;
    char *codice;
    printf("Inserisci il codice del personaggio da stampare:");
    scanf("%s",codice);
    for(x = l_pg->head;x != NULL && strcmp(codice,x->val.personaggio.codice)!= 0;x = x->next)
    if(x != NULL){
        stampaPersonaggio_l(x->val.personaggio);

    }else printf("Non è stato trovato alcun personaggio da stampare");
}
void stampaPersonaggi(lista l_pg){
    link x ;
    for( x= l_pg->head ;x != NULL;x = x->next)
        stampaPersonaggio_l(x->val.personaggio);
} 
void inserimentoEqu_l(pg personaggio,char *nome,tabInv_t tabInv){//fatto
    int i = 0;
    for(i = 0;i<tabInv->n_oggetti;i++){
        if(strcmp(nome,tabInv->inv[i].nome) == 0){
            if(personaggio.e->vett_equ == NULL){
                personaggio.e->vett_equ = malloc(personaggio.e->inUso+1 * sizeof(ogg));
                personaggio.e->vett_equ[personaggio.e->inUso] = tabInv->inv[i];
                personaggio.e->inUso = 1;
            }else{
                realloc(personaggio.e->vett_equ,personaggio.e->inUso+1 * sizeof(ogg));
                personaggio.e->vett_equ[personaggio.e->inUso] = tabInv->inv[i];
                personaggio.e->inUso++;
            }
        }
    }
    

}
void eliminaEqu_l(pg personaggio,char *nome,tabInv_t tabInv){//fatto
     int i = 0,j = 0,k = 0;
    for(i = 0;i<tabInv->n_oggetti;i++){
        if(strcmp(nome,tabInv->inv[i].nome) == 0){
            if(personaggio.e->vett_equ == NULL)
                printf("L'oggetto non è presente nella lista di equipaggiamenti di quel personaggio");
            else{
                for(j = 0;j<personaggio.e->inUso && strcmp(nome,personaggio.e->vett_equ[j].nome) != 0;j++)
                for(k = j;j<personaggio.e->inUso;j++)personaggio.e->vett_equ[k] = personaggio.e->vett_equ[k+1];
                personaggio.e->inUso--;
                printf("L'oggetto è stato eliminato");
            }
        }
    }
}
void eliminaEq(lista l_pg,tabInv_t tabInv){
    char *codice,*nome;
    link x;
    printf("Inserisci il codice del personaggio da cui vuoi eliminare l'oggetto:");
    scanf("%s",codice);
    printf("Inserisci il nome dell'oggetto da eliminare:");
    scanf("%s",nome);
    for(x = l_pg->head;x!= NULL && strcmp(x->val.personaggio.codice,codice) != 0 ;x = x->next) 
    if(x != NULL){
        eliminaEqu_l(x->val.personaggio,nome,tabInv);
    }else printf("Non è stato trovato alcun oggetto");

}
void inserimentoEqu(lista l_pg,tabInv_t tabInv){
    char *codice,*nome;
    link x;
    printf("Inserisci il codice del personaggio nel quale vuoi inserire l'oggetto:");
    scanf("%s",codice);
    printf("Inserisci il nome dell'oggetto da inserire:");
    scanf("%s",nome);
    for(x = l_pg->head;x!= NULL && strcmp(x->val.personaggio.codice,codice) != 0 ;x = x->next) 
    if(x != NULL){
        inserimentoEqu_l(x->val.personaggio,nome,tabInv);
    }else printf("Non è stato trovato alcun oggetto");
}
void inserimentoPersonaggio_l(link *head,Item val,link *tail,int *n_pg){ // fatto;
    if(*head == NULL){
        *head = *tail = newNode(NULL,val);
    }else{
        printf(" ciao");
        (*tail)->next = newNode(NULL,val);
        *tail = (*tail)->next;
    }
    *n_pg++;
}
void caricaPg_l(link *head,link *tail,int *n){ // fatto
    FILE *fp;
    Item val;
    int i = 0;
    if((fp = fopen("pg.txt","r"))== NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    
    while(!feof(fp)){
        if(!feof(fp)){
            if(val.personaggio.e != NULL) {realloc(val.personaggio.e,sizeof(tab_eq));  }
            else val.personaggio.e = malloc(sizeof(tab_eq));
            fscanf(fp,"%s %s %s %d %d %d %d %d %d",val.personaggio.codice,val.personaggio.nome,val.personaggio.classe,&val.personaggio.statistiche.hp,&val.personaggio.statistiche.mp,&val.personaggio.statistiche.atk,&val.personaggio.statistiche.def,&val.personaggio.statistiche.mag,&val.personaggio.statistiche.spr);
            val.personaggio.e->inUso = 0;
            val.personaggio.e->vett_equ = NULL;
            inserimentoPersonaggio_l(head,val,tail,n);
            stampaPersonaggio_l((*head)->val.personaggio);
            i++;
        }
    }
    *n = i;
    fclose(fp);
}
void caricaPg(lista l_pg){
    caricaPg_l(&l_pg->head,&l_pg->tail,&l_pg->n_pg);
}
Item inserimentoItem(){
    Item val;
    scanf("%s %s %s %d %d %d %d %d %d",val.personaggio.codice,val.personaggio.nome,val.personaggio.classe,&val.personaggio.statistiche.hp,&val.personaggio.statistiche.mp,&val.personaggio.statistiche.atk,&val.personaggio.statistiche.def,&val.personaggio.statistiche.mag,&val.personaggio.statistiche.spr); // da inserire le altre statistiche
    return val;
}
void cancellaPersonaggio_l(link *head,char *codice,int *n){ // fatto
    link x,t;
    for(x = *head;x != NULL && strcmp(x->val.personaggio.codice,codice) != 0 ;x = x->next)
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
        *n-=1;
    }else{
        printf("Non è stato trovato alcun personaggio \n");
    }
}
void cancellaPersonaggio(lista l_pg){
    char *codice;
    printf("Inserisci il codice del personaggio");
    scanf("%s",codice);
    cancellaPersonaggio_l(&l_pg->head,codice,&l_pg->n_pg);
}
void ricercaPersonaggio_l(link head,char *codice){
    link x;
    for(x = head;x != NULL && strcmp(x->val.personaggio.codice,codice) != 0 ;x = x->next)
    if(x != NULL){
        stampaPersonaggio_l(x->val.personaggio);
    }else printf("Non è stato trovato alcun personaggio");

}
void inserimentoPersonaggio(lista l_pg){ //da finire funzione di inserimento di item
    Item val;
    val = inserimentoItem();
    inserimentoPersonaggio_l(&l_pg->head,val,&l_pg->tail,&l_pg->n_pg);
}
void ricercaPersonaggio(lista l_pg){
    char *codice;
    printf("Inserisci il codice da ricercare:");
    scanf("%s",codice);
    ricercaPersonaggio_l(l_pg->head,codice);
}
void modificaEqu_l(link head,char *codice,char *nome_equ){
    link x;
    int i = 0;
    for(x = head;x != NULL && strcmp(x->val.personaggio.codice,codice) != 0 ;x = x->next)
    if(x != NULL){
        for(i = 0;i<x->val.personaggio.e->inUso;i++){
            if((x->val.personaggio.e->vett_equ[i].nome,nome_equ) == 0){
            }
        }
    }else printf("Non è stato trovato alcun personaggio");
}
void modificaEqu(lista l_pg){
    char *codice;
    char *nome_equ;
    printf("Inserisci il codice del personaggio da ricercare :");
    scanf("%s",codice);
    printf("Inserisci il nome dell'oggetto da equipaggiare :");
    scanf("%s",nome_equ);
    modificaEqu_l(l_pg->head,codice,nome_equ);
}
lista initList(){
    lista l_pg = malloc(sizeof(lista));
    l_pg->head = malloc(sizeof(link));
    l_pg->tail = malloc(sizeof(link));
    l_pg->head = NULL;
    l_pg->tail = NULL;
    l_pg->n_pg = 0;
    return l_pg;
}