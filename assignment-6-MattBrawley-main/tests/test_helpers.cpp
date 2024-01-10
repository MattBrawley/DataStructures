#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code/BookCollection.hpp"


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


traceNode *traceHead = NULL;
bool verbose = false;
int numAllocs = 0;


string test_add(string* bookName, string* Author, float* bookRating, int len)
{
    BookCollection* book = new BookCollection();
    testing::internal::CaptureStdout();
    
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding:(" <<bookName[i]<<", "<<Author[i]<<", "<<bookRating[i] <<")"<< endl;
        book->addBook(bookName[i],Author[i],bookRating[i]);
    }
    cout<<"[GRADER] Printing book collection:"<<endl;
    book->showBookCollection();
    
     // MEMCHECK!
    delete book;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_show_book(string* bookNames, string* authors, double* ratings, int len, string bookName){
    BookCollection* tree = new BookCollection();
    testing::internal::CaptureStdout();

    for(int i = 0; i < len; i++){
        tree->addBook(bookNames[i], authors[i], ratings[i]);
    }

    tree->showBook(bookName);
    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_show_book_by_author(string* bookNames, string* authors, double* ratings, int len, string authorName){
    BookCollection* tree = new BookCollection();
    testing::internal::CaptureStdout();

    for(int i = 0; i < len; i++){
        tree->addBook(bookNames[i], authors[i], ratings[i]);
    }

    tree->showBooksByAuthor(authorName);
    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;

}

string test_show_highest_rated_books(string* bookNames, string* authors, double* ratings, int len){
    
    BookCollection* tree = new BookCollection();
    testing::internal::CaptureStdout();

    for(int i = 0; i < len; i++){
        tree->addBook(bookNames[i], authors[i], ratings[i]);
    }

    tree->showHighestRatedBooks();
    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_get_height_of_book_collection(string* bookNames, string* authors, double* ratings, int len){
    BookCollection* tree = new BookCollection();
    testing::internal::CaptureStdout();

    for(int i = 0; i < len; i++){
        tree->addBook(bookNames[i], authors[i], ratings[i]);
    }

    int height = tree->getHeightOfBookCollection();
    cout << "[GRADER]Height of Book Collection:" << height << endl;
    // MEMCHECK!
    delete tree;
    if (traceHead != nullptr){
        cout << endl << "[ERROR] The program leaked memory. The following nodes are still alive:" << endl;
        traceNode *hold = traceHead;
        while (hold != nullptr){
            printNode(hold);
            hold = hold->next;
        }
    }
    else {
        cout << endl << "[GRADER] No leaked memory (Good)." << endl;
    }
     
    string output = testing::internal::GetCapturedStdout();
    return output;
}
