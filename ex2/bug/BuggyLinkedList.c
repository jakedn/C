#include<stdio.h>
#include<stdlib.h>

typedef struct node nodeStruct;

struct node
{
    int data;
    nodeStruct *next;
};

nodeStruct *head;   //head wasnt defined properly
int sizeOfNodes;

/**
 * adds the data in the last place of the list
 * @param dataToAdd the data to add
 */
void addToEnd(int dataToAdd)
{
    nodeStruct *temp, *right;
    temp = (struct node *)malloc(sizeof(struct node));
    //temp->data = (int) malloc(sizeof(int));
    //the above line was taken out because memory is already allocated in nodeStruct
    //for the data no need for another malloc that leads to memory leakage
    temp->data = dataToAdd;
    right = (struct node *)head;

    while(right->next != NULL)
        right = right->next;

    right->next = temp;
    right = temp;
    right->next = NULL;
}

/**
 * adds the data in the first place of the list
 * @param dataToAdd the data to add
 */
void addFirst(int dataToAdd)
{
    nodeStruct *tempNode;
    tempNode = (struct node *)malloc(sizeof(struct node));
    //tempNode->data = (int) malloc(sizeof(int));
    //the above line was taken out because memory is already allocated in nodeStruct
    //for the data no need for another malloc that leads to memory leakage
    tempNode->data = dataToAdd;
    if (head == NULL)
    {
        head = tempNode;
        head->next = NULL;
    }
    else
    {
        //we need to save the old heads address first otherwise we lose the chain of the linked list
        //the way it was before is we had tempnode==head and tempnode->next==tempnode
        nodeStruct *temp = head;
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
    nodeStruct *temp, *left, *right;
    right = head;

    // the for loops contents only had the left=right line in it so it did that place to add timesso i fixed the
    // loop contents also there was a logic error placeTOAdd is index of the new node that needs to be added
    // so we need to skip exacly placeToAdd nodes from the begginning not placeToAdd+1 nodes like was written
    for(i = 0; i < placeToAdd; i++)
    {
        left = right;
        right = right->next;
    }
    temp = (struct node *)malloc(sizeof(struct node));
    //temp->data = (int) malloc(sizeof(int));
    //the above line was taken out because memory is already allocated in nodeStruct
    //for the data no need for another malloc that leads to memory leakage
    temp->data = dataToAdd;
    left->next = temp;
    left = temp;
    left->next = right;
    return;//TODO
}


/**
 * inserts a new data number
 * the data is inserted in ascending order, from the lowest to highest
 * @param dataToAdd the data to insert
 * @param numberOfNodes the current number of nodes
 */
void insert(int dataToAdd, int *numberOfNodes)
{
    int c = 0;
    nodeStruct *temp;
    temp = head;
    if(temp == NULL)
    {
        addFirst(dataToAdd);
    }
    else
    {
        //the next loop went into an infinite loop without the correction made (stated below)
        //because we can get to a temp != null can the if condition wont trigger
        while(temp != NULL)
        {
            if(temp->data < dataToAdd)
            {
                c++;
            }
            //CORRECTION: i moved the line below outside the if statement so we continue down the chain
            //regardless of the if statement and the loop will terminate eventually
            temp = temp->next;
        }

        if(c==0)
        {
            addFirst(dataToAdd);
        }

        else if(c < *numberOfNodes)
        {
            //c represents the index of the linked list (starting from 0) of where data needs to be put
            //this is because it is the amount of nodes we skipped from the beginning
            //so i took out the ++
            addInPlace(dataToAdd, c);
        }
        else
            addToEnd(dataToAdd);
    }
    // we need to add one from what numberofnodes points to not numberofnodes itself i added a star
    // parentesis added to add 1 to what is pointer too and not the pointer
    (*numberOfNodes)++;
}

// didnt have return comment so i added. and also added return values
/**
 * deletes the first node with the number num
 * @param dataToDelete the data to delete
 * @param numberOfNodes the number of nodes
 * @return 1 on successful removal and 0 otherwise
 */
int deleteNode(int dataToDelete,int *numberOfNodes)
//delete is keyword in C cant be name of function so renamed to deleteNode
{
    nodeStruct *temp, *prev;
    temp = head;
    while(temp != NULL)
    {
        if(temp->data == dataToDelete)
        {
            if(temp == head)
            {
                head=temp->next;
                free(temp);

            }
            else
            {
                prev->next = temp->next;
                free(temp);
            }
            //we need to subtract one from what numberofnodes points to not numberofnodes itself i added a star
            //added peretesis also to make sure it subtracts from the value pointer to and not the pointer
            (*numberOfNodes)--;
            //delete successful so i added the return value line below
            return 1;
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }
    //if we got here we didnt delete anything so i return 0
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
    if(startingNodeToPrint == NULL)
    {
        return;
    }
    while(startingNodeToPrint!=NULL)
    {
        printf("%d --> ",startingNodeToPrint->data);
        startingNodeToPrint=startingNodeToPrint->next;
    }
    printf("NULL\n");
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
        deleteNode(i,&sizeOfNodes);
    }
    display(head);
    for (int i=0;i<100;i++){
        deleteNode(i,&sizeOfNodes);
    }
    display(head);
}



int  main()
{

    basicTest();
    hardTest();

    return 0;
}