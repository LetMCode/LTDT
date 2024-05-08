#include <stdio.h>

#define NO_EDGE 0
#define oo 99999
typedef struct
{
    int data[100][500];
    int n;
} Graph;

void makeNullGraph(Graph *pG, int n)
{
    pG->n = n;
    for (int i = 1; i <= pG->n; i++)
    {
        for (int j = 1; j <= pG->n; j++)
        {
            pG->data[i][j] = NO_EDGE;
        }
    }
}

void add_edge(Graph *pG, int u, int v, int t)
{
    pG->data[u][v] = t;
}

int mark[100];   // danh dau da~ duyet
int pi[100];     // trong so' duong` di
int parent[100]; // danh dau' cha cua dinh
int w[100];

void dijkstra(Graph *pG, int s)
{
    int i, j, k;
    // khoi tao
    for (i = 1; i <= pG->n; i++)
    {
        pi[i] = oo;
        mark[i] = 0;
    }
    // dua 1 vao`

    pi[s] = w[s];
    parent[s] = -1;
    // tim trong so nho nhat
    for (k = 1; k <= pG->n; k++)
    {
        int min_pi = oo;
        for (j = 1; j <= pG->n; j++)
        {
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                min_pi = pi[j];
                i = j;
            }
        }
        mark[i] = 1;
        for (j = 1; j <= pG->n; j++)
        {
            if (pG->data[i][j] != NO_EDGE && mark[j] == 0)
            {
                if (pi[i] + pG->data[i][j] < pi[j])
                {
                    pi[j] = pi[i] + pG->data[i][j];
                    parent[j] = i;
                }
                parent[j] = i;
            }
        }
    }
}

int main()
{
    Graph G;
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    makeNullGraph(&G, n * m);
    for (int i = 1; i <= n * m; i++)
    {
        scanf("%d", &u);
        w[i] = u;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int di[] = {-1, 1, 0, 0};
            int dj[] = {0, 0, -1, 1};
            for (int k = 0; k < 4; k++)
            {
                int i_ke = i + di[k];
                int j_ke = j + dj[k];
                if (i_ke >= 0 && i_ke < n && j_ke >= 0 && j_ke < m)
                {
                    v = i_ke * m + j_ke + 1;
                    u = i * m + j + 1;
                    G.data[u][v] = w[v];
                }
            }
        }
    }
    dijkstra(&G, 1);

    printf("%d ", pi[G.n]);

    return 0;
}