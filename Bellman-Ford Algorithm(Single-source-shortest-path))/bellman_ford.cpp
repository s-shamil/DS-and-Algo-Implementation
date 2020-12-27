#include<stdio.h>
#include<stdlib.h>

#define INF 1000000000
#define MAXV 10000

using namespace std;

struct edge
{
    //from u to v weight w
    int u;
    int v;
    int w;
} typedef Edge;

Edge * edges;
int * parent;
int * dist;

void init(int n, int m)
{
    edges = new Edge[m];
    parent = new int[n+1];
    dist = new int[n+1];
}
void finish()
{
    delete[] edges;
    delete[] parent;
    delete[] dist;
}


void relax(int u, int v, int w)
{
    if(dist[v]>(dist[u]+w))
    {
        dist[v] = dist[u]+w;
        parent[v] = u;
    }
}

//return value -> neg cycle? yes1 : no0
bool bellmanFord(int s, int n, int m)
{
    for(int i = 1; i<=n; i++)
    {
        dist[i] = INF;
        parent[i] = 0;
    }
    dist[s] = 0;
    for(int i = 0; i<(n-1); i++)
    {
        for(int j = 0; j<m; j++)
        {
            relax(edges[j].u, edges[j].v, edges[j].w);
        }
    }
    for(int j = 0; j<m; j++)
    {
        if(dist[edges[j].v]>(dist[edges[j].u]+edges[j].w))
        {
            return true;
        }
    }
    return false;
}


int main()
{
    freopen("input.txt", "r", stdin);
    int t;
    scanf("%d", &t);
    //t = 1;
    for(int ti = 0; ti<t; ti++)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        init(n,m);
        for(int i = 0; i<m; i++){
            scanf("%d %d %d", &edges[i].u, &edges[i].v,  &edges[i].w);
        }
        printf("Source? : ");
        int s;
        scanf("%d", &s);
        bool neg = bellmanFord(s, n, m);
        printf("\nV\t\tV.d\t\tV.pi\n");
        for(int i = 1; i<=n; i++){
            printf("%d\t\t", i);
            if(dist[i]!=INF){
                printf("%d\t\t", dist[i]);
            }
            else{
                printf("INF\t\t");
            }
            if(parent[i]!=0){
                printf("%d\n", parent[i]);
            }
            else{
                printf("NIL\n");
            }
        }
        printf("Negative Cycle? ");
        if(neg) printf("Yes\n");
        else printf("No\n");
        finish();
    }
    return 0;
}
