#include <stdio.h>
#include "Graph.h"
int main(int argc,char **argv){
    if(argc>2) return 1;
    Graph G;
    G = GraphLoad(argv[1]);//carico il grafo insieme ad una tabella di simboli

}