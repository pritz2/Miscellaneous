#include "priority_queue.h"

using namespace std;

template <class T>
PriorityQueue<T>::PriorityQueue()
{
    numElems = 0;
    max = NULL;
    numroots = 0;
}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{
    clear();
}

template <class T>
void PriorityQueue<T>::clear()
{
    while(!isEmpty())
        pop();
}
/*
template <class T>
PriorityQueue::PriorityQueue(const PriorityQueue & other)
{
    if(this != other)
    {
        this->clear();
        this.insert(other.max);
        
    }
    return *this;
}

template <class T>
PriorityQueue::node* PriorityQueue::copy(node* here)
{
    if(here == NULL)
        return;
    node* temp = new node* here;
    if(max->child != NULL)
    {
        temp->child = copy(here->child);
    }
    here = here->right;
    while(here != temp)
    {
        temp->right = copy(here);
        copy(here->child);
        temp = temp->right;
    }
}
*/
template <class T>
void PriorityQueue<T>::insert(const T & value)
{
    // Construct the new node
    node* newnode = new node();
    newnode->data = value;
    newnode->right = newnode;
    newnode->left = newnode;
    
    // Inserts new node in the circular root list
    if(!isEmpty())
    {
        newnode->right = max;
        newnode->left = max->left;
        max->left->right = newnode;
        max->left = newnode;
    }
    if(max == NULL || value > max->data)
        max = newnode;
    numElems++;
    numroots++;
}

template <class T>
T PriorityQueue<T>::pop()
{
    // Get return value
    if(isEmpty())
        return T();
    T ret = max->data;
    node* temp1;
    
    /* Append Children to root list */
    
    if(max->child == NULL && max->right == max)
    {
        delete max;
        numroots--;
        numElems--;
        return ret;
    }
    // Case 1: max has no children
    else if(max->child == NULL)
    {
        max->right->left = max->left;
        max->left->right = max->right;
        temp1 = max;
        max = max->right;
        delete temp1;
        numroots--;
    }
    // Case 2: max, the only root, has children
    else if(max->right == max)
    {
        node* temp = max;
        max = max->child;
        delete temp;
        temp1 = max->right;
        while(temp1 != max)
        {
            numroots++;
            temp1 = temp1->right;
        }
    }
    // Case 3: max, one of several roots, has children
    else
    {
        max->right->left = max->child->left;
        max->left->right = max->child;
        max->child->left->right = max->right;
        max->child->left = max->left;
        
        temp1 = max->left->right;
        while(temp1 != max->right)
        {
            numroots++;
            temp1 = temp1->right;
        }
        node* temp = max;
        max = max->child;
        delete temp;
        numroots--;
    }
    /*
     if(max == NULL)
     {
     numElems --;
     return ret;
     }
     */
    /* Update max and Consolidate */
    
    node* ranks[200];
    for(int i=0; i< 200; i++)
        ranks[i] = NULL;
    node* curr = max;
    
    // First node put in to ranks array
    ranks[curr->rank] = curr;
    curr = curr->right;
    
    // While loop will need to run through every root once,
    // so we increment i only on loop iterations where we
    // do not merge 2 subtrees
    int i=1;
    int number = numroots;
    while(i< number)
    {
        // Update max
        if(curr->data >= max->data)
            max = curr;
        
        /* Consolidate */
        
        // curr is the only subtree so far with rank curr->rank
        if(ranks[curr->rank] == NULL)
        {
            ranks[curr->rank] = curr;
            curr = curr->right;
            i++;
        }
        // Rank array spot is filled!
        else if(ranks[curr->rank] != curr)
        {
            temp1 = ranks[curr->rank];
            ranks[curr->rank] = NULL;
            
            // The first tree was larger than curr
            if(temp1->data > curr->data)
            {
                // Take curr out of root list
                curr->right->left = curr->left;
                curr->left->right = curr->right;
                // Has no children:
                if(temp1->child == NULL)
                {
                    temp1->child = curr;
                    curr->right = curr;
                    curr->left = curr;
                }
                // Has children:
                else
                {
                    curr->left = temp1->child;
                    curr->right = temp1->child->right;
                    temp1->child->right->left = curr;
                    temp1->child->right = curr;
                }
                temp1->rank ++;
                curr = temp1;
            }
            // curr is larger than the first tree
            else
            {
                //take curr out of root list
                temp1->right->left = temp1->left;
                temp1->left->right = temp1->right;
                // Has no children:
                if(curr->child == NULL)
                {
                    curr->child = temp1;
                    temp1->right = temp1;
                    temp1->left = temp1;
                }
                // Has children:
                else
                {
                    temp1->left = curr->child;
                    temp1->right = curr->child->right;
                    curr->child->right->left = temp1;
                    curr->child->right = temp1;
                }
                curr->rank ++;
            }
            numroots--;
        }
        // curr points to a tree already in my array.
        // In theory, should never happen.
        else
        {
            //i++;
            curr = curr->right;
        }
    }
    
    numElems--;
    return ret;
}

template <class T>
const T PriorityQueue<T>::top() const
{
    if(isEmpty())
        return T();
    return max->data;
}

template <class T>
bool PriorityQueue<T>::isEmpty() const
{
    return numElems==0;
}


template <class T>
void PriorityQueue<T>::printTree()
{
    cout <<"Tree currently has " << numroots << " roots, with " << numElems << " total elements." << endl;
    print(max);
}
 
template <class T>
void PriorityQueue<T>::print(node* here)
{
    if(here == NULL)
        return;
    cout << "Start children:" << endl;
    node* temp = here;
    cout << here->data << endl;
    if(max->child != NULL)
    {
        print(here->child);
    }
    here = here->right;
    while(here != temp)
    {
        cout << here->data << endl;
        print(here->child);
        here = here->right;
    }
    cout << "End children" << endl;
}