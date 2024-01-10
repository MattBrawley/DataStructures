#ifndef DECODEWORDS_H__
#define DECODEWORDS_H__
#include <iostream>
#include <string>
#include "MyQueue.hpp"
#include "MyStack.hpp"


class MessageDecoder
{

private:
    MyQueue* my_queue;
    MyStack* my_stack;

public:
    MessageDecoder();
    ~MessageDecoder();

    void generate_operator_queue(std::string jumbled_str);
    std::string generate_postfix(std::string jumbled_str);
    int evaluate_postfix(std::string postfix);

    MyQueue* getQueue(); // For Testing purposes only
    MyStack* getStack(); // For Testing purposes only
};
#endif