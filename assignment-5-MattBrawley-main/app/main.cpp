#include<iostream>
#include <fstream>
#include<cmath>
#include<iomanip>
#include "../code/MessageDecoder.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    if (argc < 2){
        cout << "Usage: ./run_app <inputfilename>" << endl;
        return 0;
    } 
    else{
        // TODO 
        //Open the file which is provided though the argument.
        ifstream file(argv[1]);
        string line;
        string jumbled_str;

        //If the file is successfully opened, you need to reads the first line of the file into a string variable jumbled_str.
        if (file.is_open()) {
            getline(file, jumbled_str);
        } 
        else{
            cout << "Error: Could not open file.\n";
            return 0;
        }
        
        //Then creates an instance of the MessageDecoder class using the default constructor. 
        MessageDecoder messageDecoder;

        //Given the jumbled_str, call the generate_operator_queue. 
        messageDecoder.generate_operator_queue(jumbled_str);

        //Takes postfix by calling generate_postfix. 
       string postfix = messageDecoder.generate_postfix(jumbled_str);

        //Call the evaluate_postfix function with the postfix expression as an argument to get the final answer.
        int answer = messageDecoder.evaluate_postfix(postfix);
        
        //Then, print out the message with the postfix and final answer with this command;
        cout << "Postfix Notation::" << postfix << endl;
        cout << "Final Answer::" << answer << endl;

        //Otherwise, if the file couldn’t be opened, it should prints an error message and returns.
        file.close();
    }
    
    return 0;
}