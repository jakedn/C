#include<stdio.h>
#include<stdlib.h>

typedef struct node nodeStruct;

struct node
{
    int data;
    nodeStruct *next;
};

nodeStruct *head; //head wasnt defined properly
int sizeOfNodes;

/**
 * adds the data in the last place of the list
 * @param dataToAdd the data to add
 */
void addToEnd(int dataToAdd)
{
    nodeStruct *temp,*right;
    temp= (struct node *)malloc(sizeof(struct node));
    temp->data = (int*) malloc(sizeof(int));    //cast to int and not int*
    temp->data=dataToAdd;
    right=(struct node *)head;

    while(right->next != NULL)
        right=right->next;

    right->next =temp;
    right=temp;
    right->next=NULL;
}

/**
 * adds the data in the first place of the list
 * @param dataToAdd the data to add
 */
void addFirst(int dataToAdd)
{
    nodeStruct *tempNode;
    tempNode=(struct node *)malloc(sizeof(struct node));
    tempNode->data = (int*) malloc(sizeof(int));     //casted int not int*
    tempNode->data = dataToAdd;
    if (head == NULL)   //codestyle correction
    {     //code style correction
        head = tempNode;
        head->next = NULL;
    }
    else
    {   //codestyle correction
        //we need to save the old heads address first otherwise we lose the chain
        void *temp = head;
        head = tempNode;
        tempNode->next = temp;
    }

}

/**
 * adds a new data in a given place to add
 * @param dataToAdd the data to add
 * @param placeToAdd the place to add
 */
void addInPlace(int dataToAdd, int placeToAdd)
{
    int i;
    nodeStruct *temp,*left,*right;
    right=head;
    for(i=0;i<placeToAdd+1;i++)
        left = right;
        right = right->next;

    temp=(struct node *)malloc(sizeof(struct node));
    temp->data = (int) malloc(sizeof(int));
    temp->data=dataToAdd;
    left->next=temp;
    left=temp;
    left->next=right;
    return;
}


/**
 * inserts a new data number
 * the data is inserted in ascending order, from the lowest to highest
 * @param dataToAdd the data to insert
 * @param numberOfNodes the current number of nodes
 */
void insert(int dataToAdd,int *numberOfNodes)
{
    int c=0;
    nodeStruct *temp;
    temp=head;
    if(temp==NULL)
    {
        addFirst(dataToAdd);
    }
    else
    {
        while(temp!=NULL)
        {
            if(temp->data<dataToAdd) {
                c++;
                temp = temp->next;
            }

        }

        if(c==0) {
            addFirst(dataToAdd);
        }

        else if(c<*numberOfNodes){
            addInPlace(dataToAdd, ++c);
        }
        else
            addToEnd(dataToAdd);
    }
    numberOfNodes++;
}


/**
 * deletes the first node with the number num
 * @param dataToDelete the data to delete
 * @param numberOfNodes the number of nodes
 * @return
 */
int deleteNode(int dataToDelete,int *numberOfNodes)
//delete is keyword in C cant be name of function so renamed to deleteNode
{
    nodeStruct *temp, *prev;
    temp=head;
    while(temp!=NULL)
    {
        if(temp->data==dataToDelete)
        {
            if(temp==head)
            {
                head=temp->next;
                free(temp);

            }
            else {
                prev->next = temp->next;
                free(temp);
            }
            numberOfNodes--;
            return 1;

        }
        else
        {
            prev=temp;
            temp = temp->next;
        }
    }

    return 0;
}

/**
 * should print all the nodes in the linked list in this format:
 * number of nodes: <numberOfNodes>\n
 * <firstNodeData> --> <secondNodeData> --> .... <lastNodeData>\n
 * @param startingNodeToPrint the first node to print
 */
void  display(nodeStruct *startingNodeToPrint)
{
    printf("number of nodes: %d\n",sizeOfNodes);
    if(startingNodeToPrint==NULL)
    {
        return;
    }

    //here we print the last node as null this is a mistake because we want only the nodes with data
    while(startingNodeToPrint->next!=NULL)
    {
        printf("%d --> ",startingNodeToPrint->data);
        startingNodeToPrint=startingNodeToPrint->next;
    }
    printf("%d\n", startingNodeToPrint->data);
}




void basicTest(){
    int data0 = 0;
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    insert(data1,&sizeOfNodes);
    insert(data2,&sizeOfNodes);
    insert(data3,&sizeOfNodes);
    insert(data2,&sizeOfNodes);
    insert(data1,&sizeOfNodes);
    insert(data2,&sizeOfNodes);
    insert(data1,&sizeOfNodes);
    insert(data0,&sizeOfNodes);
    display(head);

    deleteNode(data1,&sizeOfNodes);
    deleteNode(data2,&sizeOfNodes);
    display(head);
    deleteNode(data2,&sizeOfNodes);
    deleteNode(data3,&sizeOfNodes);
    deleteNode(data2,&sizeOfNodes);
    display(head);
    deleteNode(data1,&sizeOfNodes);
    deleteNode(data1,&sizeOfNodes);
    deleteNode(data0,&sizeOfNodes);
    display(head);
}

void hardTest(){
    for (int i=0;i<100;i++){
        insert(i,&sizeOfNodes);
    }
    display(head);

    for (int i=0;i<100;i++){
        insert(i,&sizeOfNodes);
    }

    display(head);
    for (int i=0;i<100;i++){
        delete(i,&sizeOfNodes);
    }
    display(head);
    for (int i=0;i<100;i++){
        delete(i,&sizeOfNodes);
    }
    display(head);
}



int  main()
{

    basicTest();
    hardTest();

    return 0;
}