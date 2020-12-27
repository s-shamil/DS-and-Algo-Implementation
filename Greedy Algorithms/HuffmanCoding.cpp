/*
Huffman coding: Given a set of n characters and their frequencies f1, ..., fn in some text, construct
Huffman codes for the characters (Reference: Cormen et al. – Section 16.3). Your algorithm should run in time O(n log n).
*/


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
using namespace std;

#define MAX_HEAP_SIZE 1000

class HeapItem{
public:
    char ch;
    int freq;
    HeapItem * left, * right;
};

HeapItem * createNewItem(char c, int f){
    HeapItem * tmp = new HeapItem;
    tmp->ch = c;
    tmp->freq = f;
    tmp->left = tmp->right = 0;
    return tmp;
}

void swapTwo(HeapItem ** a, HeapItem **b){
    HeapItem * tmp = *a;
    *a = *b;
    *b = tmp;
}

class MinHeap{
public:
    HeapItem ** A;
    int heapLength;

    MinHeap()
    {
        A = new HeapItem * [MAX_HEAP_SIZE];
        A[0] = createNewItem('?', 0); // unused node
        heapLength = 0;
    }
    ~MinHeap()
    {
        if(A) delete[] A;
        A = NULL;
    }

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
            else if( A[l]->freq < A[r]->freq )
                smallest = l;
            else
                smallest = r;

            if(A[i]->freq <= A[smallest]->freq)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                swapTwo(&A[i], &A[smallest]);
                i = smallest;
            }
        }
    }
    void buHeapify(int i)
    {
        //cout<<"asi"<<endl;
        int parent = i/2;
        if(parent<=0) return;
        //cout<<"Parent: "<<parent<<endl;
        //cout<<A[1]->freq<<endl;
        //cout<< A[parent]->freq << ' ' <<A[i]->freq<<endl<<endl;
        if(A[parent]->freq<=A[i]->freq)
        {
            return;
        }
        swapTwo(&A[parent], &A[i]);
        i = parent;
        buHeapify(i);
    }

    void addItem(HeapItem * a){
        if(heapLength>=MAX_HEAP_SIZE-1)
        {
            printf("Storage limit exceeded\n");
            return;
        }
        A[++heapLength] = a;
        //cout<<A[heapLength-1]->freq<<endl<<endl;
        buHeapify(heapLength);
    }

    HeapItem * removeMin(){
        HeapItem * t = new HeapItem;
        swapTwo(&A[1], &A[heapLength]);
        t = A[heapLength];
        heapLength--;
        heapify(1);
        return t;
    }
};

void printChars(HeapItem * root, queue<bool> code){
    //cout<<"dhuksi"<<endl;
    if(root->left==0 && root->right==0){

        cout<<root->ch<<' ';
        while(!code.empty()){
            cout<<code.front();
            code.pop();
        }
        cout<<endl;
        return;
    }
    queue<bool> ca(code), cb(code);
    ca.push(0);
    //cout<<root->left->ch<<endl<<endl;
    printChars(root->left, ca);
    cb.push(1);
    printChars(root->right, cb);
}


int main()
{
    int n;
    MinHeap tree;

    cin>>n;
    for(int i = 0; i<n; i++)
    {
        char c;
        int f;
        cin>>c>>f;
        HeapItem * myHeapItem = new HeapItem;

        myHeapItem = createNewItem(c,f);
        //cout<<tree.heapLength<<endl;
        //cout<<myHeapItem->ch<<endl;
        tree.addItem(myHeapItem);
    }
    //cout<<"Okay";

    //makeTree(&tree, &c);

    int i = 0;
    while(tree.heapLength>1){
            //cout<<"dhuksi"<<endl;

        HeapItem * a =  tree.removeMin();
        HeapItem * b =  tree.removeMin();
        HeapItem * c  = createNewItem('?', a->freq+b->freq);
        c->left = a;
        c->right = b;
        tree.addItem(c);
    }
    cout<<endl;
    HeapItem * root = tree.A[1];
    //cout<<root->right->right->left->left->ch<<endl;
    queue<bool> code;
    printChars(root, code);
    //cout<<"Okay";
    return 0;
}


