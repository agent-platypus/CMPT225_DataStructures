#ifndef QUEUET_H_INCLUDED
#define QUEUET_H_INCLUDED
#pragma once
#include <iostream>
#include <string>

template <class T>
class NodeT{
public:
T data;
NodeT* next;
NodeT* previous;
NodeT(T val, NodeT* nxt, NodeT* prev): data(val), next(nxt), previous(prev) {};
NodeT(T val): data(val), next(nullptr), previous(nullptr) {};
};

template <class T>
class QueueT{
public:
    QueueT();
    QueueT(const QueueT &Q);
    ~QueueT();
    QueueT<T> & operator=(const QueueT &Q);
    void enqueue(T val);
    T dequeue();
    void print() const;
    bool empty() const;
    int size() const;
    void concatenate(const QueueT<T> &Q, int n);
    QueueT merge(const QueueT<T> &Q);
    NodeT<T>* getFront() const;

private:
    NodeT<T>* front;
    NodeT<T>* back;
    int num;
    void copyNode(NodeT<T>* original, NodeT<T>* copy);
    void copyQueue(const QueueT<T> &Q);
    void full_delete();
};

//default constructor
template <class T>
QueueT<T>::QueueT()
{
    front = back = nullptr;
    num = 0;
}

//copy constructor
template <class T>
QueueT<T>::QueueT(const QueueT & Q)
{
    back = nullptr;
    front = nullptr;
    num = 0;
    copyNode(Q.back, back);
}

template <class T>
QueueT<T> & QueueT<T>::operator=(const QueueT &Q)
{
    //if the parameter object is not the calling object
    // (not a copy of itself)
    if(this != &Q)
    {
        full_delete();
        copyQueue(Q);
    }
    return *this;
}

//destructor that frees memory starting from the front node
template <class T>
QueueT<T>::~QueueT()
{
   full_delete();
}

//essentially insert back
template <class T>
void QueueT<T>::enqueue(T val)
{
    //check if queue is empty
    if(back == nullptr)
    {
        //create a single node that contains data = val
        NodeT<T>* temp = new NodeT<T>(val);
        back = temp;
        front = back;
        num++;
    }

    //check if the queue has only 1 node
    else
    {
        back->next = new NodeT<T>(val);
        back->next->previous = back;
        back = back->next;
        num++;
    }

}

//remove front and return contents of front
//decrement size of queue by 1
//and relink head to the next node
template <class T>
T QueueT<T>::dequeue()
{
    if(!empty())
        //if the queue is not empty
    {
    num--;
    NodeT<T>* temp = front;
    T front_data = front->data;
    front = front->next;
    delete temp;
    temp = nullptr;
    return front_data;
    }
}

//print method; print from front to back, iterate using next pointers
template <class T>
void QueueT<T>::print() const
{
    NodeT<T>* temp = front;
    while(temp != nullptr)
    {
        std::cout << temp->data << "  ";
        temp = temp->next;
    }
}

//check if queue is empty, returns true if empty, false if not
template <class T>
bool QueueT<T>::empty() const
{
    if(num == 0)
        return true;
    else
        return false;
}

//returns the size of the queue (return int num)
template <class T>
int QueueT<T>::size() const
{
   return num;
}

//concatenate function that combines the first n nodes in the parameter Queue onto
//the back of the calling object
//calling object should be the result of the concatenation
template <class T>
void QueueT<T>::concatenate(const QueueT & Q, int n)
{
    NodeT<T>* temp = Q.front;
    int true_num = 0;
    //checking if int n is a valid value/within the number of nodes in parameter queue
    if(n<0)
        return;
    if(n>Q.num)
        {
        true_num = Q.num;
        }
    else
        {
        true_num = n;
        }
    for(int i = 0; i<true_num; i++)
        {
        enqueue(temp->data);
        temp = temp->next;
        }
}

//merge function combines 2 queues in the following manner
//calling object = {a,b,c,d,e}, parameter = {r,s,t}, result = {a,r,b,s,c,t,d,e}
//returns a QueueT object
template <class T>
QueueT<T> QueueT<T>::merge(const QueueT<T> & Q)
{
    QueueT MergeObj;
    NodeT<T>* temp1 = this->front;
    NodeT<T>* temp2 = Q.front;

    //ensures loop iterates even if the size of queues are uneven
    while(temp1 != nullptr || temp2 != nullptr)
    {
        //inserting a node from the calling object then
        // a node from the parameter object
        if(temp1 != nullptr && temp2 != nullptr)
        {
        MergeObj.enqueue(temp1->data);
        MergeObj.enqueue(temp2->data);
        temp1 = temp1->next;
        temp2 = temp2->next;
        }
        if(temp1 != nullptr && temp2 == nullptr)
            //if the calling queue is bigger than the parameter queue
        {
            MergeObj.enqueue(temp1->data);
            temp1 = temp1->next;
        }
        if(temp1 == nullptr && temp2 != nullptr)
        // if the parameter queue is bigger than the calling queue
        {
            MergeObj.enqueue(temp2->data);
            temp2 = temp2->next;
        }
    }
    return MergeObj;
}

//returns front pointer of calling objects queue
template <class T>
NodeT<T>* QueueT<T>::getFront() const
{
    return front;
}

////////HELPER METHODS START HERE///////////

//helper method for freeing memory
template <class T>
void QueueT<T>::full_delete()
{
    NodeT<T>* temp = front;
    while(front != nullptr)
    {
        front = temp->next;
        delete temp;
        temp = front;
    }
    num = 0;
    front = back = nullptr;
}

//helper method for deep copying part 1
template <class T>
void QueueT<T>::copyQueue(const QueueT<T> &Q)
{
    back = nullptr;
    front = nullptr;
    num = 0;
    copyNode(Q.back, back);
}

//helper method for deep copying part 2
template <class T>
void QueueT<T>::copyNode(NodeT<T>* original, NodeT<T>* copy)
{
    //passing back pointer of dq as parameter
    //copy starts off as back pointer == null

    //copying the first node (back node)

        //loop to ensure that iteration stops at the head of the original deque
        NodeT<T> *curr1, *prev1 = nullptr;
        if(original == nullptr)
                    //if original deque is empty
                {
                    back = front = copy;
                    return;
                }
        if(original->next == NULL)
        //checking if the element is the back element of original deq
        {
            if(original->previous == NULL)
                //if original deque has only 1 node
            {
                curr1 = new NodeT<T>(original->data);
                copy = curr1;
                back = front = copy;
                num++;

            }
            //copying 1 node at a time, starting with the back node
            //node is created with empty next and previous pointers
            //
            else
            {
                curr1 = new NodeT<T>(original->data);
                copy = curr1;
                back = copy;
                num++;
                copyNode(original->previous, copy);
            }
        }
        else
            //for nodes of back->previous
        {
            if(original->previous == nullptr)
                //at the last node of the original deque
            {
                num++;
                prev1 = new NodeT<T>(original->data, copy, nullptr);
                copy->previous = prev1;
                curr1 = prev1;
                //no more recursive call as base case is reached
                copy = curr1;
                front = copy;
            }

            else
            {
                //at this iteration, original ptr points to previous node in original deque
                //creating a new node whose next pointer points to next node
                prev1 = new NodeT<T>(original->data, copy, nullptr);
                copy->previous = prev1;
                curr1 = prev1;
                copy = curr1;
                num++;
                copyNode(original->previous, copy);
            }
        }
}
#endif // QUEUET_H_INCLUDED
