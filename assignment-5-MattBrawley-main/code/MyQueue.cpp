#include "MyQueue.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// In this assignment, Queues need to be implemented using Arrays

MyQueue::MyQueue(){
    queueFront = -1;
	queueEnd = -1;
}

bool MyQueue::isEmpty(){
	//TODO
	if (counter == 0){
		queueFront = -1;
		queueEnd = -1;
		return true;
	}
	else{
		return false;
	}
}

bool MyQueue::isFull(){
	//TODO
	//Size = 20
	if (counter == SIZE){
		return true;
	}
	else{
		return false;
	}
}

void MyQueue::enqueue(char ch){
	//TODO
	if (isFull()){
        cout << "Queue full, cannot add!\n";
        return;
    }
	
    if (isEmpty()){
        queueFront = 0;
        queueEnd = 0;
    }

	else{
		queueEnd++;
		queueEnd = queueEnd % SIZE; //resets it when it gets over 20
	}
	queue[queueEnd] = ch;
	counter++;
	return;
    //myQueue.push(item);
}


void MyQueue::dequeue(){
	//TODO
	if (isEmpty()){
		cout << "Queue empty, cannot dequeue!\n";
		//string nullString = "\0";
		//return nullString;
		return;
	}

	if (queueFront == queueEnd){ // if last item in queue
        queueFront = -1;
        queueEnd = -1;
    }
	else{
        queueFront++;
    }
	counter--;

	return;
}


char MyQueue::peek(){
	//TODO
	//if the queue is empty, then print “Queue empty, cannot peek!” and return null_string (\0). Otherwise, return the first character in the queue.
	if (isEmpty()){
		cout << "Queue empty, cannot peek!\n";
		//char nullString = "\0";
		char nullString = NULL;
		return nullString;
	}

	char peekChar = queue[queueFront];

	return peekChar;
}

int MyQueue::queueSize(){
    //TODO
    return counter;
}
