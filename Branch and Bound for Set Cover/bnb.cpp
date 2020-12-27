#include <bits/stdc++.h>
using namespace std;
#define mem(x,val) memset((x),(val),sizeof(x));
#define write(x) freopen(x,"w",stdout);
#define read(x) freopen(x,"r",stdin);
#define sqr(x) ((x)*(x))
#define pb push_back
#define clr clear()


#define inf (1<<25)
#define NN 1001 //num of elements in universal set = 1000
vector<int> subsets[100]; //num of subsets = 100

int N = NN-1, M = 100;
bool cmp(const vector<int> & a, const vector<int> & b)
{
    return a.size()>b.size();
}

struct Node{
    int level;
    int takenSets;
    int LB;
    int coveredMarks[NN];
    int elementsCovered;
} typedef BBnode;

bool operator<(const BBnode& a, const BBnode& b){
    return a.LB>b.LB;
}

//node dile minimum kotogula subset nite hobe seta bole dibe
int findLB(BBnode node){
    //check this function later
    if(node.elementsCovered==N) return node.takenSets;
    if(node.level==M-1) return inf;
    return node.takenSets + (int)ceil((N-node.elementsCovered) * 1.0 / subsets[node.level+1].size());
}

BBnode setCover(BBnode root){
    priority_queue<BBnode> live;
    BBnode u, v;
    live.push(root);
    while(!live.empty()){
        u = live.top();
        live.pop();
        if(u.elementsCovered==N){
            return u;
        }

        //next level e kichu na thakle
        if(u.level==M-1){
            continue;
        }
        v = u;

        //v k nilam na
        v.level++;
        v.LB = findLB(v);
        live.push(v);

        //v k nicchi
        int idx = v.level;
        for(int i = 0; i<subsets[idx].size(); i++){
            if(v.coveredMarks[subsets[idx][i]]==-1){
                v.coveredMarks[subsets[idx][i]] = idx;
                v.elementsCovered++;
            }
        }
        v.takenSets++;
        v.LB = findLB(v);
        live.push(v);
    }
    return root;
}

int main()
{
    int n, m;
    //freopen("test.txt", "r", stdin);
    scanf("%d %d", &n, &m); // m is the number of subsets
    N = n; M = m;

    BBnode node;
    node.level = -1;
    node.takenSets = 0;
    node.LB = inf;
    mem(node.coveredMarks, -1);
    node.elementsCovered = 0;

    for(int i = 0; i<m; i++)
    {
        int x;
        char tmp;
        while(1){
            scanf("%d%c", &x, &tmp);
            subsets[i].push_back(x);
            if(tmp=='\n'){
                break;
            }
        }
    }
    //reverse sort using cmp arrays to make a greedy choice
    sort(subsets, subsets+ m, cmp);

    BBnode ans = setCover(node);
    printf("\n");
    //sobaike na peye thakle root return dbe jetay takenSets 0
    if(n>0 && ans.takenSets==0){
        cout<<"Impossible\n"<<endl;
        return 0;
    }
    sort(ans.coveredMarks+1, ans.coveredMarks + n + 1);
    cout<<ans.takenSets<<endl;
    for(int i = 1; i<=n; i++){
        if(i==n || ans.coveredMarks[i+1]!=ans.coveredMarks[i]){
            for(int j = 0; j<subsets[ans.coveredMarks[i]].size(); j++){
                cout<<subsets[ans.coveredMarks[i]][j]<<' ';
            }
            cout<<endl;
        }
    }
    return 0;
}

/*
6 4
1 2 3
2 4 6
3 4
4 5
*/
