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
struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
	tail = 0;
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

//add required codes to insert item at the beginning, remember to properly set the tail pointer!
int insertItem(int item)
{
	struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = list ; //point to previous first node
    list = newNode ; //set list to point to newnode as this is now the first node
    if(tail == 0){
        tail = newNode;
    }
    return SUCCESS_VALUE;
}

//add required codes to delete item, remember to properly set the tail pointer!
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
            //if del is the tail
            if(del->next == 0){
                tail = temp;
            }
            free(del);
            return SUCCESS_VALUE;
        }
        temp = temp->next;
    }
    return SUCCESS_VALUE;
}

int insertLast(int item)
{
    //creating the new node
    struct listNode * newNode, *temp;
    newNode = (struct listNode *) malloc(sizeof(struct listNode));
    newNode->item = item;
    newNode->next = 0;
    //in case of empty list
    if(list==0){
        list = newNode;
        tail = newNode;
        return SUCCESS_VALUE;
    }
    tail->next = newNode;
    tail = newNode;
    return SUCCESS_VALUE;
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert item\n");
        printf("2. Delete after\n");
        printf("3. Search item\n");
        printf("4. Insert last\n");
        printf("5. Print list\n");
        printf("6. Exit\n");

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
            deleteAfter(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4){
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }
    }
    return 0;
}
