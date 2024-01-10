# CSCI 2270 – Data Structures - Assignment 5 - Stacks and Queues

## Objectives

1. Implement a queue using an array
2. Implement a stack using a Linked List
3. Implement MessageDecoder (Postfix calculation)
4. Main function (Read file, use MessageDecoder)

## Instructions to run programs

Write code to complete Parts 1, 2, 3 and 4. Implement the solution for each part as a separate program. To receive credit for your code, you will need to pass the necessary test cases. Use the following steps to test your code as you work on the assignment:

 1. Open up your Linux terminal, navigate to the build directory of this assignment (e.g. `cd build`).
 2. Run the `cmake ..` command.
 3. Run the `make` command.
 4. If there are no compilation errors, three executables will be generated within the build directory: `run_app_1 ../tests/input_1.txt`, and `run_tests`.
 5. If you would like to run your program including your app implementation in the `main` function, execute `run_app` from the terminal by typing `./run_app`.
 6. To run the grading tests, execute `run_tests` from the terminal by typing `./run_tests`. 

## Instructions for the problem
Given a jumbled string having 1-digit numbers, Alphabets and special characters along with mathematical operators (only consider addition, subtraction and multiplication), build a queue of all the mathematical operators. Generate a postfix expression from the jumbled string. Follow the below steps to generate the postfix operation.

## Background

Queue is a container of objects (a linear collection) that are inserted and removed according to the first-in first-out (FIFO) principle. On the other hand, Stack is a container of objects that are inserted and removed according to the last-in first-out (LIFO) principle. Both of them can be implemented using Arrays or LinkedLists. In this assignment, Queues need to be implemented using Arrays, and Stacks should be implemented using LinkedLists.

## Problem
### Overview:
You will be provided with a jumbled string having 1-digit numbers, Alphabets and special characters along with mathematical operators(+,-,*). There are a `MyQueue.cpp`, `MyStack.cpp`, `MessageDecoder.cpp`, `main.cpp` which you need to implement.

### Specification:
The MessageDecoder is the main class which integrates Stack and Queue structures that you need to implement later. It has three functions;

① `generate_operator_queue`: Take the jumbled string and select only the operator(+,-,*) and enqueue it to my_queue.

② `generate_postfix`: Receive the jumble string again, select the 1-digit number, and complete the postfix string. While doing so, it takes the operator from the queue to make the postfix maintain postfix expression.

③ `evaluate_postfix`: Given the postfix string, do the calculation using my_stack.

** The more details follows in Part 3

When you are done with the implementation, `./run_app` with inputfile will show how the program works.
```
./run_app ../tests/input_1.txt

Postfix Notation::23+17--
Final Answer::11

```

In the MessageDecoder, Queue and Stack are being used with the required functionality;

Queue:
	`isEmpty`: Check if the queue is empty
	`isFull`: Check and returns if the queue is full
	** These two functions are helper for the following functions
	`Enqueue`: Add new data to the back of the queue
	`Dequeue`: Remove data  from the queue’s front
		(You are not really removing the data from the queue.)
	`Peek`: Just see what’s in the front (To be dequeued)
	`QueueSize`: Return the size of the queue


Stack:
	`isEmpty`: Check if the stack is empty
	** The above function is a helper function for the following functions
	`Push`: Add new data to the top of the stack
	`Pop`: Remove data from the stack
	`Peek`: Just see what’s on top of the stack (To be popped)

#### Part 1 - MyQueue Class(MyQueue.cpp):
Important! You need to use Array for this Queue implemenation.

`MyQueue()`
➜ Constructor – Set `queueFront` and `queueEnd` to -1

`bool isEmpty()`
➜ Return true if the queue is empty, false otherwise. You can check it with the counter.

`bool isFull()`
➜ Return true if the queue is full, false otherwise. You can check it by comparing the counter with SIZE.

`void enqueue(char ch)`
➜ If the queue is not full, then add the character(ch) to the end of the queue and modify queueEnd. After updating the queueEnd, you can insert the character(ch) at the appropriate position(index) on the queue. Plus, update queueFront if it’s needed.
➜ If the queue is full, then return “Queue full, cannot add!\n”

`void dequeue()`
➜ Remove the first character from the queue if the queue is not empty and modify queueFront and/or queueEnd if needed. Otherwise print “Queue empty, cannot dequeue!”. (When there is only a single element in the queue, you have to make the queue be the same as when it’s initialized. (There are 3 variables to reset)

`char peek()`
➜ If the queue is empty, then print “Queue empty, cannot peek!” and return null_string (`\0`). Otherwise, return the first character in the queue.

`int queueSize`
➜ Return the size of the queue

#### Part 2 - MyStack Class(MyStack.cpp):
We will use Linked lists to implement Stacks. 

`MyStack()`
➜ Constructor – Set head to NULL.

`~MyStack()`
➜ Destructor – Pops any remaining elements of the stack.

`bool isEmpty()`
➜ Return true if the stack is empty, false otherwise. You can check it with the head of the linked list.

`void push(int val)`
➜ Make a new dynamic variable of the type Node and initialize it with the argument val, and add it to the beginning of the linked list (which marks the top of the stack). For example, if we have already added the values 1, 2, 3 (respectively) to our stack, the Node containing the value 3 would be our head, and adding another Node (with value 4 in the example below), would update our head.


`void pop()`
➜ If stack is not empty, remove the last element of the stack (head) and update head accordingly. If it is empty, you should print out “Stack empty, cannot pop an item!”.

`Node* peek()`
➜ If the stack is not empty, return the last element (head) of the stack. Otherwise, print
"Stack empty, cannot peek!" and return NULL.

#### Part 3- MessageDecoder Class(MessageDecoder.cpp):
`void generate_operator_queue(std::string jumbled_str)`
➜ While iterating through the jumbled_str, you need to take the operators(+,-,*) and enqueue them to my_queue.

`string MessageDecoder::generate_postfix(std::string jumbled_str)`
➜ You have to iterate through the jumbled_str again, and need to take 1-digit numbers. It’s good to prepare an empty string to return. When appending the digits, you need to check if you need to append an operator. (Which is supposed to be already queued)

Here is the brief process to implement this function;

Initialize an empty string variable postfix to hold the postfix expression.
Iterate through the string `jumbled_str` character by character. 
For each character: 
If it is a digit, append it to the postfix string and increment a counter count. 
 If count is equal to 2 and the queue my_queue is not empty, append the next operator in the queue to the `postfix` string, and remove it from the queue. Reset the counter count to 0.
After iterating through the entire string `jumbled_str`, append any remaining operators in the queue to the `postfix` string by dequeuing them one by one. Return the `postfix` string.

`int MessageDecoder::evaluate_postfix(std::string postfix)`
➜ You have to finalize the postfix calculation here. Given the postfix which is completed with `generate_postfix()`.

In a postfix expression, operators come after their operands. For example, the postfix expression `23+` represents the infix expression `2 + 3`. To evaluate a postfix expression, you can use a stack data structure. Initialize an empty stack.

Here is the brief process to implement this function;

Iterate through the string postfix character by character. For each character:
If it is a digit, push it onto the stack as an integer. You can convert the character to an integer by subtracting the ASCII value of '0' from it (i.e., `char1 - '0'`). 
If it is an operator (+, -, or *), pop the top two elements from the stack and perform the corresponding operation on them. Push the result back onto the stack.
After iterating through the entire string postfix, the result of the expression will be the only element left on the stack. Pop it and return it as the result.

#### Part 4 - Main(main.cpp):
The main function needs to read a file and use MessageDecoder to do the postfix calculation. You need to call all the existing functions in MessageDecoder class. Here is the process;


Open the file which is provided though the argument.
If the file is successfully opened, you need to reads the first line of the file into a string variable `jumbled_str`.
Then creates an instance of the `MessageDecoder` class using the default constructor.
Given the jumbled_str, call the generate_operator_queue.
Takes postfix by calling `generate_postfix`.
Call the evaluate_postfix function with the postfix expression as an argument to get the final answer.
Then, print out the message with the postfix and final answer with this command;
```
cout << “Postfix Notation::” << postfix << endl;
cout << “Final Answer::” << answer << endl;
```
Otherwise, if the file couldn’t be opened, it should prints an error message and returns.
```
cout << “Error: Could not open file.\n”;
```

### Submitting your code:
Write your code and push the changes to your private repository. Log onto Canvas and go to Assignment 5. Paste your GitHub repository link and submit.
