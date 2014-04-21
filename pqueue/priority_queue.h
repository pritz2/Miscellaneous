/**
 * @file priority_queue.h
 */

#ifndef _PQUEUE_H_
#define _PQUEUE_H_

/**
 * Implements the max priority queue ADT.
 *
 * The implementation is up to you, but you must complete all the given
 *  public functions. You will need to add some member variables and private
 *  helper functions.
 */
template <class T>
class PriorityQueue
{
public:
    /**
     * Constructor: creates an empty priority queue.
     */
    PriorityQueue();
    
    /**
     * Destructor: empties the tree.
     */
    ~PriorityQueue();
    
    /**
     * Copy Constructor
     */
    //PriorityQueue(const PriorityQueue & other);
    
    /**
     * Inserts the given value into the queue.
     *
     * @param value The value to be inserted.
     */
    void insert(const T & value);
    
    /**
     * Removes the highest value (and its associated data) from the
     *  queue.
     *
     * @return A copy of the removed (maximum) element
     */
    T pop();
    
    /**
     * Returns the highest value from the queue. Does NOT remove it.
     *
     * @return A copy of the maximum element
     */
    const T top() const;
    
    /**
     * Determines if the queue is empty. Should be O(1).
     *
     * @return A boolean value indicating whether the queue is
     *  empty.
     */
    bool isEmpty() const;
    
    void printTree();
    
private:
    
    class node{
    public:
        node(){
            child = NULL;
            data = T();
            //marked = false;
            rank = 0;
        }
        //node* parent;
        node* child;
        node* left;
        node* right;
        T data;
        //bool marked;
        int rank;
    };
    
    node * max;
    int numElems;
    int numroots;
    
    //    node* copy(node* here);
    void clear();
    
    void print(node* here);
    
};

#include "priority_queue.cpp"
#endif