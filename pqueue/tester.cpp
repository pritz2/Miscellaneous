#include <iostream>
#include <string>
#include "priority_queue.h"
#include <queue>
using namespace std;

int main(int argc, char* argv[])
{
    //PriorityQueue<int> queue;
    
    PriorityQueue<int> queue;
    priority_queue<int> soln;
    
    srand(9999);
    for(int i = 0; i < 10000; ++i)
    {
        int key = rand() % 1000;
        queue.insert(key);
        soln.push(key);
    }
    
    // make sure we get elements back in reverse-sorted order
    for(int i=0; i<10000; i++)
    {
        int max = soln.top();
        soln.pop();
        if(queue.pop() != max)
        {
            //cout << "pop "<<i<<": "<< queue.pop() << endl;
            cout << endl << "YOU FAILED on iteration "<< i <<endl<< endl;
            //queue.printTree();
            break;
        }
        //if(i >=58 && i <= 61)
        //    queue.printTree();
        //queue.printTree();
        //ASSERT(queue.pop() == max);
    }
    
    //ASSERT(queue.isEmpty());
    
    int l, m;
    
    while (1)
    {
        cout<<"----------------------------"<<endl;
        cout<<"Operations on Fibonacci heap"<<endl;
        cout<<"----------------------------"<<endl;
        cout<<"1)Insert Element in the heap"<<endl;
        cout<<"2)Extract Maximum key node"<<endl;
        cout<<"3)Display Heap"<<endl;
        cout<<"4)Exit"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>l;
        switch(l)
        {
            case 1:
                cout<<"Enter the element to be inserted: ";
                cin >> m;
                queue.insert(m);
                break;
            case 2:
                cout << "Element is " << queue.pop()<< endl;
                break;
            case 3:
                cout << endl;
                queue.printTree();
                break;
            case 4:
                exit(1);
            default:
                cout<<"Invalid, try again"<<endl;
        }
    }
     
     /*
     cout << "Empty? " << queue.isEmpty() << endl;
     
     queue.printTree();
     for(int i=9; i > -1; i--)
         queue.insert(i);
     for(int i=0; i < 10; i++)
     {
         if(queue.pop() != 9-i)
             cout << "YOU FAILED AT i="<< i << endl;
     }
     
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     
     queue.insert(1);
     queue.insert(2);
     queue.insert(3);
     queue.insert(4);
     queue.insert(5);
     queue.insert(6);
     queue.insert(7);
     queue.insert(8);
     queue.insert(9);
     queue.insert(10);
     queue.insert(11);
     queue.insert(12);
     queue.insert(13);
     queue.insert(14);
     queue.insert(15);
     queue.insert(16);
     queue.insert(17);
     queue.insert(18);
     queue.insert(19);
     queue.insert(20);
     queue.insert(21);
     queue.insert(22);
     
     //cout << "top: " << queue.top() << endl;
     cout << "pop: " << queue.pop() << endl;
     //queue.printTree();
     
     //cout << "top: " << queue.top() << endl;
     cout << "pop: " << queue.pop() << endl;
     //queue.printTree();
    
     //cout << "top: " << queue.top() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     
     queue.insert(17);
     queue.insert(18);
     queue.insert(19);
     queue.insert(20);
     queue.insert(21);
     queue.insert(22);
     
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     //queue.printTree();
     
     //cout << "top: " << queue.top() << endl;
     cout << "pop: " << queue.pop() << endl;
     
     cout << "top: " << queue.top() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     cout << "pop: " << queue.pop() << endl;
     //cout << "top: " << queue.top() << endl;
    */
    return 0;
}