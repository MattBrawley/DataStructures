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
    cout << "4. Display books by a given author"<< endl; // Show books by a given author
    cout << "5. Display the highest rated books" << endl; // Show the highest rated books in the collection
    cout << "6. Display the height of the book collection tree"<< endl; // Show the height of the book collection (Height of the BST)
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
            // Display books by a given author
            string author;
            cout << "Enter the name of the author" << endl;
            cin.ignore();
            getline(cin,author);
            tree->showBooksByAuthor(author);
        }
        else if (input == 5){
            // Display the highest rated books
            tree->showHighestRatedBooks();
        }
        else if(input == 6)
        {
            // Display the height of the collection tree
            int height;
            height = tree->getHeightOfBookCollection();
            cout << "The Height of the Book Collection is " << height << endl;
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
