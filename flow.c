#include <stdio.h>

typedef struct
{
    int data[100];
    int front, rear;
} Queue;

void makenullQueue(Queue *Q)
{
    Q->rear = -1;
    Q->front = 0;
}

void pushQueue(Queue *Q, int x)
{
    Q->rear++;
    Q->data[Q->rear] = x;
}
void popQueue(Queue *Q)
{
    Q->front++;
}

int getQueue(Queue *Q)
{
    return Q->data[Q->front];
}
int emptyQueue(Queue *Q)
{
    return Q->front > Q->rear;
}

typedef struct
{
    int data[100];
    int size;
} List;

void makenullList(List *L)
{
    L->size = 0;
}

void pushList(List *L, int u)
{
    L->data[L->size] = u;
    L->size++;
}

void popList(List *L)
{
    L->size--;
}

int getList(List *L, int u)
{
    return L->data[u - 1];
}

int emptyList(List *L)
{
    return L->size == 0;
}

typedef struct
{
    int F[100][500]; // luong. tang luong
    int C[100][500]; // kha nang tang luong
    int n;
} Graph;

typedef struct
{
    int dir, sigma, pre;
} Label;

Label Labels[100];

void makenullGraph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
        {
            G->F[i][j] = 0;
            G->C[i][j] = 0;
        }
    }
}

void addEdge(Graph *G, int u, int v, int c, int f)
{
    G->F[u][v] = f;
    G->C[u][v] = c;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
int min(int a, int b)
{
    return (a < b) ? a : b;
}

int fordFull(Graph *G, int s, int t)
{
    Queue Q;
    int max_flow = 0, i;
    do
    {
        for (i = 1; i <= G->n; i++)
        {
            Labels[i].dir = 0;
        }
        // khoi tao dinh s:
        Labels[s].dir = 1;
        Labels[s].sigma = 9999;
        Labels[s].pre = s;
        makenullQueue(&Q);
        pushQueue(&Q, s);
        int found = 0;
        while (!emptyQueue(&Q))
        {
            int u = getQueue(&Q);
            popQueue(&Q);
            for (i = 1; i <= G->n; i++)
            {
                if (G->C[u][i] != 0 && Labels[i].dir == 0 && G->C[u][i] > G->F[u][i])
                {
                    Labels[i].dir = 1;
                    Labels[i].pre = u;
                    Labels[i].sigma = min(Labels[u].sigma, G->C[u][i] - G->F[u][i]);
                    pushQueue(&Q, i);
                }
            }
            for (i = 1; i <= G->n; i++)
            {
                if (G->C[i][u] != 0 && Labels[i].dir == 0 && G->F[u][i] > 0)
                {
                    Labels[i].dir = -1;
                    Labels[i].pre = u;
                    Labels[i].sigma = min(Labels[u].sigma, G->F[i][u]);
                    pushQueue(&Q, i);
                }
            }
            if (Labels[t].dir != 0)
            {
                found = 1;
                break;
            }
        }

        if (found == 1)
        {
            int sigma = Labels[t].sigma;
            int v = t;
            while (v != s)
            {
                int p = Labels[v].pre;
                if (Labels[v].dir > 0)
                    G->F[p][v] += sigma;
                else
                    G->F[v][p] -= sigma;
                v = p;
            }
            max_flow += sigma;
        }
        else
            break;
    } while (1);
    return max_flow;
}

int main()
{
    freopen("data.txt", "r", stdin);
    Graph G;
    int n, m, f, c, u, v, i, j;
    scanf("%d%d", &n, &m);
    makenullGraph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &u, &v, &c, &f);
        addEdge(&G, u, v, c, f);
    }

    int max_flow = fordFull(&G, 1, n);
    printf("Max flows: %d\nS: ", max_flow);

    for (i = 1; i <= n; i++)
    {
        if (Labels[i].dir != 0)
        {
            printf("%d ", i);
        }
    }
    printf("\nT: ");
    for (i = 1; i <= n; i++)
    {
        if (Labels[i].dir == 0)
        {
            printf("%d ", i);
        }
    }
}