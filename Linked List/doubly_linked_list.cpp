#include<stdio.h>
#include<stdlib.h>


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
};

struct listNode * list;

struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

int insertFirst(int item) //insert at the beginning
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;

	if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
	return SUCCESS_VALUE ;
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
            //if del is the tail
            if(del->next == 0){
                tail = temp;
            }
            else{
                del->next->prev = temp;
            }
            free(del);
            return SUCCESS_VALUE;
        }
        temp = temp->next;
    }
    return SUCCESS_VALUE;

}

int deleteLast()
{
    struct listNode * temp;

    if(tail==0) return NULL_VALUE;

    temp = tail;
    tail = tail->prev;
    if(tail != 0) tail->next = 0;
    else list = 0;

    int value = temp->item;
    free(temp);
    return value;
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

void printListForward()
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

void printListBackward()
{
	//will print the list backward starting from the tail position
    struct listNode * temp;
    temp = tail;
    printf("\n");
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->prev;
    }
    printf("\n\n");
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item\n");
        printf("2. Delete after\n");
        printf("3. Delete last\n");
        printf("4. Search item\n");
        printf("5. Print forward\n");
        printf("6. Print backward\n");
        printf("7. Exit\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==3)
        {
            int item = deleteLast();
            if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");

        }
        else if(ch==5)
        {
            printListForward();
        }
        else if(ch==6)
        {
            printListBackward();
        }
        else if(ch==7){
            break;
        }
    }

}
