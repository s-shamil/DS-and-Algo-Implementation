#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

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

public:
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
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2. Remove edge. 3. Is edge?\n");
        printf("4. Get degree 5. Print Graph  6. Has common adjacent?\n");
        printf("7. BFS 8. DFS 9. Get distance 10. Exit\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            bool p = g.isEdge(u,v);
            if(p) printf("Yes!\n");
            else printf("No!\n");
        }
        else if(ch==4)
        {
            int u;
            scanf("%d", &u);
            int n = g.getDegree(u);
            printf("Degree = %d\n", n);
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            bool p = g.hasCommonAdjacent(u,v);
            if(p) printf("Yes!\n");
            else printf("No!\n");
        }
        else if(ch==7)
        {
            printf("Source : ");
            int u;
            scanf("%d", &u);
            g.bfs(u);
            g.bfs_test();
        }
        else if(ch==8)
        {
            g.dfs();
            g.dfs_test();
        }
        else if(ch==9)
        {
            int u,v;
            scanf("%d %d", &u, &v);
            int d = g.getDist(u,v);
            printf("Distance : %d\n", d);
        }
        else if(ch==10)
        {
            break;
        }
    }
    return 0;
}
