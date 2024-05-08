#include <stdio.h>
#define oo 99999

typedef struct
{
    int data[100][500];
    int n;
} Graph;

void initGraph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
        {
            G->data[i][j] = -1;
        }
    }
}

void addEdge(Graph *G, int u, int v, int ts)
{
    G->data[u][v] = ts;
    // G->data[v][u] = ts;
}

int mark[100];
int parent[100];
int pi[100];
int cnt[100];

void dijkstra(Graph *G, int x)
{
    int i, j, min_pi, position;
    for (i = 1; i <= G->n; i++)
    {
        parent[i] = 0;
        pi[i] = oo;
        mark[i] = 0;
    }
    pi[x] = 0;
    parent[x] = -1;
    cnt[x] = 1;

    for (i = 1; i <= G->n; i++)
    {
        min_pi = oo;
        for (j = 1; j <= G->n; j++)
        {
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                min_pi = pi[j];
                position = j;
            }
        }
        mark[position] = 1;
        for (j = 1; j <= G->n; j++)
        {
            if (mark[j] == 0 && G->data[position][j] != -1)
            {
                if (pi[j] > pi[position] + G->data[position][j])
                {
                    pi[j] = pi[position] + G->data[position][j];
                    parent[j] = position;
                    cnt[j] = cnt[position];
                }
                else if (pi[j] == pi[position] + G->data[position][j])
                {
                    parent[j] = position;
                    cnt[j] += cnt[position];
                }
            }
        }
    }
}

int main()
{
    freopen("data.txt", "r", stdin);
    Graph G;
    int n, m, i, u, v, ts;
    scanf("%d%d", &n, &m);
    initGraph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &ts);
        addEdge(&G, u, v, ts);
    }
    dijkstra(&G, 1);
    printf("%d %d", pi[n], cnt[n]);
    return 0;
}