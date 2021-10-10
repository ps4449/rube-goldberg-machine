// * Classes and packages *
#include <iostream>
#include <fstream> 
#include <string.h>
#include <conio.h>
using namespace std;
// **
// ------------------------------
// * Global Variables *

int front = -1, rear = -1, top = -1, ssize = 0, sizeofData;
const int size = 1200;
char c;

// **
// ------------------------------
// * ADTs *

struct info
    //for queue (q) and stack (s)
{
    string firstName, lastName, age, dob;
}q[1200], s[1200];

struct nodeTree
    //for unordered tree
{
    struct info data;
    struct nodeTree* left;
    struct nodeTree* right;
};

struct nodeLink
    //for linked list
{
    struct info dataLink;
    nodeLink* next;
}*start, * ptr, * newptr, * r, * prevForInsertion, * ptrForInsertion;

// **
// ------------------------------
// * Framework of Data structures *

void enqueue(struct info element)
//queue
{
    if (rear == -1)
    {
        front = rear = 0;
        q[rear] = element;
    }
    else
    {
        rear++;
        q[rear] = element;
    }
}

void push(struct info element)
//stack
{
    top++;
    s[top] = element;
    ssize++;
}

nodeTree* createTree(struct info Data)
//unodered binary tree
{
    nodeTree* n = new nodeTree;
    n->data = Data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

nodeLink* createlink(struct info data)
//linked list
{
    ptr = new nodeLink;
    ptr->dataLink = data;
    ptr->next = NULL;
    return ptr;
}

// **
// ------------------------------
// * Cleaning functions *

void spaces(string a)
//To remove unnecessary spaces and insert necessary spaces
{
    int n = a.length();
    for (int i = 0; i < 10 - n; i++)
        cout << " ";
}

string removeComma(string str)
//To remove unformatted commas from interfering in the string
{
    int len = str.length();
    if (str[len - 1] == ',')
    {
        str[len - 1] = '\0';
    }
    return(str);
}

void lineBreak()
//To distinguish between outputs
{
    std::cout.fill('*');
    std::cout.width(127);
    std::cout << " " << '\n';
}

// **
// ------------------------------
// * Display functions *

void displayQueue() //for queue
{
    for (int i = front; i < rear; i++)
    {
        cout << "First Name: " << q[i].firstName;
        spaces(q[i].firstName);
        cout << "\tLast Name: " << q[i].lastName;
        spaces(q[i].lastName);
        cout << "\tAge: " << q[i].age;
        spaces(q[i].age);
        cout << "\tDate of birth: " << q[i].dob << endl;
    }
}

void displayTree(struct info data) //for unordered binary tree
{
    cout << "First Name: " << data.firstName;
    spaces(data.firstName);
    cout << "\tLast Name: " << data.lastName;
    spaces(data.lastName);
    cout << "\tAge: " << data.age;
    spaces(data.age);
    cout << "\tDate of birth: " << data.dob << endl;
    spaces(data.dob);
}

void displayLink(nodeLink* np)
//for linked list
{
    cout << "Linked list : \n";
    while (np != NULL)
    {
        displayTree(np->dataLink);
        np = np->next;
    }
}

// **
// ------------------------------
// * PART 1: Reading input from file *

/* Here, the file name is sample.txt and
there are certain names, ages and dates of birth
that need to be read by our program. */

void readFile()
//Function 1: To read file from user
{
    fstream fio;
    string filename;
    filename = "DSA.txt";
    int i = 0;
    string str[1200], word;

    int j = 0, k = 0;
    fio.open(filename.c_str());
    while (fio >> str[i])
    {
        if (str[i][str[i].length() - 1] == ',')
        {
            str[i][str[i].length() - 1] == '\0';
        }
        i++;
    }
    int n;
    n = i;

    int len;
    sizeofData = n / 4;
    for (i = 0; i < sizeofData; i++)
    {
        j = (i * 4);
        q[i].firstName = str[j];
        len = q[i].firstName.length();
        q[i].firstName[len - 1] = '\0';
        j++;
        q[i].lastName = str[j];
        len = q[i].lastName.length();
        q[i].lastName[len - 1] = '\0';
        j++;
        q[i].age = str[j];
        len = q[i].age.length();
        q[i].age[len - 1] = '\0';
        j++;
        q[i].dob = str[j];
        len = q[i].dob.length();
        q[i].dob[len] = '\0';
        enqueue(q[i]);
    }
    fio.close();
}

// * End of PART 1 *
// ------------------------------
// * PART 2: Insert read file elements into a queue data structure *

/* Part 2 consists of two main parts:
dequeuing elements into a stack, display them
and requeing them. */

void deQueue1() //Function 2: Used to dequeue, print and requeue each item
{
    struct info temp;
    temp = q[front];
    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front++;
    }
    cout << "First Name: " << temp.firstName;
    spaces(temp.firstName);
    cout << "\tLast Name: " << temp.lastName;
    spaces(temp.lastName);
    cout << "\tAge: " << temp.age;
    spaces(temp.age);
    cout << "\tDate of birth: " << temp.dob;

    cout << endl;
    enqueue(temp);
}

// * End of PART 2 *
// ------------------------------
// * PART 3: Reversing elements using stack *

/* Here, we use pop functions given by stack
to invert the queue and display it. */

void pop()
//Function 3: To pop elements that will be displayed in reverse order
{
    struct info temp;
    temp = s[top];
    top--;
    enqueue(temp);
}

void deQueue2()
//Function 4: To dequeue the items and requeue them to put it back into the queue
{
    struct info temp;
    temp = q[front];
    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front++;
    }
    enqueue(temp);
}

// * End of Part 3 *
// ------------------------------
// * PART 4: Transferring elements from queue to an unordered binary tree *

/* Here, we insert all the file items from
queue to binary tree. */

int max(int a, int b)
//Function 5.1.1: To check height of the tree after insertion
{
    return a > b ? a : b;
}

int height(nodeTree* root) //Function 5.1: To assign addresses based on binary tree insertion
{
    int h{};
    if (root == NULL)return 0;
    h += max(height(root->left), height(root->right));

    if (root->left != NULL)return h + 1;
    else if (root->right != NULL)return h + 1;
}

void insertTree(nodeTree* x, nodeTree* y)
//Function 5: To insert an element into the tree
{
    if (x->left == NULL)
    {
        x->left = y; return;
    }
    else if (x->right == NULL)
    {
        x->right = y; return;
    }
    else
    {
        if (height(x->left) < height(x->right))x = x->left;
        else x = x->right;
        insertTree(x, y);
    }
}

// * End of PART 4 *
// ------------------------------
// * PART 5: Unordered binary tree traversals *

/* This part deals with exploration related to
preorder and postorder traversals of an unordered binary tree. */

void preorder(nodeTree* root)
//Function 6: For preorder traversal of an unordered binary tree
{
    if (root == NULL)return;
    displayTree(root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(nodeTree* root)
//Function 7: For postorder traversal of an unordered binary tree
{
    if (root == NULL)return;
    postorder(root->left);
    postorder(root->right);
    displayTree(root->data);
}

// * End of PART 5 *
// ------------------------------
// * PART 6: Insert from a binary tree into Linked list *

/* Here, we shift the elements from an unordered binary tree to
a linked list using inorder traversal. */

void insertlink(nodeLink* np)
//Function 9: To insert item into linked list
{
    if (start == NULL)
    {
        start = r = np;
    }
    else
    {
        r->next = np;
        r = np;
    }
}

void inorder(nodeTree* root)
//Function 8: To input elements from binary tree in inorder traversal
{
    if (root == NULL)return;
    inorder(root->left);
    newptr = createlink(root->data);
    insertlink(newptr);
    inorder(root->right);
}

// * End of PART 6 *
// ------------------------------
// * PART 7: Use Quicksort method to sort items in linked list *

/* Here, we employ the quicksort algorithm that depends on pivoting one element
in an array or linked list to sort all the data given in the
current linked list on the basis of first name. */

nodeLink* getTail(nodeLink* cur)
//Function 10.1.2: Returns the last node of the passed list
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

int compare(string str1, string str2)
//Function 10.1.1(a): To compare both strings to sort them alphabetically in ascending order
{
    int i;
    for (i = 0; i < min(str1.length(), str2.length()); i++)
    {
        if ((int)str1[i] > (int)str2[i])
        {
            return 1;
            break;
        }
        else if ((int)str1[i] < (int)str2[i])
        {
            return 0;
            break;
        }
    }
    return 0;
}

nodeLink* partition(nodeLink* head, nodeLink* end, nodeLink** newHead, nodeLink** newEnd)
//Function 10.1.1: Partitions the list into sublists taking the last element as the pivot
{
    nodeLink* pivot = end;
    nodeLink* prev = NULL, * cur = head, * tail = pivot;

    while (cur != pivot)
    {
        if (compare(cur->dataLink.firstName, pivot->dataLink.firstName) != 1)
        {
            if ((*newHead) == NULL)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            nodeLink* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;
    (*newEnd) = tail;

    return pivot;
}

nodeLink* quickSortRecur(nodeLink* head, nodeLink* end)
//Function 10.1: To sort the list and sublist exclusive of the pivot
{
    if (!head || head == end)
        return head;

    nodeLink* newHead = NULL, * newEnd = NULL;
    nodeLink* pivot = partition(head, end, &newHead, &newEnd);
    if (newHead != pivot)
    {
        nodeLink* tmp = newHead;

        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;
}

void quickSort(nodeLink** headRef)
//Function 10: Driver function for quickSort 
{
    *headRef = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

// * End of PART 7 *
// ------------------------------
// * PART 8: User interaction and input *

/* In this part we take similar input as given in the file
from the user and integrate it into our previously sorted
linked list. */

void placeInLinkedList(struct nodeLink* newEntry)
//Function 12: Add in sorted linked list
{
    prevForInsertion = start;
    ptrForInsertion = start;
    while (ptrForInsertion != NULL)
    {
        if (compare(newEntry->dataLink.firstName, ptrForInsertion->dataLink.firstName))
        {
            prevForInsertion = ptrForInsertion;
            ptrForInsertion = ptrForInsertion->next;
        }
        else
        {
            break;
        }
    }
    newEntry->next = ptrForInsertion;
    prevForInsertion->next = newEntry;
}

void inputFromTerminal()
//Function 11: Take input from user in terminal window
{
    string a, b, c, d;
    struct info newdata;
    cout << "Enter data in the format:" << endl;
    cout << "First name, last name, age, date of birth" << endl;
    cin >> a >> b >> c >> d;
    a = removeComma(a);
    newdata.firstName = a;
    b = removeComma(b);
    newdata.lastName = b;
    c = removeComma(c);
    newdata.age = c;
    d = removeComma(d);
    newdata.dob = d;
    newptr = createlink(newdata);
    placeInLinkedList(newptr);
}

// * End of PART 8 *
// ------------------------------
// * PART 9: Appending all the functions *

/* This part takes over the entire execution by arranging all the functions
in 8 separate functions. This helps to hide the unimportant information
from the user. */

void part1()
{
    lineBreak();
    cout << "Reading given file." << endl;
    readFile();
    cout << endl;
    cout << "Press enter for processing." << endl;
    getchar();
}

void part2()
{
    cout << endl;
    lineBreak();
    cout << "To dequeue, print and requeue items from file:" << endl;
    int x = front, y = rear;
    while (x <= y)
    {
        deQueue1(); //Function 2
        x++;
    }
    cout << "\nPress enter for processing." << endl;
    getchar();
}

void part3()
{
    cout << endl;
    lineBreak();
    cout << "Reversed list:" << endl;
    int x = front, y = rear;
    while (x <= y)
    {
        push(q[x]);
        x++;
    }
    x = ssize + 1;
    front = rear = -1;
    while (x != 0)
    {
        pop();
        x--;
    }
    displayQueue();

    //dequeue and enqueue again
    x = front;
    y = rear;
    while (x <= y)
    {
        deQueue2(); //Function 4
        x++;
    }
    cout << "\nPress enter for processing." << endl;
    getchar();
}

void part45and6()
{
    nodeTree* treeRoot = NULL;
    int ctr = front;
    for (int i = 0; i < sizeofData; i++)
    {
        if (i == 0)
        {
            treeRoot = createTree(q[ctr]);
        }
        else
        {
            ctr++;
            nodeTree* y;
            y = createTree(q[ctr]);
            insertTree(treeRoot, y); //Function 5
        }
    }

    cout << endl;
    lineBreak();
    cout << "\nPreorder traversal of tree:\n";
    preorder(treeRoot); //Function 6 (prints interally)
    cout << "\nPress enter for processing." << endl;
    getchar();

    cout << endl;
    lineBreak();
    cout << "\nPostorder traversal of tree:\n";
    postorder(treeRoot); //Function 7 (prints internally) 
    cout << "\nPress enter for processing." << endl;
    getchar();

    cout << endl;
    lineBreak();
    cout << "\nData transferred to linked list:\n";
    inorder(treeRoot); //Function 8
    displayLink(start);

    cout << endl;
    cout << "Press enter for processing." << endl;
    getchar();
}

void part7()
{
    cout << endl;
    lineBreak();
    cout << "\nList after sorting:\n";
    quickSort(&start); //Function 10
    displayLink(start);
    cout << "\nPress enter for processing." << endl;
    getchar();
}

void end()
{
    cout << endl;
    lineBreak();
    cout << "You have reached end of processing." << endl;
    cout << "Thank you for trying our API!" << endl;
    system("pause");
}

void part8()
{
    cout << endl;
    lineBreak();
    cout << "Insertion of data from user." << endl;
    while (c != '3')
    {
        cout << "\nPress 1 to enter new data." << endl;
        cout << "Press 2 to display updated list" << endl;
        cout << "Press 0 to exit." << endl;
        cin >> c;
        switch (c)
        {
        case '0': end(); c = '3';
            break;
        case '1': inputFromTerminal(); //Function 11
            cout << endl;
            break;
        case '2': lineBreak();
            cout << "List after addition of new elements." << endl;
            displayLink(start);
            break;
        }
    }
}

// * End of PART 9 *
// ------------------------------
// * PART 10: Appending all the functions *

int main()
//Function 16: main() to execute the entire program
{
    cout << "\t\t\t\t\tWelcome to our Rube-Goldberg's Machine\n";
    part1();
    part2();
    part3();
    part45and6();
    part7();
    part8();
    return 0;
}