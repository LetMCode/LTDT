#include <stdio.h>
typedef struct
{
    int x, y, ts;
} Edge;

typedef struct
{
    Edge data[100];
    int n, m;
} Graph;

void makenullGraph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
}

void addEdge(Graph *G, int x, int y, int ts)
{
    G->data[G->m].x = x;
    G->data[G->m].y = y;
    G->data[G->m].ts = ts;
    G->m++;
}

void swap(Edge *a, Edge *b)
{
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(Graph *G)
{
    int i, j;
    for (i = 1; i <= G->m; i++)
    {
        for (j = G->m - 1; j >= i; j--)
        {
            if (G->data[j].ts < G->data[j - 1].ts)
                swap(&G->data[j], &G->data[j - 1]);
        }
    }
}

int findRoot(int parent[], int u)
{
    while (u != parent[u])
    {
        u = parent[u];
    }
    return u;
}

void kruskal(Graph *G, Graph *T)
{
    makenullGraph(T, G->n);
    int parent[100];
    int first, last, u, v, ts, i, sum = 0;
    for (i = 1; i <= G->n; i++)
    {
        parent[i] = i;
    }
    for (i = 0; i < G->m; i++)
    {
        u = G->data[i].x;
        v = G->data[i].y;
        ts = G->data[i].ts;
        first = findRoot(parent, u);
        last = findRoot(parent, v);
        if (first != last)
        {
            if (u < v)
                addEdge(T, u, v, ts);
            else
                addEdge(T, v, u, ts);
            sum += ts;
            parent[last] = first;
        }
    }
    printf("%d\n", sum);
}

int main()
{
    freopen("data.txt", "r", stdin);
    Graph G;
    int n, m, x, y, ts, i;
    scanf("%d%d", &n, &m);
    makenullGraph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &x, &y, &ts);
        addEdge(&G, x, y, ts);
    }
    bubbleSort(&G);

    Graph T;
    kruskal(&G, &T);
    for (i = 0; i < T.m; i++)
    {
        printf("%d %d %d\n", T.data[i].x, T.data[i].y, T.data[i].ts);
    }
}