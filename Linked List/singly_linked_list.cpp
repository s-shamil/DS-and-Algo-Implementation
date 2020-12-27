#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning of the linked list
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = list ; //point to previous first node
    list = newNode ; //set list to point to newnode as this is now the first node
    return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
    struct listNode *temp, *prev ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) break ;
        prev = temp;
        temp = temp->next ; //move to next node
    }
    if (temp == 0) return NULL_VALUE ; //item not found to delete
    if (temp == list) //delete the first node
    {
        list = list->next ;
        free(temp) ;
    }
    else
    {
        prev->next = temp->next ;
        free(temp);
    }
    return SUCCESS_VALUE ;
}


struct listNode * searchItem(int item)
{
    struct listNode * temp ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) return temp ;
        temp = temp->next ; //move to next node
    }
    return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    printf("\n");
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n\n");
}

int insertLast(int item)
{
    //creating the new node
    struct listNode * newNode, *temp;
    newNode = (struct listNode *) malloc(sizeof(struct listNode));
    newNode->item = item;
    newNode->next = 0;
    //taking temp from head to tail
    temp = list;
    //in case of empty list
    if(temp==0){
        list = newNode;
        return SUCCESS_VALUE;
    }
    while(temp->next != 0)
    {
        temp = temp->next;
    }
    //linking the new node in tail
    temp->next = newNode;
    return SUCCESS_VALUE;
}


int insertBefore(int oldItem, int newItem)
{
    //creating the new node
    struct listNode * newNode, *temp;
    newNode = (struct listNode *) malloc(sizeof(struct listNode));
    newNode->item = newItem;
    newNode->next = 0;

    //in case of empty list
    if(list == 0) {
        list = newNode;
        return SUCCESS_VALUE;
    }

    //olditem at beginning
    if(list->item == oldItem)
    {
        newNode->next = list;
        list = newNode;
        return SUCCESS_VALUE;
    }

    temp = list;
    //search for the old item
    while(temp->next != 0)
    {
        if(temp->next->item == oldItem)
        {
            newNode->next = temp->next;
            temp->next = newNode;
            return SUCCESS_VALUE;
        }
        temp = temp->next;
    }

    //in case not found
    newNode->next = list;
    list = newNode;
    return SUCCESS_VALUE;
}

int deleteAfter(int item)
{
    struct listNode * temp, *del;
    temp = list;
    del = 0;
    if(temp==0){
        return NULL_VALUE;
    }
    while(temp->next != 0){
        if(temp->item == item){
            del = temp->next;
            temp->next = del->next;
            free(del);
            return SUCCESS_VALUE;
        }
        temp = temp->next;
    }
    return SUCCESS_VALUE;
}

int deleteLast(){
    struct listNode * temp, *prev;
    temp = list;
    prev = 0;
    if(temp==0) {
        return NULL_VALUE;
    }
    while(temp->next != 0){
        prev = temp;
        temp = temp->next;
    }
    free(temp);
    if(prev != 0) prev->next = 0;
    else initializeList();
    return SUCCESS_VALUE;
}

int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item.\n");
        printf("2. Delete item\n");
        printf("3. Search item\n");
        printf("4. Print\n");
        printf("5. Insert item at tail\n");
        printf("6. Insert before\n");
        printf("7. Delete after\n");
        printf("8. Delete last item\n");
        printf("9. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            printList();
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch==6)
        {
            int olditem, newitem;
            scanf("%d %d", &olditem, &newitem);
            insertBefore(olditem, newitem);
        }
        else if(ch==7){
            int i;
            scanf("%d", &i);
            deleteAfter(i);
        }
        else if(ch==8){
            deleteLast();
        }
        else if(ch==9)
        {
            break;
        }
    }
    return 0;
}
