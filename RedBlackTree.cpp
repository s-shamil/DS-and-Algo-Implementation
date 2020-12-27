#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define RED 0
#define BLACK 1
#define NIL_VAL -1

struct red_black_node{
    int key;
    int color;
    struct red_black_node * parent;
    struct red_black_node * left;
    struct red_black_node * right;
} typedef rbnode;

rbnode * nil, * root;

rbnode * makeNode(int key, int color){
    rbnode * newnode;
    newnode = (rbnode *) malloc(sizeof(rbnode));
    newnode->key = key;
    newnode->color = color;
    newnode->parent = newnode->left = newnode->right = nil;
}
//test function
void isNil(rbnode * temp){
    if(temp->key==nil->key && temp->color==nil->color){
        cout<<"Yes"<<endl;
    }
    else cout<<"No"<<endl;
}
void initializeTree()
{
    root = nil;
}
//search key
rbnode * searchKey(rbnode * node, int key){
    if(node==nil) return nil;
    if(node->key==key) return node;
    rbnode * t = nil;
    if(key < node->key){
        t = searchKey(node->left, key);
    }
    else{
        t = searchKey(node->right, key);
    }
    return t;
}

void leftRotate(rbnode * x)
{
    rbnode * y = x->right;
    x->right = y->left;
    if(y->left != nil){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent==nil){
        root = y;
    }
    else if(x==x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(rbnode * x)
{
    rbnode * y = x->left;
    x->left = y->right;
    if(y->right != nil){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent==nil){
        root = y;
    }
    else if(x==x->parent->right){
        x->parent->right = y;
    }
    else{
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}


void fixInsert(rbnode * z){
    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            rbnode * y = z->parent->parent->right;
            if(y->color==RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z==z->parent->right){
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        }
        else{
            rbnode * y = z->parent->parent->left;
            if(y->color==RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else{
                if(z==z->parent->left){
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}


//insert key
void insertKey(rbnode * node, int key){
    rbnode * y = nil;
    rbnode * x = root;
    rbnode * z = makeNode(key, RED);
    while(x!=nil){
        y = x;
        if(key<x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y==nil){
        root = z;
    }
    else if(key<y->key){
        y->left = z;
    }
    else{
        y->right = z;
    }
    fixInsert(z);
}


//deletion and others

void Transplant(rbnode * u, rbnode * v){
    if(u->parent==nil){
        root = v;
    }
    else if(u==u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

rbnode * findMinNode(rbnode * node){
    if(node==nil){
        return nil;
    }
    while(node->left!=nil){
        node = node->left;
    }
    return node;
}


rbnode * findMaxNode(rbnode * node){
    if(node==nil){
        return nil;
    }
    while(node->right!=nil){
        node = node->right;
    }
    return node;
}

void fixDelete(rbnode * x){
    while(x!=root && x->color==BLACK){
        //if x is left child
        if(x==x->parent->left){
            rbnode * w = x->parent->right;
            //case 1  - reduces to 2/3/4
            if(w->color==RED){
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            //case 2
            if(w->left->color==BLACK && w->right->color==BLACK){
                w->color = RED;
                x = x->parent; // moving up the problem
            }
            else{
                //case 3 - reduces to case 4
                if(w->right->color==BLACK){
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                //case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        //if x is right child
        else if(x==x->parent->right){
            rbnode * w = x->parent->left;
            //case 1  - reduces to 2/3/4
            if(w->color==RED){
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            //case 2
            if(w->right->color==BLACK && w->left->color==BLACK){
                w->color = RED;
                x = x->parent; // moving up the problem
            }
            else{
                //case 3 - reduces to case 4
                if(w->left->color==BLACK){
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                //case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

//delete function
void deleteKey(int key){
    rbnode * z = searchKey(root, key);
    if(z==nil) {
        printf("Key not found!\n");
        return;
    }
    rbnode * y = z;
    int y_original_color = y->color;

    rbnode * x = nil;

    if(z->left == nil){
        x = z->right;
        Transplant(z, z->right);
    }
    else if(z->right==nil){
        x = z->left;
        Transplant(z, z->left);
    }
    else{
        y = findMinNode(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent==z){
            x->parent = y;
        }
        else{
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if(y_original_color==BLACK){
        fixDelete(x);
    }
    printf("Key deleted!\n");
}

//print in ascending order
void printSorted(rbnode * node){
    if(node==nil) return;

    printSorted(node->left);
    printf("%d ", node->key);
    printSorted(node->right);
}

//calculate height - needed for print
int calcNodeHeight(rbnode * node){
    if(node==nil) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    return max(l,r) + 1;
}

//print in order
void printInOrder(rbnode * node, int height){
    if(node==nil) return;

    printInOrder(node->left, height-1);
    for(int i = 0; i<height; i++) printf("    ");
    printf("%3d", node->key);
    if(node->color==RED) printf("R\n");
    else printf("B\n");
    printInOrder(node->right, height-1);
}
//del node
int main(){
    //freopen("test.txt", "r", stdin);
    //nil node to use as NULL
    nil = makeNode(-1, BLACK);

    initializeTree();

    int cmd;
    // 1 - insert key
    // 2 - search key
    // 3 - delete key
    // 4 - print ascend
    // 5 - min - return min key
    // 6 - max - return max key


    // 9 - print in order tree
    printf("1: Insert 2: Lookup 3: Delete 4: Print 5: Min 6: Max 0: Exit\n");
    while(scanf("%d", &cmd) && cmd!=0){

        if(cmd==1){
            //insert
            int x;
            scanf("%d", &x);
            insertKey(root, x);
        }
        else if(cmd==2){
            int x;
            scanf("%d", &x);
            rbnode * rs = searchKey(root, x);
            if(rs==nil){
                printf("Key (%d) not found!\n", x);
            }
            else{
                printf("Key (%d) found!\n", x);
            }
        }
        else if(cmd==3){
            int x;
            scanf("%d", &x);
            deleteKey(x);
        }
        else if(cmd==4){
            printf("All keys in ascending order:\n");
            printSorted(root);
            printf("\n\n");
        }
        else if(cmd==5){
            rbnode * rs = findMinNode(root);
            if(rs==nil){
                printf("Tree is empty!\n");
            }
            else{
                printf("Min key: %d\n", rs->key);
            }
        }
        else if(cmd==6){
            rbnode * rs = findMaxNode(root);
            if(rs==nil){
                printf("Tree is empty!\n");
            }
            else{
                printf("Max key: %d\n", rs->key);
            }
        }

        else if(cmd==9){
            printInOrder(root, calcNodeHeight(root));
        }
        printf("1: Insert 2: Lookup 3: Delete 4: Print 5: Min 6: Max 0: Exit\n");
    }
    //cout<<calcNodeHeight(root)<<" HEIGHT"<<endl;
    return 0;
}
