#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>

#include "../code/MessageDecoder.hpp"
#include "../code/MyQueue.hpp"
#include "../code/MyStack.hpp"

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);

string test_push(int* arr, int length);
string test_pop(int* arr, int length);
string test_peek(int* arr, int length);
string test_all(int* arr, int length);


string test_consQ();
string test_enQ(string arr, int length);
string test_deQ(string arr, int length, int dequeue);
string test_peekQ(string arr, int length, int dequeue);
string test_allQ(string show, string* op, int length);

string test_generate_operator_queue(string _str);
string test_generate_postfix(string _str);
int test_evaluate_postfix(string postfix);

// string test_evaluate(char* arr, int length);

#endif // TEST_H__