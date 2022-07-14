#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMenu();
struct node* MakeEmpty(struct node* L);
void DeleteList(struct node * L);
struct node* readFile(struct node* x);
void Insert(char x[],struct node* L,struct node* p);
void printStrings(struct node* x);
struct node* sortStrings(struct node* L);
struct node* sortChar(struct node* L,int NumOfDigits,struct node* b[],struct node* alpha[]);
int IsEmpty(struct node* x);
int IsLast(struct node* p,struct node* L);
int getMax(struct node* L);

//Linked List
struct node // Define a struct which contain a pointer leads to the second struct & a place to the string which will put
{
    char Data[15] ; // 15 is the max
    struct node* Next ;
};

int main()
{

    struct node* head = NULL; // Define a struct node that we will start with
    head = MakeEmpty(head) ;
    char Option[2] ;    // to scan the option
    do //while loop still unless the user did not select Option 4
    {
        printMenu(); // Print the Menu everytime the user didnt break the loop
        scanf("%s", Option) ; // scan the option number
        if(strlen(Option) > 1)    // if the option more than one character so it will be wrong, because our options are 1,2,3,4
            strcpy(Option,"0") ; //  and this will help us to get rid of the wrong scan like "2d"
        switch(atoi(Option)) // to know which option the user select
        {
        case 1 : // if option 1 selected..
            head = NULL; //call function to read the file
            head =readFile(head);
            break; // break the switch cases and execute the loop one more
        case 2 : // if option 2 selected..
            printStrings(head); // call function to print the held strings in Linked List(head)
            break;
        case 3 : // if option 3 selected..
            head = sortStrings(head); // call function to sort the held strings in Linked List(head)
            break;
        case 4 :    // if option 4 selected, do nothing but break the switch cases
            break; // so it will not execute the statements in 'default'
        default:
            printf("Sorry but this thing doesn't exist!\n");
        }
    }
    while(atoi(Option) != 4); // to exit the app
    return 0;
}

void printMenu() // just print
{
    printf("------------------- Menu -------------------\n");
    printf("Write the number of the option that you want\n\n");
    printf("           1. Read the input file.\n");
    printf("            2. Print the strings.\n");
    printf("             3. Sort the strings.\n");
    printf("              4. Exit the app.\n");
}

struct node* MakeEmpty(struct node* L) // to ensure that the Linked List L is empty
{
    if(L != NULL)         // if not empty..
        DeleteList( L ); // call function to delete the Linked List as a data and as a struct
    L = (struct node*)malloc(sizeof(struct node)); // give the Linked List(head) a new place with struct node size
    if(L == NULL) // if there is no place for the Linked List, print that
        printf("Out of memory!\n");
    L->Next = NULL; // make the pointer in the struct node points on NULL
    return L;
}

void DeleteList(struct node* L)
{
    struct node* P; // to leads to the struct node to delete
    struct node* temp; // to keep catching the next struct node that will be deleted after P get rid of its struct node
    P = L->Next;
    L->Next = NULL;
    while(P != NULL) // while there is a struct node to delete, do the next statements
    {
        temp = P->Next; // temp catchs the next struct
        free(P); // P get rid of the current struct node,
        P=temp; // and look to the next struct node that will be deleted if it is not NULL
    }
}

struct node* readFile(struct node* x) // x is the node that will points on the nodes which will be read from the file
{
    char temp[100]; // took a place for the string that will be scanned
    x = MakeEmpty(x) ; // to prevent the repeated reading for the same inputs
    struct node* p = x; // P points on the struct node that we will add the inputs for it after scanning the file
    FILE* in = fopen("Input.txt","r"); // select the file to open, and scan it later
    if(in == NULL) // if there is no near file as the previous name, print that
        printf("Error in opening the file!\n");
    else // otherwise..
        while(fscanf(in,"%s\n",temp)!=EOF) // scan a single line. if it is not empty, continue
        {
            if(strlen(temp)>15) // if the string more than 15 characters, print that it is not the required,
            {                  // make the struct node empty and returned it ; to edit the problem and continue
                printf("Can't read a string more than 15 character! Please Edit it\n");
                MakeEmpty(x);
                return x;
            }
            Insert(temp,x,p); // this function will be called when the input is correct and less than 15 characters
            p = p->Next; // it is useful to select where the next struct node(if exists) will be added in L.L X
        }
    printf("The Input file has been read\n"); // print when this function read without problems
    fclose(in); // close the file we opened before
    return x;
}

void Insert(char x[],struct node* L,struct node* p) // x contains the data of the node we will insert in L.L L after node P
{
    struct node* temp ; // define a struct node
    temp = (struct node*)malloc(sizeof (struct node)); // give it a place
    strcpy(temp->Data,x); // put the required data in the node
    temp->Next=p->Next; // it will lead to the node 3 that we will insert node 2 after the node 1 which points on node 3
                       // and to not loss the rest of the struct nodes
    p->Next=temp; // node 1's pointer leads to the new node (2)
}

void printStrings(struct node* x)
{
    struct node* p = x ; // P points on L.L X
    if(IsEmpty(x)) // when X is empty it will not print any thing
        printf("Empty!\n");
    else // otherwise..
        do // do-while P is not the last struct node in L.L X
        {
            p=p->Next; //P points in the next struct node and print its data
            printf("%s\t",p->Data);
        }
        while(!IsLast(p,x));
    printf("\n");
}

struct node* sortStrings(struct node* L)
{
    if(IsEmpty(L)) // if L.L L is empty, print that and returned it
    {
        printf("Can't sort a Strings not available!\n");
        return L;
    }
    struct node* alpha[64]; // define the struct nodes which will use to sort in radix sort
    struct node* b[64]; // define the struct nodes which every node will point on where the next
                        // node will be inserted in every alpha node
    for(int i = 0 ; i < 64 ; i++) // to make the previous struct nodes empty and have their places
    {
        alpha[i] = NULL;
        b[i] = NULL;
        alpha[i] = MakeEmpty(alpha[i]) ;
        b[i] = MakeEmpty(b[i]) ;
        b[i] = alpha[i] ; //initially, every 'b' node will point on every 'alpha' node
    }
    struct node* temp = L; //define a struct node to point on L.L L, make it easy to deal without lose data
    int max=getMax(temp); // and to get the string which has the max number of characters
    for(int i = max; i > 0; i--) // to sort every character along the tallest string individually
        temp = sortChar(temp,i,b,alpha); // make temp points on the sorted (by char.) L.L everytime

    printf("The string sorted!\n"); // print when this function sort without problems
    return temp; // return the sorted L.L
}

struct node* sortChar(struct node* L,int NumOfDigits,struct node* b[],struct node* alpha[])
{
    int X; // to store the ASCII code of the character and treat with it
    struct node* temp = L->Next; // temp points on the first node
    while(temp!=NULL) // while there is a node..
    {
        if(strlen(temp->Data)<NumOfDigits) // if the node's string is short to deal with it, insert it in the first L.L(alpha[0])
        {
            Insert(temp->Data,alpha[0],b[0]); // this will give the shortest words the precedence to become before the tall ones
            b[0] = b[0]->Next;               // b[0] points on where -if- the next insert will be executed in 'alpha[0]'
        }
        else
        {
            X = temp->Data[NumOfDigits-1];
            if(X>=48&&X<=57) // if the node's selected character (to sort) is a number(0,1,2,..,9)..
            {                                             // it will be inserted on alpha[1]-alpha[65],
                Insert(temp->Data,alpha[X-47],b[X-47]);  // it depends on its value(the less one is first)
                b[X-47]=b[X-47]->Next; // b points on where -if- the next insert will be executed in 'alpha' for each L.L
            }                                   // if the node's selected character (to sort) is a letter...
            else if(X>=65&&X<=90)              // if it is Capital..
            {
                Insert(temp->Data,alpha[2*(X-65)+11],b[2*(X-65)+11]); /* insert it where it before the small letter
                from the same family and after the previous letter's family according to the alphabet, also after the numbers */
                b[2*(X-65)+11]=b[2*(X-65)+11]->Next; // to make the next insertion -if exists- know where to insert
            }
            else if(X>=97&&X<=122)         // if it is small..
            {
                Insert(temp->Data,alpha[2*(X-96)+10],b[2*(X-96)+10]); /* insert it where after the capital letter
                from the same family and after the previous letter's family according to the alphabet, also after the numbers */
                b[2*(X-96)+10]=b[2*(X-96)+10]->Next; // to make the next insertion -if exists- know where to insert
            }
            else
            {   // if the node's character is neither letter nor number, insert it in the last L.L
                Insert(temp->Data,alpha[63],b[63]); /* so it will be the tail of the sorting
                with ignore sort these things comparing with each other */
                b[63]=b[63]->Next; // to make the next insertion -if exists- know where to insert
            }
        }
        temp=temp->Next; // points the next to check if there is a next node
    }

    struct node* sorted = NULL;  // define a new head which will carry the new nodes after sort them by a specific character
    sorted = MakeEmpty(sorted); // & and give it a place
    b[0] = sorted; // make -anynode- a node to point on it
    for(int i = 0 ; i < 64 ; i++) // for-loop to go by the 64L.L and get the original nodes
    {
        temp = alpha[i];    // temp points on each L.L
        if(!IsEmpty(temp)) // & check if it has a next nodes..
            do            // go by these nodes and execute the next statements
            {
                temp = temp->Next; // temp points on the next node in L.L that has a node\s
                Insert(temp->Data,sorted,b[0]); // insert the pointed node in the new L.L 'sorted'
                b[0]=b[0]->Next; // to make the next insertion -if exists- know where to insert
            }
            while(!IsLast(temp,alpha[i]));
    }
    for(int i = 0 ; i < 64 ; i++) // make the nodes empty for the next sorting -if exists-
    {
        b[i] = MakeEmpty(b[i]);
        alpha[i] = MakeEmpty(alpha[i]);
        b[i] = alpha[i] ;
    }
    return sorted; //return our new L.L that is sorted by a specific digit
}

int IsEmpty(struct node* L) // boolean function which checks if the L.L L is empty or no
{
    return L->Next == NULL ; // if the head does not point on node, so it is empty (1) else (0)
}

int IsLast(struct node* p,struct node* L) // boolean function which checks if the node P is the last node in L.L L or no
{
    return p->Next == NULL; // 0 if it has a next node, 1 if there is no next node
}

int getMax(struct node* L) // to get the max number of the characters in a string in L.L L
{
    struct node* temp = L->Next;
    int max=strlen(temp->Data); // max has the number of the characters of the first node
    while(temp!=NULL) // while there is a node..
    {
        if(strlen(temp->Data) > max)   // if it has a number of the characters more than the number that stored in 'max'..
            max = strlen(temp->Data); // store the number in 'max'
        temp=temp->Next; // to check if there is a next node
    }
    return max; // return the max number of the characters in L.L
}
