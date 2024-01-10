#ifndef MyStack_H__
#define MyStack_H__
#include <iostream>

struct Node
{
    int val;
    Node *next;
};

class MyStack
{
  private:
    Node* head; // pointer to the top of the stack

  public:
    MyStack();
    ~MyStack();
    bool isEmpty();
    void push(int val);
    void pop();
    Node* peek();
    Node* getStackHead() { return head; }
};
#endif

