#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 51
typedef struct inventario *tabInv_t;
typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat;
typedef struct{
    char nome[N];
    char tipologia[N];
    stat modificatore;
}ogg;
struct inventario{
    ogg *inv;
    int n_oggetti;
    int max_oggetti;
};
tabInv_t initInv(){
    tabInv_t tabInv;
    tabInv->n_oggetti = 0;
    tabInv->max_oggetti = 0;
    return tabInv;
}
void caricaOggetti(tabInv_t tabInv){
    FILE *fp;
    int n_oggetti,i = 0;
    if((fp = fopen("inventario.txt","r") ) == NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    fscanf(fp,"%d",&tabInv->n_oggetti);
    tabInv->inv = malloc(tabInv->n_oggetti*sizeof(ogg));
    while(i<tabInv->n_oggetti){
        fscanf(fp,"%s %s %d %d %d %d %d %d",tabInv->inv[i].nome,tabInv->inv[i]->tipologia,&tabInv->inv[i].modificatore.hp,&tabInv->inv[i].modificatore.mp,&tabInv->inv[i].modificatore.atk,&tabInv->inv[i].modificatore.def,&tabInv->inv[i].modificatore.mag,&tabInv->inv[i].modificatore.spr);
        i++;
    }
    fclose(fp);
}
void stampaOggetto_i(ogg oggetto){
    printf("%s %s %d %d %d %d %d %d",oggetto.nome,oggetto.tipologia,oggetto.modificatore.hp,oggetto.modificatore.mp,oggetto.modificatore.atk,oggetto.modificatore.def,oggetto.modificatore.mag,oggetto.modificatore.spr);
}
void stampaOggetto(tabInv_t tabInv){
    char *nome;
    printf("Inserisci il nome dell'oggetto di cui vuoi stampare i dettagli:");
    scanf("%s",nome);
    int i = 0;
    for(i = 0;i<tabInv->n_oggetti;i++){
        if(strcmp(nome,tabInv->inv[i].nome) == 0){
            printf("L'oggetto è stato trovato");
            stampaOggetto_i(tabInv->inv[i]);
        }
    }
    
}
void ricercaOggetto_i(tabInv_t tabInv,char *nome){
    int i = 0;
    for(i = 0;i<tabInv->n_oggetti;i++){
        if(strcmp(nome,tabInv->inv[i].nome) == 0){
            printf("L'oggetto è stato trovato");
        }
    }
}
void ricercaOggetto(tabInv_t tabInv){
    char *nome;
    printf("Inserisci il nome dell'oggetto da ricercare");
    scanf("%s",nome);
    ricercaOggetto_i(tabInv,nome);

}

