#include <stdio.h>
#include <stdlib.h>
#include "pg.h"
int main(){
    lista personaggi;
    tabInv_t inventario;
    /*
    personaggi = initList();
    caricaPg(personaggi);*/
    //stampaPersonaggi(personaggi);
    inventario = initInv();
    caricaOggetti(inventario);
    stampaOggetti(inventario);
    ricercaOggetto(inventario);
    /*
    menu(personaggi,inventario);*/
    return 0;
}