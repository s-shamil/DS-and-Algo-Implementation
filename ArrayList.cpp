#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999
#define STRING_MAX_LENGTH 1000

int listMaxSize;
int * list;
int length;
int clear_flag = 0;

int shrink();

void initializeList()
{
    listMaxSize = LIST_INIT_SIZE;
    list = (int*)malloc(sizeof(int)*listMaxSize) ;
    length = 0 ;
}

int searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

int insertItem(int newitem)
{
    if(clear_flag==1)
    {
        //list has no memory allocated
        initializeList();
        //memory allocated
        clear_flag = 0;
    }
    else
    {
        int * tempList ;
        if (length == listMaxSize)
        {
            //allocate new memory space for tempList
            listMaxSize = 2 * listMaxSize ;
            tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
            int i;
            for( i = 0; i < length ; i++ )
            {
                tempList[i] = list[i] ; //copy all items from list to tempList
            }
            free(list) ; //free the memory allocated before
            list = tempList ; //make list to point to new memory
        };
    }

    list[length] = newitem ; //store new item
    length++ ;
    return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
    if ( position >= length ) return NULL_VALUE;
    list[position] = list[length-1] ;
    length-- ;
    shrink();
    return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return NULL_VALUE;
    deleteItemAt(position) ;
    return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

//<tasks>

//task 1
int getLength()
{
    return length;
}

//task 2
int insertItemAt(int pos, int item)
{
    if(pos>=length)
    {
        return NULL_VALUE;
    }
    int temp = list[pos];
    list[pos] = item;
    return insertItem(temp);
}

//task 3
int shrink()
{
    int * tempList;
    if(length*2 <= listMaxSize && listMaxSize>LIST_INIT_SIZE)
    {
        //allocate new memory space for tempList
        listMaxSize = listMaxSize / 2;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    }
    return SUCCESS_VALUE;
}

//task 4
int deleteLast()
{
    if(length>0)
    {
        int tmp = list[length-1];
        length--;
        shrink();
        return tmp;
    }
    return NULL_VALUE;
}

//task 5
int clear(){
    length = 0;
    free(list);
    listMaxSize = 0; // freed memory, so zero sized
    clear_flag = 1;
    return SUCCESS_VALUE;
}

//task 6
int deleteAll(){
    length = 0;
    if(listMaxSize>LIST_INIT_SIZE){
        free(list);
        listMaxSize = LIST_INIT_SIZE;
        list = (int*)malloc(sizeof(int)*listMaxSize) ;
    }
    return SUCCESS_VALUE;
}


//7th task main func
int main(void){
    initializeList();
    char str[STRING_MAX_LENGTH];
    scanf("%s", str);
    int result;
    for(int i = 0; str[i] ; i++){
        if(str[i]>='0' && str[i]<='9'){
            insertItem(str[i] - '0');
        }
        else{

            int b = deleteLast();
            int a = deleteLast();
            if(str[i] == '+'){
                result = a + b;
            }
            else if(str[i] == '-'){
                result = a - b;
            }
            else if(str[i] == '*'){
                result = a * b;
            }
            else if(str[i] == '/'){
                result = a / b;
            }
            insertItem(result);
        }
    }
    printf("Value : ");
    printf("%d\n", *list);
    printf("\n");
    clear();
    return 0;
}

// </task>


/*
int main(void)
{
    initializeList();
    while(1)
    {
        printf("\n1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. (Added from homework). 5. Print. 6. exit.\n");

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
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4)
        {
            int option;
            printf("1. Get length 2. Insert item at 3. Delete last\n4. Clear 5. Delete all\n");
            scanf("%d", &option);
            if(option == 1)
            {
                printf("Length of the list : %d\n", getLength());
            }
            else if(option==2)
            {
                printf("Enter position and item : ");
                int item, pos;
                scanf("%d %d", &pos, &item);
                insertItemAt(pos, item);
            }
            else if(option==3)
            {
                deleteLast();
            }
            else if(option == 4){
                clear();
            }
            else if(option == 5){
                deleteAll();
            }
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

}
*/
