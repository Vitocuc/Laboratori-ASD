#include "st.h"
struct symboltable{
    elab *a;
    int maxN;
    int size;
};
static elab elabSetVoid(){
    elab c;
    strcpy(c.id_elab,"");
    strcpy(c.id_rete,"");
    return c;
}
ST STinit(int maxN){
    ST st = malloc(sizeof(*st));
    int i;
    st->a = malloc(maxN*sizeof(elab));
    for(i = 0;i<maxN;i++){
        st->a[i] = elabSetVoid();
    }
    st->maxN = maxN;
    st->size = 0;
    return st;
}
void STfree(ST st){
    free(st->a);
    free(st);
}
int STcount(ST st){
    return st->size;
}
char *Keyget(elab e){
    return e.id_elab;
}
int Keycmp(char *s1,char *s2){
    return strcmp(s1,s2);
}
void STinsert(ST st,elab e){ // inserimento ordinato in una tabella di simboli
    int i = st->size++;
    if(st->size > st->maxN){
        st->a = realloc(st->a,2*st->maxN*sizeof(elab));
        if(st->a == NULL) return;
        st->maxN = 2*st->maxN;
    }
    while((i>0) && Keycmp(Keyget(e),Keyget(st->a[i-1])) == -1){
        st->a[i] = st->a[i-1];
        i--;
    }
    st->a[i] = e;
}
static elab searchR(ST st,int l,int r,char* key){ // ricerca ricorsiva
    int m = (l+r)/2;
    if(l>r) return elabSetVoid();
    if(Keycmp(key,Keyget(st->a[m])) == 0) return st->a[m];
    if(l == r) return elabSetVoid();
    if(Keycmp(key,Keyget(st->a[m])) == -1) return searchR(st,l,m-1,key);
    else return searchR(st,m+1,r,key);
}
elab STsearch(ST st,char *key){
    elab e = searchR(st,0,st->size-1,key);
    return e;
}
void STdelete(ST st,char *key){
    int h = getIndex(st,key);
    if(h != -1){
        st->a[h] = elabSetVoid();
        st->size--;
    }
}
elab STselect(ST st, int i){
    elab e = st->a[i];
    return e;
}
void STdisplay(ST st){
    int i = 0;
    for(i = 0;i<st->size;i++){
        printf("Nome: %s %s",st->a[i].id_elab,st->a[i].id_rete);
        printf("Indice: %d",i);
    }
}
int getIndexR(ST st,int l,int r,char *key){
    int m = (l+r)/2;
    if(l>r) return -1;
    if(Keycmp(key,Keyget(st->a[m])) == 0) return m;
    if(l == r) -1;
    if(Keycmp(key,Keyget(st->a[m])) == -1) return getIndexR(st,l,m-1,key);
    else return getIndexR(st,m+1,r,key);
}
int getIndex(ST st,char *key){
    return getIndexR(st,0,(st->size-1),key);
}