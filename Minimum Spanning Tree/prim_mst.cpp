/*
a) Implement Prim’s algorithmfor finding minimumspanning tree of a graph. Start from vertex 1 and
whenever there is a choice of vertices, pick the vertex with smallest number. Use the graph data
structures and heap you implemented during CSE204. Your algorithm should run in time O(ElgV).
b) Implement an algorithm to find a second best minimum spanning tree of the given graph.
*/

#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3


#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

#define MAXV 10000

class HeapItem
{
public:
    int data; //actual data that is stored
    float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;
    int * map;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap() //destructor
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0; //set to NULL after deletion
        A = 0; //set to NULL after deletion
    }

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }

    //this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, float key)
    {
        //heap can store MAX_HEAP_SIZE-1 (0 index unused)
        //overflow checking
        if(heapLength>=MAX_HEAP_SIZE-1)
        {
            printf("Storage limit exceeded\n");
            return;
        }
        A[++heapLength].data = data;
        A[heapLength].key = key;
        map[data] = heapLength;
        buHeapify(heapLength);
    }

    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        HeapItem t;
        t=A[1];
        A[1]=A[heapLength];
        map[A[1].data]=1;
        A[heapLength]=t;
        map[A[heapLength].data]=0;
        heapLength--;
        heapify(1);
        return t;
    }


    //The function updates the key value of an existing data
    //stored in the heap
    //Note that updates can result in an increase or decrease of key value
    //Call to heapify or buheapify is required
    void updateKey(int data, float key)
    {
        //Write your codes here.
        int idx = map[data];
        if(idx<1 || idx>heapLength)
        {
            printf("Not found\n");
            return;
        }
        if(A[idx].key > key)
        {
            A[idx].key = key;
            buHeapify(idx);
        }
        else if(A[idx].key < key)
        {
            A[idx].key = key;
            heapify(idx);
        }
    }


    //This function returns the key value of a data stored in heap
    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( (A[l].key < A[r].key) || (A[l].key == A[r].key && A[l].data < A[r].data))
                smallest = l;
            else
                smallest = r;

            if((A[i].key < A[smallest].key) || ((A[i].key == A[smallest].key) && A[i].data<A[smallest].data))
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }

        }
    }

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
    void buHeapify(int i)
    {
        int parent = i/2;
        if(parent==0) return;

        if( A[parent].key<A[i].key || (A[parent].key==A[i].key && A[parent].data<A[i].data))
        {
            return;
        }
        HeapItem t;
        t = A[i];
        A[i] = A[parent];
        map[A[i].data] = i;
        A[parent] = t;
        map[A[parent].data] = parent;
        i = parent;
        buHeapify(i);
    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};

int time;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Pair
{
    int x;
    int y;
public:
    Pair()
    {
        x = -1;
        y = -1;
    };
    Pair(int u, int v)
    {
        x = u;
        y = v;
    };
    int getx()
    {
        return x;
    };
    int gety()
    {
        return y;
    };
};

int w[MAXV][MAXV];

class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int *color;
    int *parent;
    int *dist;
    int *t_discover;
    int *t_finish;

    bool MSTPossible;

public:
    Pair * mstEdges;
    Pair * sbmstEdges;

    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(); //will run dfs in the graph
    //added
    void dfs_visit(int u);
    void bfs_test();
    void dfs_test();
    //for MST
//    void setParent(int u, int v){ parent[u] = v;};
//    int getParent(int u) {return parent[u];};
    int MST_Prim(int n, int r);
    void MST_PrimEdges();

    int SBMST_Prim(int n, int r);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    color = 0;
    parent = 0;
    dist = 0;
    t_discover = 0;
    t_finish = 0;
    mstEdges = 0;
    sbmstEdges = 0;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;

    //color parent dist time
    color = new int[nVertices];
    parent = new int[nVertices];
    dist = new int[nVertices];
    t_discover = new int[nVertices];
    t_finish = new int[nVertices];
    mstEdges = new Pair[nVertices-1];
    sbmstEdges = new Pair[nVertices-1];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    //if no edge
    int idx = adjList[u].searchItem(v);
    if( idx == NULL_VALUE) return;
    //edge ache
    adjList[u].removeItemAt(idx);
    if(!directed) adjList[v].removeItem(u);
    this->nEdges--;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    int idx = adjList[u].searchItem(v);
    if(idx == NULL_VALUE) return false;
    return true;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    int len = adjList[u].getLength();
    for(int i = 0; i<len; i++)
    {
        int x = adjList[u].getItem(i);
        int idx = adjList[v].searchItem(x);
        if(idx != NULL_VALUE) return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
        //t_discover[i] = -1;
        //t_finish[i] = -1;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int tmp = q.dequeue();
        int len = adjList[tmp].getLength();
        for(int i = 0; i<len; i++)
        {
            int x = adjList[tmp].getItem(i);
            if(color[x] == WHITE)
            {
                color[x] = GREY;
                dist[x] = dist[tmp] + 1;
                parent[x] = tmp;
                q.enqueue(x);
            }
        }
        color[tmp] = BLACK;
    }
}

void Graph::bfs_test()
{
    printf("Distance array : ");
    for(int i = 0; i<nVertices; i++)
    {
        printf("%d ", dist[i]);
    }
    printf("\n");
    printf("Parent array : ");
    for(int i = 0; i<nVertices; i++)
    {
        printf("%d ", parent[i]);
    }
    printf("\n");
}

void Graph::dfs()
{
    //write this function
    //initialize
    for(int i = 0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        //dist[i] = INFINITY ;
        t_discover[i] = -1;
        t_finish[i] = -1;
    }
    time = 0;

    for(int i = 0; i<nVertices; i++)
    {
        if(color[i] == WHITE)
        {
            dfs_visit(i);
        }
    }
}

void Graph::dfs_visit(int u)
{
    time++;
    t_discover[u] = time;
    color[u] = GREY;
    int len = adjList[u].getLength();
    for(int i = 0; i<len; i++)
    {
        int v = adjList[u].getItem(i);
        if(color[v] == WHITE)
        {
            parent[v] = u;
            dfs_visit(v);
        }
    }
    color[u] = BLACK;
    time++;
    t_finish[u] = time;
}

void Graph::dfs_test()
{
    printf("Time array : ");
    for(int i = 0; i<nVertices; i++)
    {
        printf("(%d,%d) ", t_discover[i], t_finish[i]);
    }
    printf("\n");

    printf("Parent array : ");
    for(int i = 0; i<nVertices; i++)
    {
        printf("%d ", parent[i]);
    }
    printf("\n");
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
    int d = dist[v];
    return d;
    //return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here

    if(adjList) delete[] adjList;
    adjList = 0;
    if(color) delete[] color;
    color = 0;
    if(parent) delete[] parent;
    parent = 0;
    if(dist) delete[] dist;
    dist = 0;
    if(t_discover) delete[] t_discover;
    t_discover = 0;
    if(t_finish) delete[] t_finish;
    t_finish = 0;
    if(mstEdges) delete[] mstEdges;
    mstEdges  = 0;
    if(sbmstEdges) delete[] sbmstEdges;
    sbmstEdges  = 0;
}


int Graph::MST_Prim(int n,  int r)
{

    MinHeap Q;

    int mark[n];
    for(int i = 0; i<n; i++)
    {
        //printf("oka\n");
        Q.insertItem(i, MAXREAL);
        mark[i] = 1;
        parent[i] = -1;
    }


    Q.updateKey(r, 0);

    //parent[r] = -1;
    //printf("oka\n");
    int cost = 0;
    int e = 0;
    int parentless = 0;
    while(!Q.Empty())
    {
        //printf("oka\n");
        int u = Q.removeMin().data;
        if(parent[u]==-1) parentless++;
        if(parent[u]!=-1)
        {
            //printf("%d %d\n", parent[u], u);
            int a = parent[u]<u? parent[u]:u;
            int b = parent[u]+u - a;
            mstEdges[e++] = Pair(a,b);
            cost += w[a][b];
        }
        mark[u] = 0;
        int len = adjList[u].getLength();
        for(int i = 0; i<len; i++)
        {
            int v = adjList[u].getItem(i);
            if(mark[v]==1 && w[u][v]<Q.getKey(v))
            {
                parent[v] = u;
                Q.updateKey(v, w[u][v]);
            }
        }
    }
    if(parentless>1) return -1;
    return cost;
}

void Graph::MST_PrimEdges()
{

    for(int i = 0; i<nVertices-1; i++)
    {
        printf("%d %d\n", mstEdges[i].getx()+1, mstEdges[i].gety()+1);
    }
}

int Graph::SBMST_Prim(int n, int r)
{
    this->MST_Prim(n,r);
    Pair * tmp;
    tmp = new Pair[n-1];
    for(int i = 0; i<n-1; i++)
    {
        tmp[i] = mstEdges[i];
    }
    int sbcost = -1;
    bool sbFound = false;
    for(int i = 0; i<n-1; i++)
    {
        int x = mstEdges[i].getx();
        int y = mstEdges[i].gety();
        this->removeEdge(x, y);
        int sb = this->MST_Prim(n, r);
        //printf("%d\n\n\n", sb);
        if(sb!=-1 && (!sbFound  || sb < sbcost))
        {
            for(int j = 0; j<n-1; j++)
            {
                sbmstEdges[j] = mstEdges[j];
            }
            sbcost = sb;
        }
        if(sb!=-1) sbFound = true;
        this->addEdge(x,y);
        for(int j = 0; j<n-1; j++)
        {
            mstEdges[j] = tmp[j];
        }
    }
    if(!sbFound)
    {
        printf("No SBMST\n");
    }
    else
    {
        for(int i = 0; i<nVertices-1; i++)
        {
            printf("%d %d\n", sbmstEdges[i].getx()+1, sbmstEdges[i].gety()+1);
        }
        printf("%d\n", sbcost);
    }
}

//**********************Graph class ends here******************************


int main(void)
{
    freopen("input.txt", "r", stdin);
    int n, m;
    Graph g;
    //in Graph , vertices are from 0 to n-1
    //so handle 1 indexed vertices from main func
    scanf("%d %d", &n, &m);
    //int w[n][n];
    g.setnVertices(n);
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            w[i][j] = INFINITY;
        }
    }


    for(int i = 0; i<m; i++)
    {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--;
        v--;
        g.addEdge(u, v);
        w[u][v] = w[v][u] = c<w[u][v]?c:w[u][v];
        //printf("oka\n");
    }
    //printf("oka\n");
    int mstCost = g.MST_Prim(n,  0); //actual vertex is 1 as root
    if(mstCost==-1)
    {
        printf("No MST\n\n");
    }
    else
    {
        g.MST_PrimEdges();
        printf("%d\n\n", mstCost);
    }
    g.SBMST_Prim(n,0);
    return 0;
}
