#define N 51
#define N_ele 8
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
    stat modificatori;
}ogg;
typedef struct{
    ogg oggetti[N_ele];
}inv;
// lettura usando il controllo
void caricaOggetti(){

}
void aggiungiOggetto(){

}
void eliminaOggetto(){
    
}