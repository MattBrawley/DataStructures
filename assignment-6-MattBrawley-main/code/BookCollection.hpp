#ifndef BookCollection_H__
#define BookCollection_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std; 

struct Book {
    string bookName;
    string author;
    double rating;

    Book* left = NULL;
    Book* right = NULL;

    Book(string bm, string a, double r) {
        bookName = bm;
        author = a;
        rating = r;
    }

    void *operator new(std::size_t bytes);
    void operator delete(void *);
};

class BookCollection {
    private:
        Book* root;

    public:
        BookCollection();
        ~BookCollection();
        
        void addBook(string bookName, string author, double rating);
        void showBookCollection();
        void showBook(string bookName);
        void showBooksByAuthor(string author);
        void showHighestRatedBooks();
        int getHeightOfBookCollection();

        void inOrderTraversal(Book* node);
        void highestRatingFinder(Book* currBook, double& highestRating, Book *highestRatedBook);
        void printBooksByRating(Book* currBook, double highestRating);
        void destructor(Book* node);
        void searchAuthor(Book* book, string author);
        int heightFinder(Book* book, int &counter, int &maxHeight);
};

//----------------- DONOT change the code given below --------------------------//
/**************** you can ignore this ******************/
/*     TraceNode memcheck definitions                  ***********/
/*     This will keep track of memory allocation and deallocation*/
/*     This is required for overloading new and delete **********/
/****************************************************************/

struct traceNode
{
  std::string pType;
  void *ptr;
  traceNode *next = NULL;
  traceNode(){}
  traceNode(std::string t, void *p, traceNode *n) : pType(t), ptr(p), next(n) {}
};

extern traceNode *traceHead;
extern bool verbose;
extern int numAllocs;

inline traceNode * addTraceNode(std::string pType, void *ptr, traceNode *traceHead)
{
  traceNode *nn = new traceNode(pType, ptr, traceHead);
  return nn;
}

inline traceNode * removeTraceNode(traceNode *traceHead, void *ptr)
{

  if (traceHead == nullptr){
    std::cerr << "[ERROR] Attempted to delete a node that was never allocated." << std::endl;
    exit(1);
  }
  else if (traceHead->ptr == ptr){
    traceNode *tmp = traceHead->next;
    delete traceHead;
    return tmp;
  }
  else{
    traceHead->next = removeTraceNode(traceHead->next, ptr);
    return traceHead;
  }
}
//----------------------Overloads tree nodes---------------------------
inline void* Book::operator new(std::size_t bytes)
{
  numAllocs += 1;
  void * buf = malloc(bytes);
  memset(buf, 0x0, bytes);

  if(verbose){
    std::cout << "[GRADER] Created Book with address: " << buf << std::endl;
  }

  traceHead = addTraceNode("BST", buf, traceHead);

  return buf;
}

inline void Book::operator delete(void *ptr)
{
  numAllocs -= 1;

  if (verbose){
      std::cout << "[GRADER] Deleted Book with address: " << ptr << std::endl;
  }

  traceHead = removeTraceNode(traceHead, ptr);

  free(ptr);
}

inline void printNode(traceNode * n)
{
  if(n->pType=="BST"){
    Book *b = (Book*) n->ptr;
    cout << "    Book <" << b->bookName << ">" << endl;
  }
}

#endif
