// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions below to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/BookCollection.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

string bookNames1[] = {"Harry Potter: Chamber of Secrets", "Animal Farm", "Brave New World", "Winnie-the-Pooh"};
string authorNames1[] = {"J.K. Rowling", "George Orwell", "Aldous Huxley", "A.A. Milne"};
double ratings1[] = {4.58, 3.98, 3.99, 4.35};
int len1 = 4;

string bookNames2[] = {""};
string authorNames2[] = {""};
double ratings2[] = {};
int len2 = 0;

string bookNames3[] = {"Animal Farm", "Brave New World", "Harry Potter: Chamber of Secrets", "The Hobbit", "Winnie-the-Pooh"};
string authorNames3[] = {"George Orwell", "Aldous Huxley", "J.K. Rowling", "J.R.R. Tolkien", "A.A. Milne"};
double ratings3[] = {3.98, 3.99, 4.58, 4.28, 4.35};
int len3 = 5;

string bookNames4[] = {"Harry Potter: Chamber of Secrets", "Animal Farm", "Brave New World", "Winnie-the-Pooh", "Akira"};
string authorNames4[] = {"J.K. Rowling", "George Orwell", "Aldous Huxley", "A.A. Milne", "Katsuhiro Otomo"};
double ratings4[] = {4.58, 3.98, 3.99, 4.35, 4.4};
int len4 = 5;


//Test Remove Book
//Grade Points: 20
TEST_F(test_x, TestRemoveBook){
	//Book found not at root and Deleted
	BookCollection* rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	string actual = testRemoveBook(rootNode, "Animal Farm");
	string expected = "BOOK: Brave New World BY: Aldous Huxley RATING: 3.99\nBOOK: Harry Potter: Chamber of Secrets BY: J.K. Rowling RATING: 4.58\nBOOK: Winnie-the-Pooh BY: A.A. Milne RATING: 4.35\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
	

	//Book found at root and Deleted
	rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	actual = testRemoveBook(rootNode, "Harry Potter: Chamber of Secrets");
	expected = "BOOK: Animal Farm BY: George Orwell RATING: 3.98\nBOOK: Brave New World BY: Aldous Huxley RATING: 3.99\nBOOK: Winnie-the-Pooh BY: A.A. Milne RATING: 4.35\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	//Book not found
	rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	actual = testRemoveBook(rootNode, "Chetan Bhagat");
	expected = "Book not found!\nBOOK: Animal Farm BY: George Orwell RATING: 3.98\nBOOK: Brave New World BY: Aldous Huxley RATING: 3.99\nBOOK: Harry Potter: Chamber of Secrets BY: J.K. Rowling RATING: 4.58\nBOOK: Winnie-the-Pooh BY: A.A. Milne RATING: 4.35\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	//Empty Collections
	rootNode = createBookCollection(bookNames2, authorNames2, ratings2, len2);
	actual = testRemoveBook(rootNode, "Animal Farm");
	expected = "Book not found!\nCollection is empty.\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
}

//Test Rotate Book Collection
//Grade Points: 20
TEST_F(test_x, TestRotateCollection){
	
	// Book found not at root to rotate
	BookCollection* rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	string actual = testRotateCollection(rootNode, "Animal Farm");
	string expected = "BOOK: Harry Potter: Chamber of Secrets BY: J.K. Rowling RATING: 4.58\nBOOK: Brave New World BY: Aldous Huxley RATING: 3.99\nBOOK: Animal Farm BY: George Orwell RATING: 3.98\nBOOK: Winnie-the-Pooh BY: A.A. Milne RATING: 4.35\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	//Book not found
	rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	actual = testRotateCollection(rootNode, "Chetan Bhagat");
	expected = "BOOK: Harry Potter: Chamber of Secrets BY: J.K. Rowling RATING: 4.58\nBOOK: Animal Farm BY: George Orwell RATING: 3.98\nBOOK: Brave New World BY: Aldous Huxley RATING: 3.99\nBOOK: Winnie-the-Pooh BY: A.A. Milne RATING: 4.35\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
	

	//Book found at root to rotate 
	rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	actual = testRotateCollection(rootNode, "Harry Potter: Chamber of Secrets");
	expected = "BOOK: Winnie-the-Pooh BY: A.A. Milne RATING: 4.35\nBOOK: Harry Potter: Chamber of Secrets BY: J.K. Rowling RATING: 4.58\nBOOK: Animal Farm BY: George Orwell RATING: 3.98\nBOOK: Brave New World BY: Aldous Huxley RATING: 3.99\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	//Empty Collections
	rootNode = createBookCollection(bookNames2, authorNames2, ratings2, len2);
	actual = testRotateCollection(rootNode, "Animal Farm");
	expected = "\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
}

//Test Closest Parent
//Grade Points: 40
TEST_F(test_x, TestClosestParent){

	BookCollection* rootNode = nullptr;
	string testCaseSuffix = "\n[GRADER] No leaked memory (Good).\n";

	// Empty collection
	rootNode = createBookCollection(bookNames2, authorNames2, ratings2, len2);
	string actual = testClosestParent(rootNode, "No book 1", "No book 2");
	string expected = "Book not found!\nError - wrong book name" + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Single book in collection
	rootNode = createBookCollection(bookNames2, authorNames2, ratings2, len2);
	rootNode->addBook("A Game of Thrones", "George R.R. Martin", 4.44);
	actual = testClosestParent(rootNode, "The book that doesnt exist", "A Game of Thrones");
	expected = "Book not found!\nError - wrong book name" + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Single book in collection - Both books to be searched are the same
	rootNode = createBookCollection(bookNames2, authorNames2, ratings2, len2);
	rootNode->addBook("A Game of Thrones", "George R.R. Martin", 4.44);
	actual = testClosestParent(rootNode, "A Game of Thrones", "A Game of Thrones");
	expected = "A Game of Thrones"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Multiple books in collection - Root is the closest parent
	rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	actual = testClosestParent(rootNode, "Brave New World", "Winnie-the-Pooh");
	expected = "Harry Potter: Chamber of Secrets"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(3);

	// Same test case as the previous, but book names in the input are flipped
	rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	actual = testClosestParent(rootNode, "Winnie-the-Pooh", "Brave New World");
	expected = "Harry Potter: Chamber of Secrets"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(2);

	// Multiple books in collection - Non Root node is the closest parent
	rootNode = createBookCollection(bookNames4, authorNames4, ratings4, len4);
	actual = testClosestParent(rootNode, "Brave New World", "Akira");
	expected = "Animal Farm" +  testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Multiple books in collection - One node to be compared is the root
	rootNode = createBookCollection(bookNames4, authorNames4, ratings4, len4);
	actual = testClosestParent(rootNode, "Harry Potter: Chamber of Secrets", "Akira");
	expected = "Harry Potter: Chamber of Secrets"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Multiple books in collection - One book is in the subtree of the other
	rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	actual = testClosestParent(rootNode, "Brave New World", "Animal Farm");
	expected = "Animal Farm" + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(5);

	// Multiple books in collection - One of the books to be searched doesnt exist
	rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	actual = testClosestParent(rootNode, "Animal Farm", "No Book like this");
	expected = "Book not found!\nError - wrong book name" + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(3);

	// Multiple books in collection - Both books to be searched dont exist
	rootNode = createBookCollection(bookNames1, authorNames1, ratings1, len1);
	actual = testClosestParent(rootNode, "No Book like this", "No Book like this either");
	expected = "Book not found!\nError - wrong book name"  + testCaseSuffix;
	ASSERT_EQ(expected, actual);
	add_points_to_grade(2);

}

//Test Overall Functionality
//Grade Points: 20
TEST_F(test_x, TestMain){
	string desired = readFileIntoString("../tests/output/output1.txt");
	string resp = exec("./run_app ../tests/input/books1.csv ../tests/input/input1.txt");
	ASSERT_EQ(desired, resp);
	add_points_to_grade(7.5);
	
	desired = readFileIntoString("../tests/output/output2.txt");
	resp = exec("./run_app ../tests/input/books2.csv ../tests/input/input2.txt");
	ASSERT_EQ(desired, resp);
	add_points_to_grade(7.5);
	
	desired = readFileIntoString("../tests/output/output3.txt");
	resp = exec("./run_app ../tests/input/books3.csv ../tests/input/input2.txt");
	ASSERT_EQ(desired, resp);
	add_points_to_grade(5);
}
