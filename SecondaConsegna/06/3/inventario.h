#ifndef OGG
#define OGG 
#define N 51
#define N_ele 8
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
tabInv_t initInv();
void stampaOggetti(tabInv_t tabInv);
void caricaOggetti(tabInv_t *tabInv);
void liberaInventario(tabInv_t tabInv);
void stampaOggetto_i(ogg oggetto);
void stampaOggetto(tabInv_t tabInv);
void ricercaOggetto_i(tabInv_t tabInv,char *nome);
void ricercaOggetto(tabInv_t tabInv);
#endif