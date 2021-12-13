#include "inventario.h"
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
typedef struct {
    int inUso;
    ogg *vett_equ = NULL;
}equip;
typedef struct{
    char codice[N];
    char nome[N];
    char classe [N];
    stat statistiche;
    equip equipaggiamento; // è un'altra struct che deve contenere dei riferimenti a sdegli oggeti preosenti all'interno 
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
void inserimentoEqu_l(pg personaggio,char *nome,tabInv_t tabInv){
    int i = 0;
    for(i = 0;i<tabInv->n_oggetti;i++){
        if(strcmp(nome,tabInv->inv[i].nome) == 0){
            if(personaggio.equipaggiamento.vett_equ == NULL){
                personaggio.equipaggiamento.vett_equ = malloc(personaggio.equipaggiamento.inUso+1 * sizeof(ogg));
                personaggio.equipaggiamento.vett_equ[personaggio.equipaggiamento.inUso] = tabInv->inv[i];
                personaggio.equipaggiamento.inUso = 1;
            }else{
                realloc(personaggio.equipaggiamento.vett_equ,personaggio.equipaggiamento.inUso+1 * sizeof(ogg));
                personaggio.equipaggiamento.vett_equ[personaggio.equipaggiamento.inUso] = tabInv->inv[i];
                personaggio.equipaggiamento.inUso++;
            }
        }
    }
    

}
void eliminaEqu_l(pg personaggio,char *nome){
     int i = 0;
    for(i = 0;i<tabInv->n_oggetti;i++){
        if(strcmp(nome,tabInv->inv[i].nome) == 0){
            if(personaggio.equipaggiamento.vett_equ == NULL){
                printf("L'oggetto non è presente nella lista di equipaggiamenti di quel personaggio");
            }else{
                //ricerca l'oggetto nell'equipaggiamento
                personaggio.equipaggiamento.inUso--;
            }
        }
    }

}
void eliminaEq(lista l_pg){
    char *codice,*nome;
    link x;
    printf("Inserisci il codice del personaggio da cui vuoi eliminare l'oggetto:");
    scanf("%s",codice);
    printf("Inserisci il nome dell'oggetto da eliminare:");
    scanf("%s",nome);
    for(x = l_pg->head;x!= NULL && strcmp(x->val.codice,codice) != 0 ;x = x->next) 
    if(x != NULL){
        eliminaEqu_l(x,nome);
    }else printf("Non è stato trovato alcun oggetto");

}
void inserimentoEqu(lista l_pg,tabInv_t tabInv){
    char *codice,*nome;
    link x;
    printf("Inserisci il codice del personaggio nel quale vuoi inserire l'oggetto:");
    scanf("%s",codice);
    printf("Inserisci il nome dell'oggetto da inserire:");
    scanf("%s",nome);
    for(x = l_pg->head;x!= NULL && strcmp(x->val.codice,codice) != 0 ;x = x->next) 
    if(x != NULL){
        inserimentoEqu_l(x,nome,tabInv);
    }else printf("Non è stato trovato alcun oggetto");
    

}

void caricaPg_l(link *head,link *tail,int n*){ // fatto
    FILE *fp;
    Item val;
    int i = 0;
    if((fp = fopen("personaggi.txt","r") == NULL)){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    while(!feof(fp)){
        if(!feof(fp)){
            fscanf(fp,"%s %s %s %d %d %d %d %d %d",val.personaggio.codice,val.personaggio.nome,val.personaggio.classe,&val.personaggio.statistiche.hp,&val.personaggio.statistiche.mp,&val.personaggio.statistiche.atk,&val.personaggio.statistiche.def,&val.personaggio.statistiche.mag,&val.personaggio.statistiche.spr); // da inserire le altre statistiche
            //inserimento nel nodo
            inserimentoPersonaggio_l(head,val,tail);
            i++;
        }
    }
    *n = i;
    fclose(fp);
}
void caricaPg(lista l_pg){
    caricaPg_l(&l_pg->head,&l_pg->tail,&l_pg->n_pg)
}
Item inserimentoItem(){
    Item val;
    scanf("%s %s %s %d %d %d %d %d %d",val.personaggio.codice,val.personaggio.nome,val.personaggio.classe,&val.personaggio.statistiche.hp,&val.personaggio.statistiche.mp,&val.personaggio.statistiche.atk,&val.personaggio.statistiche.def,&val.personaggio.statistiche.mag,&val.personaggio.statistiche.spr); // da inserire le altre statistiche
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
void stampaPersonaggio_l(pg personaggio){
    printf("%s %s %s %d %d %d %d %d %d",val.personaggio.codice,val.personaggio.nome,val.personaggio.classe,val.personaggio.statistiche.hp,val.personaggio.statistiche.mp,val.personaggio.statistiche.atk,val.personaggio.statistiche.def,val.personaggio.statistiche.mag,val.personaggio.statistiche.spr);
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
void modificaEqu_l(link head,char *codice,char *nome_equ){
    link x;
    for(x = head;x != NULL && strcmp(x.val.personaggio.codice,codice) != 0 ;x = x->next)
    if(x != NULL){
        //controllo se quell'oggetto non è stato equipaggiato

        
    }else printf("Non è stato trovato alcun personaggio");

}
lista initList(){
    struct tab_l l_pg;
    l_pg.head = NULL;
    l_pg.tail = NULL;
    l_pg.n_pg = 0;
    return pg;
}