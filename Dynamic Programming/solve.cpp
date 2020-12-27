#include <bits/stdc++.h>
using namespace std;

#define B 100000
#define N 1000
#define eps 1e-9
#define bug printf("hello\n");
#define bug2 printf("hello 2\n");

double dp[B][N];
int cost[N],  m[B][N], remB;
double r[N], NN;

double maxProb(int rem, int pos)
{
    if(pos==NN)
    {
        //bug2
        return 1.0;
    }
    if(rem<cost[pos])
    {
        //bug
        //cout<<rem<<"%"<<pos<<endl;
        return 0.0;
    }
    if(dp[rem][pos]>=0) return dp[rem][pos];

    int mi = 0, imax = (int)(rem/cost[pos]);
    double prb, maxprb = 0.0;

    for(int i = 1; i<=imax; i++)
    {
        prb = (1 - pow((1-r[pos]), i)) * maxProb(rem - i * cost[pos], pos+1);
        if(prb>maxprb)
        {
            maxprb = prb;
            mi = i;
        }
    }
    //cout<<maxprb;
    m[rem][pos] = mi;
    return dp[rem][pos] = maxprb;
}


int main()
{
    freopen("input.txt", "r", stdin);
    int t;
    cin>>t;
    for(int T = 0; T<t; T++)
    {
        int n;
        int b;
        memset(dp, -1.0, sizeof dp);
        scanf("%d %d", &b, &n);
        remB = b;
        NN = n;
        for(int i = 0; i<n; i++)
        {
            scanf("%lf", &r[i]);
        }
        for(int i = 0; i<n; i++)
        {
            scanf("%d", &cost[i]);
        }
        double probability = maxProb(remB, 0);
        int rem = remB;
        if(probability<eps)
        {
            printf("Impossible\n");
        }
        else
        {
            for(int i=0; i<NN; i++)
            {
                printf("%d ", m[rem][i]);
                rem = rem - cost[i] * m[rem][i];
            }

            cout<<endl<<probability<<endl;
        }
    }
    return 0;
}
