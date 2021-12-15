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
    x = malloc(sizeof(*x));
    x->val = val; // anche qui
    x->next = h;
    return x;
}
void stampaPersonaggio_l(pg personaggio){//fatto
    int i = 0;
    printf("%s %s %s %d %d %d %d %d %d",personaggio.codice,personaggio.nome,personaggio.classe,personaggio.statistiche.hp,personaggio.statistiche.mp,personaggio.statistiche.atk,personaggio.statistiche.def,personaggio.statistiche.mag,personaggio.statistiche.spr);
    if(personaggio.e->inUso != 0) printf(" Oggetti :");
    for(i = 0;i<personaggio.e->inUso;i++)
        stampaOggetto_i(personaggio.e->vett_equ[i]);
    printf("\n");
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
    printf("Numero di personaggi: %d \n",l_pg->n_pg);
    for( x = l_pg->head ;x != NULL;x = x->next)
        stampaPersonaggio_l(x->val.personaggio);
    
} 
void inserimentoEqu_l(pg personaggio,char *nome,tabInv_t tabInv){//fatto
    int i = 0;
    if(tabInv->n_oggetti == tabInv->max_oggetti){
        printf("Non è possibile inserire oggetti"); 
        return;
    }
    for(i = 0;i<tabInv->n_oggetti && strcmp(nome,tabInv->inv[i].nome) != 0 ;i++);
    if(i<tabInv->n_oggetti){
        personaggio.e->vett_equ[personaggio.e->inUso] = tabInv->inv[i];
        personaggio.e->inUso+=1;
        }
}
void eliminaEqu_l(pg personaggio,char *nome,tabInv_t tabInv){//fatto
    int i = 0,j = 0,k = 0;
    if(personaggio.e->inUso == 0 ){
         printf("Il personaggio non ha un inventario \n");
        return;
    }
    for(i = 0;i<tabInv->n_oggetti && strcmp(nome,tabInv->inv[i].nome) != 0;i++);
    if(i<tabInv->n_oggetti){
                for(j = 0;j<personaggio.e->inUso && strcmp(nome,personaggio.e->vett_equ[j].nome) != 0;j++);
                if(j>=personaggio.e->inUso) printf("Non è stato trovato nessun oggetto corrispondente nell'inventario di questo personaggio \n");
                else {
                    for(k = j;j<personaggio.e->inUso;j++)personaggio.e->vett_equ[k] = personaggio.e->vett_equ[k+1];
                    personaggio.e->inUso--;
                    printf("L'elemento e' stato eliminato con successo \n");
                }  
            }
}
void eliminaEq(lista *l_pg,tabInv_t *tabInv){
    char codice[N],nome[N];
    link x;
    printf("Inserisci il codice del personaggio da cui vuoi eliminare l'oggetto:");
    scanf("%s",codice);
    printf("Inserisci il nome dell'oggetto da eliminare:");
    scanf("%s",nome);
    for(x = (*l_pg)->head;x!= NULL && strcmp(x->val.personaggio.codice,codice) != 0 ;x = x->next);
    if(x != NULL){
        eliminaEqu_l(x->val.personaggio,nome,*tabInv);
        
    }else printf("Non è stato trovato alcun personaggio \n");
}
void inserimentoEqu(lista *l_pg,tabInv_t *tabInv){
    char codice[N],nome[N];
    link x;
    printf("Inserisci il codice del personaggio nel quale vuoi inserire l'oggetto:");
    scanf("%s",codice);
    printf("Inserisci il nome dell'oggetto da inserire:");
    scanf("%s",nome);
    for(x = (*l_pg)->head;x!= NULL && strcmp(x->val.personaggio.codice,codice) != 0 ;x = x->next); 
    if(x != NULL){
        inserimentoEqu_l(x->val.personaggio,nome,*tabInv);
        printf("L'oggetto e' stato inserito \n");
    }else printf("Personaggio non valido \n");
}
void inserimentoPersonaggio_l(link *head,Item val,link *tail,int *n_pg){ // fatto;
    if(*head == NULL){
        *head = *tail = newNode(NULL,val);
    }else{     
        (*tail)->next = newNode(NULL,val);
        *tail = (*tail)->next;
    }
    *n_pg = *n_pg+1;
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
            val.personaggio.e = malloc(sizeof(*val.personaggio.e));
            fscanf(fp,"%s %s %s %d %d %d %d %d %d",val.personaggio.codice,val.personaggio.nome,val.personaggio.classe,&val.personaggio.statistiche.hp,&val.personaggio.statistiche.mp,&val.personaggio.statistiche.atk,&val.personaggio.statistiche.def,&val.personaggio.statistiche.mag,&val.personaggio.statistiche.spr);
            val.personaggio.e->inUso = 0; // mi da il sigseg qui
            val.personaggio.e->vett_equ = malloc(N_ele*sizeof(ogg));
            inserimentoPersonaggio_l(head,val,tail,n);
            i++;
        }
    }
    *n = i;
    fclose(fp);
}
void caricaPg(lista *l_pg){
    caricaPg_l(&(*l_pg)->head,&(*l_pg)->tail,&(*l_pg)->n_pg);
}
Item inserimentoItem(){
    Item val;
    printf("Inserisci codice:");
    scanf("%s",val.personaggio.codice);
    printf("Inserirsci nome: ");
    scanf("%s",val.personaggio.nome);
    printf("Inserisci classe: ");
    scanf("%s",val.personaggio.classe);
    printf("Inserisci hp: ");
    scanf("%d",&val.personaggio.statistiche.hp);
    printf("Inserisci mp: ");
    scanf("%d",&val.personaggio.statistiche.mp);
    printf("Inserisci atk: ");
    scanf("%d",&val.personaggio.statistiche.atk);
    printf("Inserisci def: ");
    scanf("%d",&val.personaggio.statistiche.def);
    printf("Inserisci mag: ");
    scanf("%d",&val.personaggio.statistiche.mag);
    printf("Inserisci spr: ");
    scanf("%d",&val.personaggio.statistiche.spr);
    return val;
}
void cancellaPersonaggio_l(link *head,char *codice,int *n){
    link x,t;
    for(x = *head ;x != NULL && strcmp(x->val.personaggio.codice,codice)!= 0 ;x = x->next);
    if(x != NULL){
        if(x == *head){
            t = x;
            *head = x->next;
            free(t);
        }else{
            t = x;
            (*head)->next = x->next;
            free(t);
        }
        printf("Elemento eliminato con successo \n");
        *n-=1;
    }else{
        printf("Non e' stato trovato alcun personaggio \n");
    }
}
void cancellaPersonaggio(lista l_pg){
    char codice[N]; // non so perchè col * mi dava errore
    printf("Inserisci il codice del personaggio:");
    scanf("%s",codice);
    cancellaPersonaggio_l(&l_pg->head,codice,&l_pg->n_pg);
}
void ricercaPersonaggio_l(link head,char *codice){
    link x;
    for(x = head;x != NULL && strcmp(x->val.personaggio.codice,codice) != 0 ;x = x->next);
    if(x != NULL){
        printf("Il personaggio che stavi cercando e' stato trovato: \n");
        stampaPersonaggio_l(x->val.personaggio);
    }else printf("Non e' stato trovato alcun personaggio \n");

}
void inserimentoPersonaggio(lista *l_pg){ //da finire funzione di inserimento di item
    Item val;
    val = inserimentoItem();
    val.personaggio.e = malloc(sizeof(*val.personaggio.e));
    val.personaggio.e->inUso = 0;
    val.personaggio.e->vett_equ = malloc(N_ele*sizeof(ogg));
    inserimentoPersonaggio_l(&(*l_pg)->head,val,&(*l_pg)->tail,&(*l_pg)->n_pg);
}
void ricercaPersonaggio(lista l_pg){
    char codice[N];
    printf("Inserisci il codice da ricercare:");
    scanf("%s",codice);
    ricercaPersonaggio_l(l_pg->head,codice);
}
void calcolaStatistiche(lista l_pg){
    char codice[N];
    int i = 0;
    link x;
    stat statistiche_tmp;
    printf("Inserisci il codice del personaggfio di cui si vuoel calcolare le statistiche");
    scanf("%s",codice);
    for(x = l_pg->head;x != NULL && strcmp(x->val.personaggio.codice,codice) != 0;x = x->next);
    if(x != NULL){
        statistiche_tmp.hp = x->val.personaggio.statistiche.hp;
        statistiche_tmp.def = x->val.personaggio.statistiche.def;
        statistiche_tmp.atk = x->val.personaggio.statistiche.atk;
        statistiche_tmp.mag = x->val.personaggio.statistiche.mag;
        statistiche_tmp.mp = x->val.personaggio.statistiche.mp;
        statistiche_tmp.spr = x->val.personaggio.statistiche.spr;
        for(i = 0;i<x->val.personaggio.e->inUso;i++){
            statistiche_tmp.hp += x->val.personaggio.e->vett_equ[i].modificatore.hp;
            statistiche_tmp.def += x->val.personaggio.e->vett_equ[i].modificatore.def;
            statistiche_tmp.atk += x->val.personaggio.e->vett_equ[i].modificatore.atk;
            statistiche_tmp.mag += x->val.personaggio.e->vett_equ[i].modificatore.mag;
            statistiche_tmp.mp += x->val.personaggio.e->vett_equ[i].modificatore.mp;
            statistiche_tmp.spr += x->val.personaggio.e->vett_equ[i].modificatore.spr;
        }
        printf("Statistiche aggiornate ->");
        if(statistiche_tmp.hp< 0) printf("Hp : 0");
         else printf("Hp : %d",statistiche_tmp.hp);
        if(statistiche_tmp.mp< 0) printf("Mp : 0");
        else printf("Mp : %d",statistiche_tmp.mp);
        if(statistiche_tmp.atk< 0) printf("Atk : 0");
        else printf("Atk : %d",statistiche_tmp.atk);
        if(statistiche_tmp.def< 0) printf("Def : 0");
        else printf("Def : %d",statistiche_tmp.def);
        if(statistiche_tmp.mag< 0) printf("Mag : 0");
        else printf("Mag : %d",statistiche_tmp.mag);
        if(statistiche_tmp.spr< 0) printf("Spr : 0");
        else printf("Spr : %d",statistiche_tmp.spr);
        printf("\n");
    }else printf("Non è stato trovato il personaggio \n");
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
void liberaPersonaggi(lista l_pg){
    link x,p;
    for(x = l_pg->head->next,p = l_pg->head;x!= l_pg->tail;p = x,x = x->next){
        free(p->val.personaggio.e->vett_equ);
        free(p->val.personaggio.e);
        free(p);
    }
    free(l_pg->tail->val.personaggio.e->vett_equ);
    free(l_pg->tail->val.personaggio.e);
    free(l_pg->tail);
    free(l_pg);
}