#include <stdio.h>

typedef struct
{
    int data[100][500];
    int n;
} Graph;

void makenullGraph(Graph *G, int n)
{
    G->n = n;
    int i, j;
    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
        {
            G->data[i][j] = 0;
        }
    }
}

void addEdge(Graph *G, int x, int y, int ts)
{
    G->data[x][y] = ts;
}

int mark[100];
int pi[100];

void prim(Graph *G, int x)
{
    int i, min_pi, k, position;
    for (i = 1; i <= G->n; i++)
    {
        pi[i] = 9999;
        mark[i] = 0;
    }
    pi[x] = 0;
    for (i = 1; i <= G->n; i++)
    {
        min_pi = 9999;
        position = -1;
        for (k = 1; k <= G->n; k++)
        {
            if (pi[k] < min_pi && mark[k] == 0)
            {
                min_pi = pi[k];
                position = k;
            }
        }
        if (position == -1)
            break;

        mark[position] = 1;

        for (k = 1; k <= G->n; k++)
        {
            if (mark[k] == 0 && G->data[position][k] != 0)
            {
                if (pi[k] > G->data[position][k])
                    pi[k] = G->data[position][k];
            }
        }
    }
}

int main()
{
    freopen("data.txt", "r", stdin);
    Graph G;
    int n, m, x, y, ts, i, j, sum = 0;
    scanf("%d%d", &n, &m);
    makenullGraph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &x, &y, &ts);
        addEdge(&G, x, y, ts);
    }

    prim(&G, 1);
    for (i = 1; i <= n; i++)
    {
        sum += pi[i];
    }
    printf("%d\n", sum);

    for (i = 1; i <= G.n; i++)
    {

        for (j = 1; j <= G.n; j++)
        {
            if (G.data[i][j] != 0 && G.data[i][j] == pi[i + 1])
                printf("%d %d %d\n", i, j, G.data[i][j]);
        }
    }
}