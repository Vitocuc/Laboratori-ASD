#include "pg.h"
int main(){
    lista personaggi;
    tabInv_t inventario;
    personaggi = initList();
    caricaPg(personaggi);
    inventario = initInv();
    caricaOggetti(inventario);
    menu(personaggi);
}
vodi menu(lista personaggi,tabInv_t inventario){
}