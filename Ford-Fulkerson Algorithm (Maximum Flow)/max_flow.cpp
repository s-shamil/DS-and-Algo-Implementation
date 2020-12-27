#include <bits/stdc++.h>
using namespace std;

/* -----Salman Shamil ----- */
/* -----Date : 25-NOV-2017 ----- */


/* Input pattern
    T
    T times
    [n m
    all (u, v, c)
    s t]
*/
#define mem(x,val) memset((x),(val),sizeof(x));
#define write(x) freopen(x,"w",stdout);
#define read(x) freopen(x,"r",stdin);
#define sqr(x) ((x)*(x))
#define inf (1<<30)
#define eps 1e-9
#define bug printf("hello\n");
#define bugx(x) printf("hello $ %d\n", x);

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

#define N 1001 //number of nodes+1

vector <int> adj[N];
int cf[N][N];
int echeck[N][N];
int NN; // updated number of nodes

int visited[N];
int parent[N];

bool bfs(int s, int t){
    for(int i = 0; i<=NN; i++){
        visited[i] = 0;
        parent[i] = -1;
    }
    queue<int> Q;
    Q.push(s);
    visited[s] = 1;

    while(!Q.empty()){
        int u = Q.front();
        Q.pop();

        for(int i = 0; i<adj[u].size(); i++){
            int v = adj[u][i];
            //if(u==8 && v==2) cout<<"$"<<cf[u][v]<<endl;
            if(visited[v]==0 && cf[u][v]>0){
                visited[v] = 1;
                parent[v] = u;
                if(v==t) return true;
                Q.push(v);
            }
        }
    }
    return false;
}
int ford_fulkerson(int s, int t){
    int total_flow = 0;
    while(bfs(s,t)){
        stack<int> st;
        int min_res_cap = cf[parent[t]][t];
        int tt = t;
        int pt = parent[tt];
        st.push(tt);
        //st.push(pt);
        while(tt!=s){
            pt = parent[tt];
            if(cf[pt][tt] < min_res_cap){
                min_res_cap = cf[pt][tt];
            }
            st.push(pt);
            tt = pt;
        }
        int x = st.top();
        st.pop();
        int y;
        while(!st.empty()){
            y = st.top();
            cf[x][y] -= min_res_cap;
            cf[y][x] += min_res_cap;
            x = y;
            st.pop();
        }

        total_flow += min_res_cap;
    }
    return total_flow;
}
void min_cut_print(){
    //bfs returned false last time - so we can work on that vis array
    vector< pii > mincut;
    int cnt = 0;
    for(int i = 0; i<=NN; i++){
        //cout<<visited[i]<< " * ";
        if(visited[i]==1){
            for(int j = 0; j<adj[i].size(); j++){
                if(echeck[i][adj[i][j]]==1 && visited[adj[i][j]] == 0){
                    mincut.push_back(make_pair(i, adj[i][j]));
                    cnt++;
                }
            }
        }
    }
    cout<<endl;
    printf("Number of edges in min cut: %d\n", cnt);
    for(int i = 0; i<cnt; i++){
        printf("%d %d\n", mincut[i].first, mincut[i].second);
    }
    printf("\n\n\n");
}

typedef struct edge{
    int u;
    int v;
    int c;
} Edge;

vector<Edge> edg;

int main() {
    read("test.txt");
    int T;
    cin>>T;
    for(int toc = 1; toc<=T; toc++)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        NN = n;

        //clear all
        for(int i = 0; i<=n; i++){
            adj[i].clear();
        }
        edg.clear();
        mem(cf, 0);
        mem(echeck, 0);
        //take edges
        for(int i = 0; i<m; i++){
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            Edge e;
            e.u = u; e.v = v; e.c = c;
            edg.push_back(e);
            adj[u].push_back(v);
            adj[v].push_back(u);
            cf[u][v] += c;
            echeck[u][v] = 1;
        }
        int s, t;
        scanf("%d %d", &s, &t);
        printf("Case %d:\n\n", toc);
        int flow = ford_fulkerson(s, t);
        printf("Max Flow Value: %d\n\n", flow);
        printf("Flow along edges:\n");
        for(int i = 0; i<m; i++){
            Edge ed = edg[i];
            printf("%d -> %d  :  %d\n", ed.u, ed.v, ed.c - cf[ed.u][ed.v]);
        }
        printf("\n");
        min_cut_print();
    }
    return 0;
}

