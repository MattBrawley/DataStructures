#include <iostream>
#include <cstdlib>
#include <iostream>
#include "MyStack.hpp"

using namespace std;

// In this assignment, Stacks should be implemented using LinkedLists.

MyStack::MyStack()
{
	head = NULL;
}

MyStack::~MyStack()
{
	//TODO
	Node *current = head;
	Node *temp = new Node;
	while (current != nullptr){
		temp = current->next;
		delete current;
		current = temp;
	}
}

bool MyStack::isEmpty()
{
	if (head == nullptr){
		return true;
	}
	else{
		return false;
	}

}

void MyStack::push(int val)
{
	// inserting at beginning of list
	Node* newNode = new Node;
    newNode->val = val;
    newNode->next = head;
    head = newNode;

	/*
	Node *newNode = new Node;
	newNode->val = val;

	if(head == NULL){
		head = newNode; // Sets head to newNode
  	}
	else{
		newNode->next = head->next;
		head->next = newNode;
	}

	return;
	*/
}

void MyStack::pop()
{   
	//TODO
	if (head == nullptr){
		cout << "Stack empty, cannot pop an item!\n";
		return;
	}
	// Deleting first node and moving head forward
    Node* nodeToDelete = head;
    head = head->next;
    delete nodeToDelete;
}

Node* MyStack::peek()
{
	//TODO
	if (head == nullptr){
		cout << "Stack empty, cannot peek!\n";
		return NULL;
	}
	// returning top of stack
	return head;
}
