#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int V, E;

void sort(int **e);
int comp(const void *a, const void *b);
int findParent(int *parent, int vertex);
void _union(int *parent, int a, int b);
void kruskal(int **e, int **min);

int main()
{
    scanf("%d %d", &V, &E);

    int **edges = (int **)malloc(E * sizeof(int *));
    int **minCost = (int **)malloc(E * sizeof(int *));

    for (int i = 0; i < E; i++)
    {
        edges[i] = (int *)malloc(3 * sizeof(int));
        minCost[i] = (int *)malloc(3 * sizeof(int));
    }

    for (int i = 0; i < E; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &edges[i][j]);
        }
    }

/*
    printf("-----------------------\n");
    for (int i = 0; i < E; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", edges[i][j]);
        }
        printf("\n");
    }
*/

    kruskal(edges, minCost);
    return 0;
}

int comp(const void *pa, const void *pb)
{
    const int a = (*(const int **)pa)[2];
    const int b = (*(const int **)pb)[2];

    return (a - b);
}

void sort(int **e)
{
    qsort(e, E, sizeof e[0], comp);
}

void _union(int *parent, int a, int b)
{
    for (int i = 0; i < V; i++)
    {
        if (parent[i] == b)
            parent[i] = a;
    }
}

int findParent(int *parent, int vertex)
{
    return(parent[vertex]);
}

void kruskal(int **e, int **min)
{
    int *parent = (int*) malloc(V * sizeof(int));
    int c1, c2;
    long long cost = 0;

    sort(e);

    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
    }
    
    for (int i = 0; i < E; i++)
    {
        c1 = findParent(parent, e[i][0]);
        c2 = findParent(parent, e[i][1]);

        if (c1 != c2)
        {
            min[i][0] = e[i][0];
            min[i][1] = e[i][1];
            min[i][2] = e[i][2];
            cost += e[i][2];
            _union(parent, c1, c2);
        }
    }
    
    printf("%lld", cost);
}
