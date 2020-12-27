/*
Fractional Knapsack: You are given n items, their weights w1, ..., wn and their values v1, ..., vn as well as a
capacity of a knapsack, W. You want to pack items in the knapsack in such way that total value of items
taken is maximized and total weight of items taken does not exceed knapsack capacity. You are allowed
to take fractions of items. Give an algorithm for the problem that runs in O(n log n) time. (Reference:
Cormen et al. – Section 16.2)

*/

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define MAX_HEAP_SIZE 100000

class obj{
public:
    int item_id;
    int weight;
    int value;
    void set_val(int i, int w, int v){
        item_id = i;
        weight= w;
        value = v;
    };
    void print_obj(){
        printf("%d %d %d\n", item_id, weight, value);
    }
};

class MaxHeap
{
public:
    obj * A;
    int heapLength;

    MaxHeap(){
        A = new obj[MAX_HEAP_SIZE];
        heapLength = 0;
    }

    ~MaxHeap(){
        if(A) delete[] A;
        A = 0;
    }
    void buHeapify(int i){
        int parent = i/2;
        if(A[parent].value * A[i].weight >= A[parent].weight * A[i].value){
            return;
        }
        obj t;
        t = A[i];
        A[i] = A[parent];
        A[parent] = t;
        i = parent;
        buHeapify(i);
    }
    void heapify(int i){
        int l, r, biggest;
        while(1){
            l = 2* i;
            r = 2*i+1;
            biggest = i;
            if(l>heapLength && r>heapLength) {
                break; //nothing to do
            }
            else if(r>heapLength){
                biggest = l;
            }
            else if(l>heapLength){
                biggest = r;
            }
            else if(A[l].value*A[r].weight >= A[r].value*A[l].weight){
                biggest = l;
            }
            else{
                biggest = r;
            }
            if(A[i].value*A[biggest].weight >= A[i].weight*A[biggest].value){
                break; //done
            }
            else{
                obj t;
                t = A[i];
                A[i] = A[biggest];
                A[biggest] = t;
                i = biggest;
            }
        }
    }
    void addObj(obj x){
        if(heapLength>=MAX_HEAP_SIZE-1)
        {
            printf("Storage limit exceeded\n");
            return;
        }
        A[++heapLength] = x;
        buHeapify(heapLength);
    }

    obj removeMax(){
        obj t;
        t = A[1];
        A[1] = A[heapLength];
        A[heapLength] = t;
        heapLength--;
        heapify(1);
        return t;
    }
};


int main()
{
    MaxHeap P;
    obj inp;
    int w, W_rem;
    int v;
    int n;
    cin>>n;
    for(int i = 0; i<n; i++){
        cin>>w>>v;
        inp.set_val(i+1, w, v);
        P.addObj(inp);
    }
    cin>>W_rem;
    obj * outp;
    outp = new obj[MAX_HEAP_SIZE];
    int  p = 0;
    int total = 0;
    while(W_rem>0){
        obj t = P.removeMax();
        if(W_rem<t.weight){
            t.set_val(t.item_id, W_rem, (t.value*W_rem)/t.weight);
            W_rem = 0;
        }
        else{
            W_rem -= t.weight;
        }
        total += t.value;
        outp[p++] = t;
    }
    cout<<total<<endl;
    for(int i=0; i<p; i++){
        outp[i].print_obj();
    }
    return 0;
}
