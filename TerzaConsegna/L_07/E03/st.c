#include <st.h>
typedef struct{
    elab elaboratore;
}ItemSt;
struct symboltable{
    ItemSt *a;
    int maxN;
    int size;
};
static ItemSt ItemSetVoid(){
    ItemSt c;
    strcpy(c.elaboratore.id_elab,"");
    strcpy(c.elaboratore.id_rete,"");
    return c;
}
ST STinit(int maxN){
    ST st = malloc(sizeof(*st));
    int i;
    st->a = malloc(maxN*sizeof(ItemSt));
    for(i = 0;i<maxN;i++){
        st->a[i] = ItemSetVoid();
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
    return st->count;
}
char *Keyget(elab e){
    return e.id_elab;
}
int Keycmp(char *s1,char *s2){
    return strcmp(s1,s2);
}
void STinsert(ST st,ItemSt e){ // inserimento ordinato in una tabella di simboli
    int i = st->size++;
    if(st->size > st->maxN){
        st->a = realloc(st->a,2*st->maxN*sizeof(ItemSt));
        if(st->a == NULL) return;
        st->maxN = 2*st->maxN;
    }
    while((i>0) && Keycmp(Keyget(e.elaboratore),Keyget(st->a[i-1])) == -1){
        st->a[i] = st->a[i-1];
        i--;
    }
    st->a[i] = e;
}
static ItemSt searchR(ST st,int l,int r,char* key){ // ricerca ricorsiva
    int m = (l+r)/2;
    if(l>r) return ItemSetVoid();
    if(Keycmp(key,Keyget(st->a[m])) == 0) return st->a[m];
    if(l == r) return ItemSetVoid();
    if(Keycmp(key,Keyget(st->a[m])) == -1) return searchR(st,l,m-1,key);
    else return searchR(st,m+1,r,key);
}
static ItemSt STsearch(ST st,char *key){
    return searchR(st,0,st->size-1,key);
}
void STdelete(ST st,char *key){
    int h = getIndex(st,0,st->size--,key);
    if(h != -1){
        st->a[h] = ItemSetVoid();
        st->size--;
    }
}
static ItemSt STselect(ST st, int i){
    return st->a[i];
}
void STdisplay(ST st){
    int i = 0;
    for(i = 0;i<st->size;i++){
        printf("Nome: %s %s",st->a[i].elaboratore.id_elab,st->a[i].elaboratore.id_rete);
        printf("Indice: %d",i);
    }
}
int getIndex(ST st,char *key){
    return getIndexR(st,0,(st->size-1),key);
}
int getIndexR(ST st,int l,int r,char *key){
    int m = (l+r)/2;
    if(l>r) return -1;
    if(Keycmp(key,Keyget(st->a[m])) == 0) return m;
    if(l == r) -1
    if(Keycmp(key,Keyget(st->a[m])) == -1) return getIndexR(st,l,m-1,key);
    else return getIndexR(st,m+1,r,key);

}