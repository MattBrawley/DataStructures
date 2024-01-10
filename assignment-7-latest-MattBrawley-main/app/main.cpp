#include "../code/BookCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
traceNode *traceHead = NULL;
bool verbose = false;
int numAllocs = 0;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Show book collection" << endl; // Show complete book collection
    cout << "2. Add a book"<< endl; // Add a book to the collection
    cout << "3. Search a book"<< endl; // Show book by searching for given book name
    cout << "4. Remove a book"<< endl; // Removes the given book
    cout << "5. Rotate the tree at given book node" << endl; // Left rotate the tree at a give node
    cout << "6. Find the closest parent of two books"<< endl; // Shows the closest parent node
    cout << "7. Quit"<< endl; //Quit
    cout << "> ";
    
}

int main(int argc, char** argv) {
	
    if(argc>2) 
     {
         freopen(argv[2],"r",stdin);  
     }
    
    int input;
    BookCollection* tree = new BookCollection();

    // PROCESS THE FILE
    ifstream iFile(argv[1]);
    string line;

    string bookName, author;
    double rating;
    
    while(getline(iFile, line)) {
        stringstream ss(line);
        string field;

        int counter = 0;
        while(getline(ss, field, ',')) {
            if (counter == 0)
                bookName = field;
            else if (counter == 1)
                author = field;
            else if (counter == 2)
                rating = stod(field);
            counter++;
        }
        tree->addBook(bookName,author,rating);
    }

    // PRESENT MENU
    displayMenu();
    cin >> input;

    while (1) {
        if (input == 1) {
            // Show book collection (in alphabetically sorted order)
            tree->showBookCollection();
        }
        else if (input == 2){
            // Add a book
            string bookName, author,rating_str;
            double rating;
            cout << "Enter the Name of the book" << endl;
            cin.ignore();
            getline(cin,bookName); 
            cout << "Enter the Author of the book" << endl;
            getline(cin,author);
            cout << "Enter the Rating of the book" << endl;
            getline(cin,rating_str);
            rating = stod(rating_str);
            tree->addBook(bookName,author,rating);
            cout << "New Book Added!" << endl;
        }
        else if (input == 3){
            // Search a book
            string book;
            cout << "Enter name of the book:" << endl;
            cin.ignore();
            getline(cin, book);
            tree->showBook(book);
        }
        else if (input == 4){
            // Remove the given book
            string bookName;
            cout << "Enter the name of the book:" << endl;
            cin.ignore();
            getline(cin,bookName);
            tree->removeBook(bookName);
        }
        else if (input == 5){
            // Left rotates the tree at a given node
            string bookName;
            cout << "Enter the name of the book:" << endl;
            cin.ignore();
            getline(cin,bookName);
            tree->rotateLeftCollection(bookName);
        }
        else if(input == 6)
        {
            // Find the closest parent for both the books
            string book1, book2, parentBook;
            cout << "Enter the name of the first book (Book1):" << endl;
            cin.ignore();
            getline(cin,book1);
            cout << "Enter the name of the second book (Book2):" << endl;
            //cin.ignore();
            getline(cin,book2);
            //cout << "Book 2 (main): " << book2 << endl;
            parentBook = tree->closestParent(book1, book2);
            cout << "The closest parent to both the books is: " << parentBook << endl;
        }
        else if (input == 7){
            // Quit
            cout << "Goodbye!" << endl;
            break;
        }
        displayMenu();
        cin >> input;
    }
    
    
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
    return 0;
}
