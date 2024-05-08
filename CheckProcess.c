#include <stdio.h>

// Grap- matran dinh
typedef struct
{
    int data[100][500];
    int n;
} Graph;

void makeNullGraph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
        {
            G->data[i][j] = 0;
        }
    }
}

void addEdge(Graph *G, int x, int y)
{
    G->data[x][y] = 1;
    // G->data[y][x] = 1;
}

int mark[100];
int parent[100];
int key = 0;

void DFS(Graph *G, int x)
{

    mark[x] = 1;
    int i;
    for (i = 1; i <= G->n; i++)
    {
        if (G->data[x][i] != 0)
        {
            if (mark[i] == 0)
                DFS(G, i);
            else if (mark[i] == 1)
            {
                key = 1;
            }
        }
    }
    mark[x] = 2;
}

int main()
{
    freopen("data.txt", "r", stdin);
    Graph G;
    int i, n, m, u, v;
    scanf("%d%d", &n, &m);
    makeNullGraph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        addEdge(&G, u, v);
    }

    for (i = 1; i <= n; i++)
    {
        mark[i] = 0;
    }
    key = 0;
    for (i = 1; i <= n; i++)
    {
        if (mark[i] == 0)
            DFS(&G, i);
    }
    if (key == 1)
        printf("NO");
    else
        printf("YES");
    return 0;
}