#include "BookCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

BookCollection::BookCollection() {
    //TODO
    root = nullptr;
}

BookCollection::~BookCollection() {
    //TODO
    destructor(root);
}

void BookCollection::addBook(string bookName, string author, double rating) {
    //TODO

    Book *temp = root;
    Book *book2add = new Book(bookName, author, rating);

    if (temp == nullptr){
        root = book2add;
    }
    
    while (temp != nullptr){
        int res = bookName.compare(temp->bookName); //if (bookName < temp->bookName){
        if (res < 0){
            if (temp->left == nullptr){
                temp->left = book2add;
                break;
            }
            else{
                temp = temp->left;
            }
        }
        else if (res > 0){ //else if(bookName > temp->bookName){
            if (temp->right == nullptr){
                temp->right = book2add;
                break;
            }
            else{
                temp = temp->right;
            }
        }
        else{
            book2add->left = temp->left;
            book2add->right = temp->right;           
            temp = book2add;
        }
    }
}

void BookCollection::showBookCollection() {
    //TODO

    //IN ORDER
    if (root == nullptr){
        cout << "Collection is empty." << endl;
        return;
    }
    else{
        inOrderTraversal(root);
    }
}

void BookCollection::showBook(string bookName) {
    //TODO
    // search tree with if statement then RETURN if found
    // by the end of the loop, cout "book not found"

    Book *currBook = root;
    while (currBook != nullptr){

        if (bookName == currBook->bookName){
            cout << "Book:" << endl;
            cout << "==================" << endl;
            cout << "Name :" << currBook->bookName << endl;
            cout << "Author :" << currBook->author << endl;
            cout << "Rating :" << currBook->rating << endl;
            return;
        } 
        else if (bookName < currBook->bookName){
            currBook = currBook->left;
        } 
        else{
            currBook = currBook->right;
        }
    }
    cout << "Book not found." << endl;
    return;
}

void BookCollection::showBooksByAuthor(string author) {
    //TODO
    // IN ORDER

    cout << "Books By: " << author << endl;

    searchAuthor(root,author);

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BookCollection::showHighestRatedBooks() {
    //TODO
    if (root == nullptr){
        cout << "Collection is empty." << endl;
        return;
    }

    // If not, you need to first, recursively traverse through the BookCollection to find out the highest 
    // rating and then, recursively traverse through the collection again to print all books having the 
    // highest rating.
    double highestRating = 0;

    Book *highestRatedBook = new Book(" ", " ", 0);

    highestRatingFinder(root, highestRating, highestRatedBook);

    cout << "Highest Rating: " << highestRating << endl;
    printBooksByRating(root, highestRating);

    delete highestRatedBook;

    return;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int BookCollection::getHeightOfBookCollection() {
    //TODO

    int height = 0;
    int counter = 0;
    height = heightFinder(root, counter, height);

    return height;
}

//////////////////////////////////////////////////////
//                  Added Functions                 //
//////////////////////////////////////////////////////

void BookCollection::inOrderTraversal(Book* book) {
    if (book == NULL){
        return;
    }

    inOrderTraversal(book->left);

    cout << "BOOK: " << book->bookName << " BY: " << book->author << " RATING: " << book->rating << endl;

    inOrderTraversal(book->right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BookCollection::highestRatingFinder(Book* currBook, double& highestRating, Book *highestRatedBook){
    if (currBook == nullptr){
        return;
    }

    highestRatingFinder(currBook->left, highestRating, highestRatedBook);

    if (currBook->rating > highestRating){
        highestRating = currBook->rating; 
        highestRatedBook = currBook; 
    }

    highestRatingFinder(currBook->right, highestRating, highestRatedBook);

    return;
}

void BookCollection::printBooksByRating(Book* currBook, double highestRating) {
    if (currBook == nullptr) {
        return;
    }

    printBooksByRating(currBook->left, highestRating);

    if (currBook->rating == highestRating) {
        cout << currBook->bookName << " BY: " << currBook->author << endl;
    }

    printBooksByRating(currBook->right, highestRating);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BookCollection::destructor(Book* node){
    if (node) {
        destructor(node->left);
        destructor(node->right);
        delete node;
    }
}

void BookCollection::searchAuthor(Book* book, string author){
    if (book == NULL){
        return;
    }

    searchAuthor(book->left, author);

    int res = author.compare(book->author); //if (bookName < temp->bookName){
    if (res == 0){
        cout << book->bookName << " RATING: " << book->rating << endl;
    }

    searchAuthor(book->right, author);
}

int BookCollection::heightFinder(Book* book, int &counter, int &maxHeight){
    if (book == NULL){
        return 0;
    }

    if (book == root){
        counter = 0;
        maxHeight = 0;
    }

    counter++;
    heightFinder(book->left,counter,maxHeight);

    if (maxHeight < counter){
        maxHeight = counter;
    }

    heightFinder(book->right,counter,maxHeight);

    counter--;

    return maxHeight;
}