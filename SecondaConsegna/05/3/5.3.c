#include "pg.h"
void menu(lista personaggi,tabInv_t inventario);
int main(){
    lista personaggi;
    tabInv_t inventario;
    personaggi = initList();
    caricaPg(personaggi);
    stampaPersonaggi(personaggi);
    /*
    inventario = initInv();
    caricaOggetti(inventario);
    menu(personaggi);*/
}