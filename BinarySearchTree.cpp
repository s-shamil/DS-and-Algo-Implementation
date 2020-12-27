#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
}
struct treeNode * searchParent(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->left != 0)
    {
        if(node->left->item == item)
        {
            return node;
        }
    }
    if(node->right != 0)
    {
        if(node->right->item == item)
        {
            return node;
        }
    }
    if(item<node->item)
    {
        return searchParent(node->left, item);
    }
    return searchParent(node->right, item);
}

struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
}

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node == 0) return 0;
    return 1 + getSize(node->left) + getSize(node->right);
}

int calcDepth(int item);

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    return calcDepth(node->item);
}


int calcDepth(int item)//return depth of an item in the tree
{
    struct treeNode * node = root;
    int depth = 0;
    while(node!=0)
    {
        if(item == node->item)
        {
            break;
        }
        if(item>node->item)
        {
            node = node->right;
        }
        else
        {
            node = node->left;
        }
        depth++;
    }
    if(node==0)
    {
        //not found
        depth = -1;
    }
    return depth;
}

int deleteItem(struct treeNode * node, int item)
{
    //write your code here, return TRUE, FALSE
    struct treeNode * parentNode = 0, * delNode = 0;

    if(root == 0) return FALSE_VALUE;

    delNode = searchItem(root, item);
    if(delNode == 0) return FALSE_VALUE;


    if(item == root->item)
    {
        // delete root
        if(node->left==0)
        {
            delNode = node;
            root = node->right;
            free(delNode);
        }
        else if(node->right==0)
        {
            delNode = node;
            root = node->left;
            free(delNode);
        }
        else
        {
            node = node->right;
            while(node->left!=0)
            {
                node = node->left;
            }
            int temp = node->item;
            deleteItem(root, temp);
            root->item = temp;

            //printf("%d\n\n", item);
        }
        return TRUE_VALUE;
    }
    parentNode = searchParent(root, item);
    //printf("%d\n\n", parentNode->item);
    if(delNode->left == 0)
    {
        if(parentNode->left != 0)
        {
            if(parentNode->left->item == item)
            {
                parentNode->left = delNode->right;
            }
        }
        if(parentNode->right!= 0)
        {
            if(parentNode->right->item == item)
            {
                parentNode->right = delNode->right;
            }
        }
    }
    else if(delNode->right==0)
    {
        if(parentNode->left != 0)
        {
            if(parentNode->left->item == item)
            {
                parentNode->left = delNode->left;
            }
        }
        if(parentNode->right!= 0)
        {
            if(parentNode->right->item == item)
            {
                parentNode->right = delNode->left;
            }
        }

    }
    else
    {
        struct treeNode * newNode = delNode;
        delNode = delNode->right;
        while(delNode->left!=0)
        {
            delNode = delNode->left;
        }
        int temp = delNode->item;
        deleteItem(root, temp);
        newNode->item = temp;

    }
    return TRUE_VALUE;
}



int getMinItem() //returns the minimum item in the tree
{
    struct treeNode * node = root;
    if(node == 0)
    {
        //empty tree
        return -1;
    }
    while(node->left != 0)
    {
        node = node->left;
    }
    return node->item;
}

int getMaxItem() //returns the maximum item in the tree
{
    struct treeNode * node = root;
    if(node == 0)
    {
        //empty tree
        return -1;
    }
    while(node->right != 0)
    {
        node = node->right;
    }
    return node->item;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    if(leftBound>rightBound) return 0;
    if(node == 0) return 0;
    if(node->item == leftBound)
    {
        return 1+rangeSearch(node->right, leftBound, rightBound);
    }
    if(node->item == rightBound)
    {
        return 1+rangeSearch(node->left, leftBound, rightBound);
    }
    if(node->item > leftBound && node->item < rightBound)
    {
        return 1 + rangeSearch(node->left, leftBound, rightBound) + rangeSearch(node->right, leftBound, rightBound);
    }
    if(node->item < leftBound)
    {
        return rangeSearch(node->right, leftBound, rightBound);
    }
    return rangeSearch(node->left, leftBound, rightBound);
}


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0; i<height; i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. Print In Order. 7. exit.\n");
        printf("8. Get Size. 9. Calculate depth of an item. 10. Calculate depth of a node\n");
        printf("11. Get minimum. 12. Get maximum.\n");
        printf("13. Range Search (low, high). 14. Delete item\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7)
        {
            break;
        }
        else if(ch==8)
        {
            int s = getSize(root);
            printf("Size of the tree: %d\n", s);
        }
        else if(ch==9)
        {
            int item;
            scanf("%d", &item);
            int d = calcDepth(item);
            printf("Depth : %d\n", d);
        }
        else if(ch == 10)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * node = makeTreeNode(item);
            int d = calcNodeDepth(node);
            printf("Depth : %d\n", d);
        }
        else if(ch==11)
        {
            printf("Min : %d\n", getMinItem());
        }
        else if(ch == 12)
        {
            printf("Max : %d\n", getMaxItem());
        }
        else if(ch == 13)
        {
            int lo, hi;
            scanf("%d %d", &lo, &hi);
            int n = rangeSearch(root, lo, hi);
            printf("N = %d\n", n);
        }
        else if(ch==14)
        {
            int n;
            scanf("%d", &n);
            deleteItem(root,n);
        }
    }
    return 0;
}
