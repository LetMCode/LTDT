#include <stdio.h>
typedef struct
{
    int data[100];
    int size;
} List;

void makenullList(List *L)
{
    L->size = 0;
}

void pushList(List *L, int x)
{
    L->data[L->size] = x;
    L->size++;
}

int getList(List *L, int i)
{
    return L->data[i - 1];
}

void popList(List *L)
{
    L->size--;
}

int emptyList(List *L)
{
    return L->size == 0;
}

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

void addEdge(Graph *G, int u, int v)
{
    G->data[u][v] = 1;
}

List neighbors(Graph *G, int u)
{
    int i;
    List L;
    makenullList(&L);
    for (i = 1; i <= G->n; i++)
    {
        if (G->data[u][i] != 0)
            pushList(&L, i);
    }
    return L;
}

void copyList(List *L1, List *L2)
{
    makenullList(L1);
    int i;
    for (i = 1; i <= L2->size; i++)
    {
        int u = getList(L2, i);
        pushList(L1, u);
    }
}

int degreeInput(Graph *G, int u)
{
    int i, count = 0;
    for (i = 1; i <= G->n; i++)
    {
        if (G->data[i][u] != 0)
            count++;
    }
    return count;
}

int degreeOutput(Graph *G, int u)
{
    int i, count = 0;
    for (i = 1; i <= G->n; i++)
    {
        if (G->data[u][i] != 0)
            count++;
    }
    return count;
}

int rank[100], k = 0;
List L1, L2;
int d[100];

List ranking(Graph *G)
{
    List rs;
    makenullList(&rs);

    int i, j;
    makenullList(&L1);
    for (i = 1; i <= G->n; i++)
    {
        d[i] = degreeInput(G, i);
        if (d[i] == 0)
            pushList(&L1, i);
    }
    while (!emptyList(&L1))
    {
        makenullList(&L2);
        for (i = 1; i <= L1.size; i++)
        {
            int u = getList(&L1, i);
            rank[u] = k;
            k++;
            pushList(&rs, u);
            List L = neighbors(G, u);
            for (j = 1; j <= L.size; j++)
            {
                int k = getList(&L, j);
                d[k]--;
                if (d[k] == 0)
                    pushList(&L2, k);
            }
        }
        copyList(&L1, &L2);
    }
    return rs;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    freopen("data.txt", "r", stdin);
    Graph G;
    int n, time[100], v, i, j;
    scanf("%d", &n);
    makenullGraph(&G, n + 2);
    time[n + 1] = 0;
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &time[i]);
        do
        {
            scanf("%d", &v);
            if (v > 0)
                addEdge(&G, v, i);
        } while (v > 0);
    }

    for (i = 1; i <= n; i++)
    {
        if (degreeInput(&G, i) == 0)
        {
            addEdge(&G, n + 1, i);
        }
    }

    for (i = 1; i <= n; i++)
    {
        if (degreeOutput(&G, i) == 0)
        {
            addEdge(&G, i, n + 2);
        }
    }
    List L = ranking(&G);
    int t[100], T[100];

    t[n + 1] = 0;
    for (i = 2; i <= L.size; i++)
    {
        int u = getList(&L, i);
        // printf("%d", u);
        t[u] = -1;
        for (j = 1; j <= G.n; j++)
        {
            if (G.data[j][u] != 0)
                t[u] = max(t[u], t[j] + time[j]);
        }
    }

    T[n + 2] = t[n + 2];
    for (i = L.size - 1; i >= 1; i--)
    {
        int u = getList(&L, i);
        T[u] = 9999;
        for (j = 1; j <= G.n; j++)
        {
            // printf("*");
            if (G.data[u][j] != 0)
                T[u] = min(T[u], T[j] - time[u]);
        }
    }

    // printf("%d\n", t[n + 2]);

    for (i = 1; i <= G.n; i++)
    {
        printf("%d %d\n", t[i], T[i]);
    }
}