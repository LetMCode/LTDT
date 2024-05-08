#include <stdio.h>

// Stack
typedef struct
{
    int top;
    int data[100];
} Stack;

void makeNullStack(Stack *S)
{
    S->top = 0;
}

void pushStack(Stack *S, int u)
{
    S->data[S->top] = u;
    S->top++;
}
void popStack(Stack *S)
{
    S->top--;
}

int topStack(Stack *S)
{
    return S->data[S->top - 1];
}

int emptyStack(Stack *S)
{
    return S->top == 0;
}

// List
typedef struct
{
    int data[100];
    int size;
} List;

void makeNullList(List *L)
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

int topList(List *L, int i)
{
    return L->data[i - 1];
}

int emptyList(List *L)
{
    return L->size == 0;
}

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
}

int checkEdge(Graph *G, int u, int v)
{
    return G->data[u][v] == 1;
}

List neighbors(Graph *G, int u)
{
    List L;
    makeNullList(&L);
    int i;
    for (i = 1; i <= G->n; i++)
    {
        if (checkEdge(G, u, i))
        {
            pushList(&L, i);
        }
    }
    return L;
}

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int on_Stack[100];
int min_num[100], num[100], k = 1, count = 0;

void strongConnect(Graph *G, int x)
{
    num[x] = min_num[x] = k;
    k++;

    Stack S;
    makeNullStack(&S);

    on_Stack[x] = 1;
    pushStack(&S, x);
    int i;
    List L = neighbors(G, x);
    for (i = 1; i <= L.size; i++)
    {
        int v = topList(&L, i);
        if (on_Stack[v] == -1)
        {
            strongConnect(G, v);
            min_num[x] = min(min_num[x], min_num[v]);
        }
        else if (on_Stack[v] == 1)
        {
            min_num[x] = min(min_num[x], num[v]);
        }
        if (num[x] == min_num[x])
        {
            int l;
            count++;
            do
            {
                l = topStack(&S);
                popStack(&S);
                on_Stack[x] = 0;
            } while (l != x);
        }
    }
}

int main()
{
    freopen("data.txt", "r", stdin);
    Graph G;
    int i, j, n, m, u, v;
    scanf("%d%d", &n, &m);
    makeNullGraph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        addEdge(&G, u, v);
    }
    for (i = 1; i <= n; i++)
    {
        on_Stack[i] = -1;
    }

    for (i = 1; i <= n; i++)
    {
        if (on_Stack[i] == -1)
        {
            strongConnect(&G, i);
        }
    }
    printf("%d", count);

    if (count == 1)
        printf("YES");
    else
        printf("NO");
    return 0;
}
