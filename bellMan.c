#include <stdio.h>
#define oo 99999

typedef struct
{
    int x, y, ts;
} Edge;

typedef struct
{
    Edge data[100];
    int n, m;
} Graph;

void initGraph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
}

void addEdge(Graph *G, int u, int v, int ts)
{
    G->data[G->m].x = u;
    G->data[G->m].y = v;
    G->data[G->m].ts = ts;
    G->m++;
}

int parent[100];
int pi[100];

void bellMan(Graph *G, int s)
{
    int u, v, it, ts, k;
    for (u = 1; u <= G->n; u++)
    {
        pi[u] = oo;
    }

    pi[s] = 0;      // chiều dài đường đi ngắn nhất từ s đến chính nó bằng 0
    parent[s] = -1; // trước đỉnh s không có đỉnh nào cả

    // Lặp n-1 lần
    for (it = 1; it < G->n; it++)
    {
        // 3. Cập nhật pi và parent của các đỉnh kề của v (nếu thoả)
        for (v = 0; v < G->m; v++)
        {
            u = G->data[v].x;
            k = G->data[v].y;
            ts = G->data[v].ts;
            if (pi[u] == oo)
                continue;
            if (pi[u] + ts < pi[k])
            {
                pi[k] = pi[u] + ts;
                parent[k] = u;
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
    int x, y;
    scanf("%d%d", &x, &y);
    bellMan(&G, x);
    // printf("%d", pi[y]);
    int cr = y, k = 0, d[100];
    while (cr != -1)
    {
        d[k] = cr;
        k++;
        cr = parent[cr];
    }
    for (i = k - 1; i > 0; i--)
    {
        printf("%d -> ", d[i]);
    }
    printf("%d", d[0]);
    return 0;
}