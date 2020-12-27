#include <bits/stdc++.h>
using namespace std;

/*Salman Shamil*/
#define rep(i,n) for(auto i=0; i<(n); i++)
#define mem(x,val) memset((x),(val),sizeof(x));
#define write(x) freopen(x,"w",stdout);
#define read(x) freopen(x,"r",stdin);
#define sqr(x) ((x)*(x))
#define pb push_back
#define clr clear()
#define inf 999999
#define eps 1e-9
#define PI acos(-1)
#define bug printf("hello\n");

typedef long long i64;
typedef unsigned long long ui64;
typedef pair<int,int> pii;

#define V 100

//int dist[V][V], pred[V][V];

int main() {
    read("test.txt");
    int T;
    cin>>T;
    for(int t = 0; t<T; t++){
        int n,m;
        cin>>n>>m;
        int dist[n+1][n+1], pred[n+1][n+1];
        for(int i = 0; i<=n; i++){
            for(int j = 0; j<=n; j++){
                if(i==j) {
                    dist[i][j] = 0;
                }
                else{
                    dist[i][j] = inf;
                }
                pred[i][j] = -1;
            }
        }

        //input edges
        for(int i = 0; i<m; i++){
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            dist[u][v] = w;
            pred[u][v] = u;
        }


        printf("\n\n*********   Case %d   **********\n", t+1);

        //initial table show
        printf("\nInitial graph:\n");
        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                if(dist[i][j]==inf){
                    printf("INF\t");
                }
                else printf("%d\t", dist[i][j]);
            }
            printf("\n");
        }

        //floyed warshall
        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                for(int k = 1; k<=n; k++){
                    if(dist[j][i]+dist[i][k]<dist[j][k]){
                        dist[j][k] = dist[j][i]+dist[i][k];
                        pred[j][k] = pred[i][k];
                    }
                }
            }
        }

        //All pair shortest path
        printf("\nAll pair shortest path:\n");
        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                if(dist[i][j]==inf){
                    printf("INF\t");
                }
                else printf("%d\t", dist[i][j]);
            }
            printf("\n");
        }

        //Parent of v for path u->v
        printf("\nPredecessor Matrix:\n");
        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                if(pred[i][j]==-1){
                    printf("NULL\t");
                }
                else printf("%d\t", pred[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
