#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include "../code/BookCollection.hpp"

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);
void memLeakCheck(BookCollection* root);
void getPreOrderedBookCollection(BookCollection* root);
BookCollection* createBookCollection(string* bookNames, string* authors, double* ratings, int len);
string testRemoveBook(BookCollection* root, string removeBook);
string testRotateCollection(BookCollection* root, string rotateBook);
string testClosestParent(BookCollection* root, string book_1, string book_2);
#endif // TEST_H__