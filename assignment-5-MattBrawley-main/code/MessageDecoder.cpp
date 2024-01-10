#include <iostream>
#include <cstdlib>
#include "MessageDecoder.hpp"

using namespace std;
# define SIZE 50

MessageDecoder::MessageDecoder()
{
	my_queue = new MyQueue();
	my_stack = new MyStack();
}

MessageDecoder::~MessageDecoder()
{
    delete my_queue;
    delete my_stack;	
}

/*
    generate_operator_queue(string jumbled_str)

    Takes the jumbled string as the input parameter and stores all the allowed operators in my_queue
*/
void MessageDecoder::generate_operator_queue(std::string jumbled_str){
    //TODO
    //Take the jumbled string and select only the operator(+,-,*) and enqueue it to my_queue.
    //While iterating through the jumbled_str, you need to take the operators(+,-,*) and enqueue them to my_queue.
    for (char c : jumbled_str){ //goes through char in string
        if (c == '+' || c == '-' || c == '*'){
            my_queue->enqueue(c);
        }
    }
    return;
}

/*
    generate_postfix(string jumbled_str)

    Takes the jumbled string as the input parameter and computes a postfix expression using the populated my_queue
    returns a postfix expression
*/
string MessageDecoder::generate_postfix(std::string jumbled_str){
    //TODO
    //Receive the jumble string again, select the 1-digit number, and complete the postfix string. While doing so, it takes the operator from the queue to make the postfix maintain postfix expression.
	string postfix = "";

    int count = 0;

    for (char c : jumbled_str){ //goes through char in string
        if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){ // >='1' && <='9'
            //append to postfix
            postfix += c;
            count++;

            //If count is equal to 2 and the queue my_queue is not empty, append the next operator in the queue to the postfix string, and remove it from the queue.
            //Reset the counter count to 0.
            if (count == 2 && !my_queue->isEmpty()){
                postfix += my_queue->peek();
                my_queue->dequeue();
                count = 0;
            }
        }
    }

    //append any remaining operators in the queue to the postfix string by dequeuing them one by one. Return the postfix string.
    while (!my_queue->isEmpty()){
        postfix += my_queue->peek();
        my_queue->dequeue();
    }

    return postfix;
}

/* 
    evaluate_postfix(string postfix) 

    Takes the post fix string as an input parameter and evaluates the post fix string. 
    returns an integer after evaluating the postfix expression
*/
int MessageDecoder::evaluate_postfix(std::string postfix){
    //TODO
    //Given the postfix string, do the calculation using my_stack.

    // Node *topNode1 = nullptr;
    // Node *topNode2 = nullptr;
    int result;
    int ascii;
    int val;
    int val1;
    int val2;

    //Iterate through the string postfix character by character. 
    for (char c : postfix){ //goes through char in string
        ascii = (int)(c);
        //For each character: If it is a digit, push it onto the stack as an integer
        if (ascii >= 48 && ascii <= 57){ //if (c >= '1' && c <= '9'){ //use ASCII
            val = c - '0';
            my_stack->push(val); //add onto stack c-'0';
            //You can convert the character to an integer by subtracting the ASCII value of '0' from it (i.e., char1 - '0')
        }
        else if ( ascii == 43 || ascii == 42 || ascii == 45){ //else if (c == '+' || c == '-' || c == '*'){
            //pop the top two elements from the stack and perform the corresponding operation on them
            //Push the result back onto the stack

            val1 = my_stack->peek()->val;
            //int int1 = topNode1->val;
            my_stack->pop();
            val2 = my_stack->peek()->val;
            //int int2 = topNode2->val;
            my_stack->pop();

            if (ascii == 43){ // else if (c == '+'){
                result = val1 + val2;
            }
            else if (ascii == 45){ // else if (c == '-'){
                result = val2 - val1;
            }
            else if(ascii == 42){ // else (c == '*'){
                result = val1 * val2;
            }
            my_stack->push(result);
        }
    }
    //After iterating through the entire string postfix, the result of the expression will be the only element left on the stack
    //Pop it and return it as the result

    result = my_stack->peek()->val; // last element on the guy ////////////////////////////////////////  
    my_stack->pop();

    return result;
}

//For Testing purposes only!
MyQueue* MessageDecoder::getQueue(){
    return my_queue;
}

//For Testing purposes only!
MyStack* MessageDecoder::getStack(){
    return my_stack;
}