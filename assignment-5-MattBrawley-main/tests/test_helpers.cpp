#include <gtest/gtest.h>
#include "test_helpers.hpp"



std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

string test_push(int arr[], int length)
{
    MyStack calc;
    testing::internal::CaptureStdout();
   
    for(int i=0;i<length;i++)
    {
        calc.push(arr[i]);
    }
    Node *temp = calc.getStackHead();
    cout << "Print stack from top to bottom:" << endl;
    while(temp != NULL){
        cout << temp->val << endl;
        temp = temp->next;
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}

string test_pop(int arr[], int length)
{
    MyStack calc;
    testing::internal::CaptureStdout();
   
    for(int i=0;i<length;i++)
    {
        calc.push(arr[i]);
    }
    int flag = 0;
    cout << "Print stack from top to bottom:" << endl;
    if(!calc.isEmpty()){
        while(!calc.isEmpty()){
            int num = calc.getStackHead()->val;
            cout << num << endl;
            calc.pop();
            flag++;
            if(flag > 10000){
                break;
            }
        }
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}

string test_peek(int arr[], int length)
{
    MyStack calc;
    testing::internal::CaptureStdout();
   
    for(int i=0;i<length;i++)
    {
        calc.push(arr[i]);
    }
    
    cout << "Print stack from top to bottom:" << endl;
    if(!calc.isEmpty()){
        while(!calc.isEmpty()){
            if(calc.peek()){
                int num = calc.peek()->val;
                cout << num << endl;
                calc.pop();
            }
            else{
                break;
            }
        }
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;  
}

string test_all(int arr[], int length)
{
    MyStack calc;
    testing::internal::CaptureStdout();
    
   
    for(int i=0;i<2;i++)
    {
        cout<<"push: "<<arr[i]<<endl;
        calc.push(arr[i]);
    }
    
    cout<<"poping thrice "<<endl;
    calc.pop();
    calc.pop();
    calc.pop();
    
    for(int i=2;i<length;i++)
    {
        cout<<"push: "<<arr[i]<<endl;
        calc.push(arr[i]);
    }
    
    cout << "Print stack from top to bottom:" << endl;
    if(!calc.isEmpty()){
        while(!calc.isEmpty()){
            if(calc.peek()){
                int num = calc.peek()->val;
                cout << num << endl;
                calc.pop();
            }
            else{
                break;
            }
        }
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}

string test_consQ(){
    testing::internal::CaptureStdout();
    MyQueue q;
    int front = q.getQueueFront();
    int back = q.getQueueEnd();
    if(front == -1 and back == -1) cout << "Correct!" << endl;
    else cout << "front and back are not -1, check constructor" << endl;
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_enQ(string show, int length){
    
    MyQueue queue;
    testing::internal::CaptureStdout();
   
    for(int i = 0; i < length; i++)
    {
        queue.enqueue(show[i]);
    }
    char* q = queue.getQueue();
    int front = queue.getQueueFront();
    int size = queue.queueSize();
    cout << "Print queue from front to back:" << endl;
    for(int i = front; i <= (front + size - 1) % length; i++) 
        cout << q[i] << endl;
   
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_deQ(string show, int length, int dequeue)
{
    MyQueue queue;
    testing::internal::CaptureStdout();
   
    for(int i = 0; i < length; i++)
    {
        queue.enqueue(show[i]);
    }
    
    cout<< "dequeuing "<< dequeue <<" times"<<endl;
    for(int i = 0; i < dequeue; i++)
    {
        queue.dequeue();
    }
    int front = queue.getQueueFront();
    int back = queue.getQueueEnd();
    char* q = queue.getQueue();

    if(length > dequeue)
    {
        cout << "Print queue from front to back:" << endl;
        if(!queue.isEmpty())
            for(int i = front; i <= back; i++) cout << q[i] << endl;
    }
    
    string output = testing::internal::GetCapturedStdout();
    return output;   
}

string test_peekQ(string show, int length, int deQ)
{
    MyQueue queue; //by default size is 5 so not passing length to constructor
    testing::internal::CaptureStdout();
     
    cout << "enqueuing " << length << " elements" << endl;
    for(int i = 0; i < length; i++)
    {
        queue.enqueue(show[i]);
    }
    
    cout << "dequeuing " << deQ << " times" << endl;
    for(int i = 0; i < deQ; i++)
    {
        queue.dequeue();
    }
    
    cout << "peeking in the queue" << endl;
    char it = queue.peek();
    
    if(it != '\0')
    {
        cout << "Front of the queue: " << it << endl;
    }
    string output = testing::internal::GetCapturedStdout();

    return output;
}
        
string test_allQ(string show, string* op, int length)
{
    MyQueue q;
    testing::internal::CaptureStdout();

    int enq = 0;
    for(int i = 0; i < length; i++)
    {
        if(op[i] == "E")
        {
            
            cout << "Enqueue(" << show[i%show.length()] << ")" << endl;
            q.enqueue(show[i]);
            enq++;
        }
        else if(op[i] == "D")
        {
            cout << "Dequeue" << endl;
            q.dequeue();
        }
        else if(op[i] == "P")
        {
            cout << "Peek" << endl;
            char it = q.peek();
            if(it != '\0'){
                cout << it << endl;
            }   
        }
    }
    string full = q.isFull() ? "true" : "false";
    cout << "Queue is full? " << full << endl;
    
    string empty = q.isEmpty() ? "true" : "false";
    cout << "Queue is empty? " << empty << endl;
    
    cout << "Queue size: " << q.queueSize() << endl;
    cout << "Queue front index: " << q.getQueueFront() << endl;
    cout << "Queue back index: " << q.getQueueEnd() << endl;
    
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_generate_operator_queue(std::string _str){
    MessageDecoder* msgDecoder = new MessageDecoder();
    msgDecoder->generate_operator_queue(_str);
    MyQueue* actualQueue = msgDecoder->getQueue();
    char* actual_queue_str = actualQueue->getQueue();
    string actual = actual_queue_str;
    actual = actual.substr(0, actualQueue->queueSize());
    return actual;
}

string test_generate_postfix(string _str){
    MessageDecoder* msgDecoder = new MessageDecoder();
    msgDecoder->generate_operator_queue(_str);
    string post_fix = msgDecoder->generate_postfix(_str);
    return post_fix;
}

int test_evaluate_postfix(string _str){
    MessageDecoder* msgDecoder = new MessageDecoder();
    testing::internal::CaptureStdout();
    msgDecoder->generate_operator_queue(_str);
    string post_fix = msgDecoder->generate_postfix(_str);
    int computed_value = msgDecoder->evaluate_postfix(post_fix);
    string output = testing::internal::GetCapturedStdout();
    return computed_value;
}
