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


void BookCollection::removeBook(string bookName) {
    //TODO
    //Hint: For this function you would want to create a helper function to find the minimum node in the right-subtree.

    int left = 0;
    int right = 0;

    Book *toBeDeleted = ifExist(bookName); // returns not found if book not found
    // if collection empty
    if (toBeDeleted == nullptr){
        cout << "Book not found!" << endl;
        return;
    }

    // root is to be deleted
    if (toBeDeleted == root){

        // Only right child
        if (toBeDeleted->left == nullptr && toBeDeleted->right != nullptr){
            root = toBeDeleted->right;
            delete toBeDeleted;
            return;
        }

        // Only left child
        if (toBeDeleted->right == nullptr && toBeDeleted->left != nullptr){
            root = toBeDeleted->left;
            delete toBeDeleted;
            return;
        }

        //3. Node having both left and right child
        if (toBeDeleted->right != nullptr && toBeDeleted->left != nullptr){
            //Hint: For this function you would want to create a helper function to find the minimum node in the right-subtree.
            Book *replacer = minRight(toBeDeleted->right);
            if (toBeDeleted->right == replacer){
                root = replacer;
                root->left = toBeDeleted->left;
                delete toBeDeleted;
            }
            else{
                replacer->right = toBeDeleted->right;
                replacer->left = toBeDeleted->left;

                root = replacer;
                delete toBeDeleted;
            }
            
            return;
        }
    }

    Book *parent = findBook(bookName); 
    if (parent == nullptr){
        parent = root;
    }

    if (parent->left != nullptr){
        if (bookName.compare(parent->left->bookName) == 0){
            toBeDeleted = parent->left;
            left = 1;
        }
    }
    if (parent->right != nullptr){
        if(bookName.compare(parent->right->bookName) == 0){
            toBeDeleted = parent->right;
            right = 1;
        }
    }

    //1. Leaf Node
    if (toBeDeleted->left == nullptr && toBeDeleted->right == nullptr){
        if (left == 1){
            parent->left = nullptr;
        }
        else if(right == 1){
            parent->right = nullptr;
        }

        delete toBeDeleted;
        return;
    }

    //2. Node having either only left or only right child

    // Only right child
    if (toBeDeleted->left == nullptr && toBeDeleted->right != nullptr){
        // delete book and move grandchild to parent

        if (left == 1){
            parent->left = toBeDeleted->right;
        }
        else if(right == 1){
            parent->right = toBeDeleted->right;
        }

        delete toBeDeleted;
        return;
    }

    // Only left child
    if (toBeDeleted->right == nullptr && toBeDeleted->left != nullptr){
        // delete book and move grandchild to parent

        if (left == 1){
            parent->left = toBeDeleted->left;
        }
        else if(right == 1){
            parent->right = toBeDeleted->left;
        }

        delete toBeDeleted;
        return;
    }

    //3. Node having both left and right child
    if (toBeDeleted->right != nullptr && toBeDeleted->left != nullptr){
        //Hint: For this function you would want to create a helper function to find the minimum node in the right-subtree.
        Book *replacer = minRight(toBeDeleted->right);
        replacer->right = toBeDeleted->right;
        replacer->left = toBeDeleted->left;

        if (left == 1){
            parent->left = replacer;
        }
        else if(right == 1){
            parent->right = replacer;
        }

        delete toBeDeleted;
        return;
    }
}


void BookCollection::rotateLeftCollection(string bookName) {
    //TODO
    // Rotating about x
    
    Book *x = nullptr;
    int left = 0;
    int right = 0;

    if (ifExist(bookName) == nullptr){
        return;
    }

    Book *parent = findBook(bookName); // returns not found if book not found
    if (parent == nullptr){
        x = root;
    }
    else{
        if (bookName.compare(parent->left->bookName) == 0){
            x = parent->left;
            left = 1;
        }
        else if(bookName.compare(parent->right->bookName) == 0){
            x = parent->right;
            right = 1;
        }
    }



    // if x is root
    if (x == root){
        Book *y = x->right;
        x->right = y->left;
        y->left = x;
        root = y;
        return;
    }
        
    //x has no right child
    if (x->right == nullptr){
        //cout << "Right Child doesn't exist, rotation can not be done" << endl;
        return;
    }
    
    Book *y = x->right;

    //1. Set the Parents pointers accordingly
    //Parent of x becomes the parent of y
    //y becomes the new parent of x

    if (left == 1){
        parent->left = y;
    }
    else if (right == 1){
        parent->right = y;
    }

    Book *leftSubtreeY = y->left;
    
    //2. Set the subtree (left and right children) pointers accordingly
    //The left subtree of y becomes the right subtree of x
    //x and its descendants become the left subtree of y
    
    x->right = leftSubtreeY;
    y->left = x;

    //3. If x was the left (or right ) subtree of xp (parent of x), make y the left (or right) subtree of 
    //xp respectively. This can be checked by comparing the book names of the parent (xp) and the child (y).

    
    //4. Check the boundary conditions
}

string BookCollection::closestParent(string book1, string book2) {
    //TODO
    Book *book1Node = ifExist(book1);
    if (book1Node == nullptr){
        //cout << "The closest parent to both the books is: Error - wrong book name" << endl; 
        cout << "Book not found!" << endl;
        return "Error - wrong book name";
    }
    Book *book2Node = ifExist(book2);
    if (book2Node == nullptr){
        cout << "Book not found!" << endl;
        //cout << "The closest parent to both the books is: Error - wrong book name" << endl;
        return "Error - wrong book name";
    }

    if (book1 == book2){
        return book1;
    }

    vector<string> path1 = pathFinder(book1);
    vector<string> path2 = pathFinder(book2);
    /*
    for (int i = 0; i < path1.size(); i++){
        cout << "Test1 : " << path1[i] << endl;
    }
    for (int i = 0; i < path2.size(); i++){
        cout << "Test2 : " << path2[i] << endl;
    }
    //
    */

    // Once the two paths are known, we can simply look for the last element that is in both the paths, in 
    // this case B. That element will then be the closest parent. Note that you are only to return the 
    // bookName of the node and not the pointer to the node.

    string closestParent;

    for (int i = 0; i < path1.size(); i++){
        for (int j = 0; j < path2.size(); j++){
            if (path1[i].compare(path2[j]) == 0){
                closestParent = path1[i];
            }
        }
    }

    return closestParent;

    // "The closest parent to both the books is: " << 
}


////////////////////////////////////////////////////////////
//////////          Helper Functions              //////////
////////////////////////////////////////////////////////////


void BookCollection::destructor(Book* node){
    if (node) {
        destructor(node->left);
        destructor(node->right);
        delete node;
    }
}

Book* BookCollection::findBook(string bookName) {
    //TODO
    // search tree with if statement then RETURN if found
    // by the end of the loop, cout "book not found"

    if (root == nullptr){
        return nullptr;
    }

    if (bookName.compare(root->bookName) == 0){ //if (root->bookName == bookName){
        return nullptr;
    }

    Book *currBook = root;

    int resLeft = 1;
    int resRight = 1;

    while (currBook != nullptr){

        if (currBook->left != nullptr){
            resLeft = bookName.compare(currBook->left->bookName);
        }

        if (currBook->right != nullptr){
            resRight = bookName.compare(currBook->right->bookName);
        }
        
        int res = bookName.compare(currBook->bookName);

        if (resLeft == 0 || resRight == 0){
            return currBook;
        }
        else if (res < 0){
            currBook = currBook->left;
        } 
        else{
            currBook = currBook->right;
        }
    }
    //cout << "Book not found!" << endl;
    return nullptr;
}


Book* BookCollection::minRight(Book* node){
    Book *parent = node;
    while (node->left != nullptr){
        parent = node;
        node = node->left;
    }
    parent->left = nullptr;
    return node;
}


/*
Book* BookCollection::minRight(Book* node){ // Office hour helped
    Book *result = node;
    while (node != nullptr){
        result = node;
        node = node->left;
    }
    return result;
}
*/

/*
Book* BookCollection::minRightParental(Book* node){
    Book *parent = node;
    node = node->right;
    while (node->left != nullptr){
        parent = node;
        node = node->left;
    }
    //parent->left = nullptr;
    return node;
}
*/


Book* BookCollection::ifExist(string bookName) {
    Book *currBook = root;
    while (currBook != nullptr){
        if (bookName.compare(currBook->bookName) == 0){
            return currBook;
        } 
        else if (bookName < currBook->bookName){
            currBook = currBook->left;
        } 
        else{
            currBook = currBook->right;
        }
    }
    //cout << "Book not found!" << endl;
    return nullptr;
}

// Using Vector:
vector<string> BookCollection::pathFinder(string bookName) {
    Book *currBook = root;
    vector<string> path;
    path.push_back(root->bookName);

    while (currBook != nullptr) {
        if (bookName == currBook->bookName) {
            if (currBook != root){
                path.push_back(currBook->bookName);
            }
            return path;
        } 
        else if (bookName < currBook->bookName) {
            path.push_back(currBook->bookName);
            currBook = currBook->left;
        } 
        else {
            path.push_back(currBook->bookName);
            currBook = currBook->right;
        }
    }
    return vector<string>();
}