#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code/BookCollection.hpp"

bool verbose = false;
int numAllocs = 0;
traceNode *traceHead = NULL;

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

void memLeakCheck(BookCollection* root){
    delete root;
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
}

void _showPreOrderBookCollectionHelper(Book* book){
    if (book != nullptr) {
        cout << "BOOK: " << book->bookName << " BY: " << book->author << " RATING: " << book->rating << endl;
        _showPreOrderBookCollectionHelper(book->left);
        _showPreOrderBookCollectionHelper(book->right);
    }
}

void getPreOrderedBookCollection(BookCollection* collection){
    if (collection == nullptr) {
        cout << "Collection is empty." << endl;
        return;
    }
    _showPreOrderBookCollectionHelper(collection->getRoot());
}

BookCollection* createBookCollection(string* bookNames, string* authors, double* ratings, int len){
    BookCollection* book = new BookCollection();
    for(int i=0;i<len;i++)
    {
        book->addBook(bookNames[i],authors[i],ratings[i]);
    }
    return book;
}

string testRemoveBook(BookCollection* root, string removeBookName){
    testing::internal::CaptureStdout();
    root->removeBook(removeBookName);
    root->showBookCollection();
    memLeakCheck(root);
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string testRotateCollection(BookCollection* root, string rotateBook){
    testing::internal::CaptureStdout();
    root->rotateLeftCollection(rotateBook);
    getPreOrderedBookCollection(root);
    memLeakCheck(root);
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string testClosestParent(BookCollection* root, string book_1, string book_2){
    testing::internal::CaptureStdout();
    cout<<root->closestParent(book_1, book_2);
    memLeakCheck(root);
    string output = testing::internal::GetCapturedStdout();
    return output;
}