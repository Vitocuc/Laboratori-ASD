#ifndef STable
#define STable
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 31
typedef struct symboltable *ST;
typedef struct{
    char id_elab[MAXLEN];
    char id_rete[MAXLEN];
}elab;
typedef struct{
    elab elaboratore;
}ItemSt;
ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
char *Keyget(elab e);
int Keycmp(char *s1,char *s2);
void STinsert(ST st,elab e);
elab STsearch(ST st,char *key);
void STdelete(ST st,char *key);
elab STselect(ST st, int i);
void STdisplay(ST st);
int getIndex(ST st,char *key);
#endif