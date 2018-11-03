#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <new>
using namespace std;

class Stack
{
    ofstream cout1;
    int max;
    int top;
    int *a;
public:
    Stack(int length)
    {
        cout1.open("task1.out");
        max = length-1;
        top = -1;
        a = new int[length];
    }

    void push(int num)
    {
        if(top == max)
            cout1<<"overflow"<<endl;
        else
        {
            top++;
            a[top] = num;
            cout1<<"pushed "<<num<<endl;
        }
    }

    void pop()
    {
        if(top == -1)
            cout1<<"underflow"<<endl;
        else
        {
            top--;
            cout1<<"popped "<<a[top+1]<<endl;
        }
    }

    void search(int num)
    {
        int found_num = 0;
        for(int i=0; i<=top; i++)
        {
            if(a[i] == num)
            {
                found_num = 1;
                break;
            }
        }
        if(found_num == 0)
            cout1<<"not found "<<num<<endl;
        else
            cout1<<"found "<<num<<endl;
    }

    void display()
    {
        for(int i=top; i>=0; i--)
            cout1<<a[i]<<" ";
        cout1<<endl;
    }
};

class Queue
{
    ofstream cout2;
    int max;
    int *a;
    int last;
public:
    Queue(int length)
    {
        max = length-1;
        last = -1;
        a = new int[length];
        cout2.open("task2.out");
    }

    void enqueue(int num)
    {
        if(last == max)
            cout2<<"overflow"<<endl;
        else
        {
            last++;
            a[last] = num;
            cout2<<"enqueued "<<num<<endl;
        }
    }

    void dequeue()
    {
        if(last == -1)
            cout2<<"underflow"<<endl;
        else
        {
            cout2<<"dequeued "<<a[0]<<endl;
            for(int i=0; i<last; i++)
                a[i] = a[i+1];
            last--;
        }
    }

    void search(int num)
    {
        int found_num = 0;
        for(int i=0; i<=last; i++)
        {
            if(a[i] == num)
            {
                found_num = 1;
                break;
            }
        }
        if(found_num == 0)
            cout2<<"not found "<<num<<endl;
        else
            cout2<<"found "<<num<<endl;
    }

    void display()
    {
        for(int i=0; i<=last; i++)
            cout2<<a[i]<<" ";
        cout2<<endl;
    }
};

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

class DoublyLinkedList
{
    ofstream cout3;
    Node *head;
public:
    DoublyLinkedList()
    {
        head = NULL;
        cout3.open("task3.out");
    }

    void insert(int num)
    {
        Node *temp = new Node;
        //To insert if there are no elements
        if(head == NULL)
        {
            temp->prev = NULL;
            temp->data = num;
            temp->next = NULL;
            head = temp;
        }
        //To insert if there are elements
        else
        {
            temp->prev = NULL;
            temp->data = num;
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
        cout3<<"inserted "<<num<<endl;
    }

    void dele(int num)
    {
        Node *temp = head;
        int found_num = 0;
        while(temp != NULL)
        {
            if(temp->data == num)
            {
                found_num = 1;
                break;
            }
            else
                temp = temp->next;
        }
        if(found_num == 0)
            cout3<<"cannot delete "<<num<<endl;
        //To delete first element
        else if (temp == head)
        {
            head = temp->next;
            (temp->next)->prev = NULL;
            delete temp;
            cout3<<"deleted "<<num<<endl;
        }
        //To delete last element
        else if (temp->next == NULL)
        {
            (temp->prev)->next = NULL;
            cout3<<"deleted "<<num<<endl;
            delete temp;
        }
        //To delete any other element
        else
        {
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            cout3<<"deleted "<<num<<endl;
            delete temp;
        }
    }

    void search(int num)
    {
        Node *temp = head;
        int found_num = 0;
        while(temp != NULL)
        {
            if(temp->data == num)
            {
                found_num = 1;
                break;
            }
            else
                temp = temp->next;
        }
        if(found_num == 0)
            cout3<<"not found "<<num<<endl;
        else
            cout3<<"found "<<num<<endl;
    }

    void display()
    {
        Node *temp = head;
        while(temp != NULL)
        {
            cout3<<temp->data<<" ";
            temp = temp->next;
        }
        cout3<<endl;
    }
};

int main(int argc, char *argv[])
{
    ifstream cin1(argv[1]);
    string l = argv[2];
    int length = stoi(l);

    istream_iterator<string> itr(cin1);
    istream_iterator<string> eos;
    Stack s(length);
    Queue q(length);
    DoublyLinkedList d;
    while(itr != eos)
    {
        if(*itr == "+")
        {
            itr++;
            s.push(stoi(*itr));
            q.enqueue(stoi(*itr));
            d.insert(stoi(*itr));
        }
        else if (*itr == "-")
        {
            itr++;
            s.pop();
            q.dequeue();
            d.dele(stoi(*itr));
        }
        else if (*itr == "?")
        {
            itr++;
            s.search(stoi(*itr));
            q.search(stoi(*itr));
            d.search(stoi(*itr));
        }
        else if (*itr == "!")
        {
            s.display();
            q.display();
            d.display();
        }
        itr++;
    }
    return 0;
}
