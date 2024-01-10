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
std::string test_add(string* bookName, string* Author, float* bookRating, int length);
string test_show_book(string* bookNames, string* authors, double* ratings, int len, string bookName);
string test_show_book_by_author(string* bookNames, string* authors, double* ratings, int len, string authorName);
string test_show_highest_rated_books(string* bookNames, string* authors, double* ratings, int len);
string test_get_height_of_book_collection(string* bookNames, string* authors, double* ratings, int len);
#endif // TEST_H__