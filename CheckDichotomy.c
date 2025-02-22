

#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define maxe 50
#define idx 100
int n,m;//Bien toan cuc luu so dinh va so cung
typedef struct{
    int matrix[maxv][maxe];
    int n,m;//
}Graph;
//LIST
typedef struct{
    int data[idx];
    int size;
}List;
//makenull
void makenullList(List *l){
    l->size=0;
}
void pushList(List *l, int element){
    l->data[l->size]=element;
    l->size++;
}
int getList(List *l, int index){
    return l->data[index];
}
//khoi tao
void initGraph(Graph *g){
    g->n=n;
    g->m=m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            g->matrix[i][j]=0;
        }
    }
}
///Them cung e = (x,y)
void addGraph(Graph *g, int e, int x, int y){
    g->matrix[x][e]=1;
    g->matrix[y][e]=1;
}
//print
void printGraph(Graph g){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            printf("%d ",g.matrix[i][j]);
        }
        printf("\n");
    }
}
bool adjacent(Graph *g, int x, int y){
    for(int e=1;e<=m;e++){
        if(g->matrix[x][e]==1 && g->matrix[y][e]==1){
            return true;
        }
    }
    return false;
}
List neighbors(Graph* G, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=G->n;i++){
        if(i!=x){
            for(int j=1;j<=G->m;j++){
                if(G->matrix[i][j]==1 && G->matrix[x][j]==1){
                    pushList(&L, i);
                    break;
                }
            }   
        }
    }
    return L;
}
int color[maxv];
int fail;
void colorize(Graph *g, int x, int c){
    if(color[x]==-1){
        color[x]=c;
        List L = neighbors(g,x);
        for(int j=0;j<L.size;j++){
            int v = getList(&L,j);
            colorize(g,v,!c);
        }
    }
    else{
        if(color[x]!=c) fail=1;
    }
}
int is_bigraph(Graph *g){
    for(int i=1;i<=n;i++){
        color[i]=-1;
    }
    fail=0;
    colorize(g,1,0);
    return !fail;
}
int main(){
    Graph g;
    int u,v;
    scanf("%d%d",&n,&m);
    initGraph(&g);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        addGraph(&g,i,u,v);
    }
    if(is_bigraph(&g)){
        for(int i=1;i<=n;i++){
            if(!color[i]){
                printf("%d ",i);
            }
        }
        printf("\n");
        for(int i=1;i<=n;i++){
            if(color[i]){
                printf("%d ",i);
            }
        }
    }
    else printf("IMPOSSIBLE");
    return 0;   
}