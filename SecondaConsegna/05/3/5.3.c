#include "pg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{
    caricaPgFile,caricaInv,aggiungiPg,eliminaPg,aggiungiOgg,eliminaOgg,calcolaStat,fine,err
}comando_c;
comando_c scelta();
void menu(lista *personaggi,tabInv_t *inventario);
int main(){
    lista personaggi;
    tabInv_t inventario;
    personaggi = initList();
    inventario = initInv();
    menu(&personaggi,&inventario);
    stampaPersonaggi(personaggi);
    return 0;
}
comando_c scelta(){
    char codici[err][30]={"caricaPgFile","caricaInv","aggiungiPg","eliminaPg","aggiungiOgg","eliminaOgg","calcolaStat","fine"};
    char s[30];
    comando_c cont = caricaPgFile;
    int i = 0;
    printf("Inserisci caricaPgFile/caricaInv/aggiungiPg/eliminaPg/aggiungiOgg/eliminaOgg/calcolaStat/fine:");
    scanf("%s",s);
    for(i = 0;cont<err && strcmp(s,codici[i])!=0 ;i++){
        cont++;
    }
    return cont;
}
void menu(lista *personaggi,tabInv_t *inventario){
    int stop = 0;
    comando_c c;
    while(stop == 0){
        c = scelta();
        switch(c){
            case caricaPgFile:
                caricaPg(personaggi);
                stampaPersonaggi(*personaggi);
                break;
            case caricaInv:
                caricaOggetti(inventario);
                stampaOggetti(*inventario);
                break;
            case aggiungiPg:
                inserimentoPersonaggio(personaggi);
                stampaPersonaggi(*personaggi);
                break;
            case eliminaPg:
                cancellaPersonaggio(personaggi);
                stampaPersonaggi(*personaggi);
                break;
            case aggiungiOgg:
                inserimentoEqu(personaggi,inventario);
                stampaPersonaggi(*personaggi);
                break;
            case eliminaOgg:
                eliminaEq(personaggi,inventario);
                stampaPersonaggi(*personaggi);
                break;
            case calcolaStat:
                calcolaStatistiche(*personaggi);
                stampaPersonaggi(*personaggi);
                break;
            case fine: 
                stop = 1;
                break;
            default: printf("Inserimento errato,riprovare \n");
                break;
        }
    }
}