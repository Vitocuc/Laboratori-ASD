#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 51
typedef struct{
  int gg;
  int mm;
  int aaaa;
}date;
typedef struct node *link;
typedef struct{
  char codice[N];
  char nome[N];
  char cognome[N];
  date dataN;
  char via[N];
  char citta[N];
  int cap;
}Item;
struct node{
  Item a;
  link next;
};
typedef enum{
    tastiera,file,ricerca,canc1,canc2,stampaf,fine,err
}comando_c;
comando_c scelta();
int checkData(date data1,date data2);
void stampaLista(link head);
link newNode(Item val,link h);
Item ricercaCodice(link *head,char *key);
link insertSorted(link head,Item val);
link leggiFile(char *s,link head);
void stampaItem(Item val);
link menu(link head);
link insertNode(link head,Item val);
link insertFile(link head,char *s);
Item cancellazione1(link *head, char *key);
Item cancellazione2(link *head,date data1,date data2);
void liberaLista(link head);
void stampafile(link head);
date inserimentoData();
Item inserimentoItem();
//MAIN
int main(){
  link head = NULL;
  head = leggiFile("anag1.txt",head);
  stampaLista(head);
  head = menu(head);
  stampaLista(head);
  liberaLista(head);
}
//Funzioni
date inserimentoData(){
  date data;
  printf("Inserisci giorno:");
  scanf("%d",&data.gg);
  printf("Inserisci mese:");
  scanf("%d",&data.mm);
  printf("Inserisci anno:");
  scanf("%d",&data.aaaa);
  return data;
}
link insertSorted(link head,Item val){
  link x,p;
  if(head == NULL || checkData(val.dataN,head->a.dataN)>0) return newNode(val,head);
  for(x = head->next ,p= head;x != NULL && checkData(val.dataN,x->a.dataN)<0;p = x,x = x->next); // esegue anche l'ultimo nodo quindi ne consente la modifica(inseirmento in lista in  maniera ordinata)
  p->next = newNode(val,p->next);
  return head;
}
link leggiFile(char *s,link head){
  link x = NULL;
  link p = NULL;
  FILE *fp;
  Item val;
  if((fp = fopen(s,"r")) == NULL){
    printf("Errore nell'apertura del file'");
    exit(1);
  }
  while(!feof(fp)){
    fscanf(fp,"%s%s%s%d/%d/%d%s%s%d",val.codice,val.nome,val.cognome,&val.dataN.gg,&val.dataN.mm,&val.dataN.aaaa,val.via,val.citta,&val.cap);
    if (!feof(fp))
        head = insertSorted(head,val);
  }
  fclose(fp);
  return head;
}
int checkData(date data1,date data2){
  int diff = data1.aaaa-data2.aaaa;
  if(diff != 0 ) return diff;
  diff = data1.mm-data2.mm;
  if(diff != 0 ) return diff;
  diff = data1.gg-data2.gg;
  if(diff != 0 ) return diff;
  return 0;
}
void stampaLista(link head){
  link x;
  for(x = head;x != NULL;x=x->next) printf("%s %s %s %d/%d/%d %s %s %d \n",x->a.codice,x->a.nome,x->a.cognome,x->a.dataN.gg,x->a.dataN.mm,x->a.dataN.aaaa,x->a.via,x->a.citta,x->a.cap);
}
link newNode(Item val,link h){
  link x = malloc(sizeof *x);
  x->a = val;
  x->next = h;
  return x;
}
link menu(link head){
  char codice[N];
  date data1,data2;
  Item val,t;
  int stop = 0,flag = 0;
  comando_c c;
  while(stop == 0){
    c = scelta();
    switch(c){
        case tastiera:
            val = inserimentoItem();
            head = insertNode(head,val);
            stampaLista(head);
            break;
        case file:
            head = insertFile(head,"anag2.txt");
            stampaLista(head);
            break;
        case ricerca:
            printf("Inserisci il codice da ricercare:");
            scanf("%s",codice);
            t = ricercaCodice(&head,codice);
            stampaItem(t);
            break;
        case canc1:
            printf("Inserisci il codice da cancellare:");
            scanf("%s",codice);
            t = cancellazione1(&head,codice);
            stampaItem(t);
            stampaLista(head);
            break;
        case canc2:
            printf("Data1\n");
            data1 = inserimentoData();
            printf("Data2\n");
            data2 = inserimentoData();
            flag = checkData(data1,data2);
            do{
                t = cancellazione2(&head,data1,data2);
                stampaItem(t);
            }while(strcmp(t.codice,"") != 0);
            break;
        case stampaf:
            stampafile(head);
            break;
        case fine: 
            stop = 1;
            break;
        default: printf("Inserimento errato,riprovare \n");
            break;
    }
  }
}
void stampafile(link head){
    link x;
    FILE *fp;
    if((fp = fopen("log.txt","w"))== NULL){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    for(x = head;x != NULL;x = x->next) fprintf(fp,"%s %s %s %d/%d/%d %s %s %d \n",x->a.codice,x->a.nome,x->a.cognome,x->a.dataN.gg,x->a.dataN.mm,x->a.dataN.aaaa,x->a.via,x->a.citta,x->a.citta);
    fclose(fp);
}
void stampaItem(Item val){
    if(strcmp(val.codice,"") == 0) printf("Non esistono piu' nodi con questo codice o data\n");
    else printf("%s %s %s %d/%d/%d %s %s %d \n",val.codice,val.nome,val.cognome,val.dataN.gg,val.dataN.mm,val.dataN.aaaa,val.via,val.citta,val.cap);
}
link insertNode(link head,Item val){
  head = insertSorted(head,val);
  return head;
}
link insertFile(link head,char *s){
  head = leggiFile(s,head);
  return head;
}
Item ricercaCodice(link *head,char *key){
  link *x;
  link t;
  Item tmp;
  strcpy(tmp.codice,"");
  for(x = head; (*x) != NULL ;x = &((*x)->next)){
    if(strcmp(key,(*x)->a.codice) == 0){
      t = *x;
      *x = (*x)->next;
      tmp = t->a;
      break;
    }
  }
  return tmp;
}
Item cancellazione1(link *head, char *key){
  link *x;
  link t;
  Item tmp;
  strcpy(tmp.codice,"");
  for(x = head;(*x) != NULL;x = &((*x)->next)){
    if(strcmp(key,(*x)->a.codice) == 0){
      t = *x;
      *x = (*x)->next;
      tmp = t->a;
      free(t);
      break;
    }  
  }
  return tmp;
}
Item cancellazione2(link *head,date data1,date data2){
  link *x,t;
  Item tmp;
  int a,b;
  //si assume data1>=data2
  strcpy(tmp.codice,"");
  for(x = head;(*x) != NULL;x = &((*x)->next)){
    if((checkData(data1,(*x)->a.dataN)>=0) && (checkData(data2,(*x)->a.dataN)<=0 )){
      t = *x;
      *x = (*x)->next;
      tmp = t->a;
      free(t);
      break;
    }  
  }
  return tmp;
}
void liberaLista(link head){
    link x = NULL, p = NULL;
    for(x = head;x->next != NULL;x=p){
        p = x->next;
        free(x);
    } 
}
comando_c scelta(){
    char codici[err][20]={"tastiera","file","ricerca","canc1","canc2","stampafile","fine"};
    char s[20];
    comando_c cont = tastiera;
    int i = 0;
    printf("Inserisci tastiera/file/ricerca/canc1/canc2/stampafile/fine:");
    scanf("%s",s);
    for(i = 0;cont<err && strcmp(s,codici[i])!=0 ;i++){
        cont++;
    }
    return cont;
}
Item inserimentoItem(){
  Item val;
    printf("Inserisci il codice: ");
    scanf("%s",val.codice);
    printf("Inserisci il nome: ");
    scanf("%s",val.nome);
    printf("Inserisci il cognome: ");
    scanf("%s",val.cognome);
    printf("Inserisci il giorno della data di nascita: ");
    scanf("%d",&val.dataN.gg);
    printf("Inserisci il mese della data di nascita: ");
    scanf("%d",&val.dataN.mm);
    printf("Inserisci l'anno della data di nascita: ");
    scanf("%d",&val.dataN.aaaa);
    printf("Inserisci la via: ");
    scanf("%s",val.via);
    printf("Inserisci la citta': ");
    scanf("%s",val.citta);
    printf("Inserisci il CAP: ");
    scanf("%d",&val.cap);
    return val;
}