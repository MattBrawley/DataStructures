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

// TestaddBook_showBookCollection
// Grade points: 25
TEST_F(test_x, TestaddBook_showBookCollection){
    string result;
    string expected;
       
    int len = 0;
    string bn[] = {""};
    string Author[] = {""};
    float bookRating[] = {};
    
    result = test_add(bn,Author, bookRating, len);
    expected = "[GRADER] Printing book collection:\nCollection is empty.\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);

    int len1 = 1;
    string bn1[] = {"Of Mice and Men"};
    string Author1[] = {"John Steinbeck"};
    float bookRating1[] = {3.88};
    
    result = test_add(bn1,Author1, bookRating1, len1);
    expected = "[GRADER] Adding:(Of Mice and Men, John Steinbeck, 3.88)\n[GRADER] Printing book collection:\nBOOK: Of Mice and Men BY: John Steinbeck RATING: 3.88\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    int len2 = 2;
    string bn2[] = {"Sophie's Choice","The Phantom Tollbooth"};
    string Author2[] = {"William Styron","Norton Juster"};
    float bookRating2[] = {4.18,4.19};
    
    result = test_add(bn2,Author2, bookRating2, len2);
    expected = "[GRADER] Adding:(Sophie's Choice, William Styron, 4.18)\n[GRADER] Adding:(The Phantom Tollbooth, Norton Juster, 4.19)\n[GRADER] Printing book collection:\nBOOK: Sophie's Choice BY: William Styron RATING: 4.18\nBOOK: The Phantom Tollbooth BY: Norton Juster RATING: 4.19\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    int len3 = 2;
    string bn3[] = {"The Hound of the Baskervilles","The Grapes of Wrath"};
    string Author3[] = {"Arthur Conan Doyle","John Steinbeck"};
    float bookRating3[] = {4.13,4};
    
    result = test_add(bn3,Author3, bookRating3, len3);
    expected = "[GRADER] Adding:(The Hound of the Baskervilles, Arthur Conan Doyle, 4.13)\n[GRADER] Adding:(The Grapes of Wrath, John Steinbeck, 4)\n[GRADER] Printing book collection:\nBOOK: The Grapes of Wrath BY: John Steinbeck RATING: 4\nBOOK: The Hound of the Baskervilles BY: Arthur Conan Doyle RATING: 4.13\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    


    int len4 = 8;
    string bn4[] = {"Cheaper by the Dozen","Animal Dreams","Heartburn","How It Is","Tripwire","The Confusions of Young Törless","My Life","The Hero With a Thousand Faces"};
    string Author4[] = {"Frank B. Gilbreth Jr.","Barbara Kingsolver","Nora Ephron","Samuel Beckett","Lee Child","Robert Musil","Oswald Mosley","Joseph Campbell"};
    float bookRating4[] = {3.99,4.06,3.6,4,4.11,3.69,3.85,4.14};
    
    result = test_add(bn4,Author4, bookRating4, len4);
	//cout<< result;
    expected = "[GRADER] Adding:(Cheaper by the Dozen, Frank B. Gilbreth Jr., 3.99)\n[GRADER] Adding:(Animal Dreams, Barbara Kingsolver, 4.06)\n[GRADER] Adding:(Heartburn, Nora Ephron, 3.6)\n[GRADER] Adding:(How It Is, Samuel Beckett, 4)\n[GRADER] Adding:(Tripwire, Lee Child, 4.11)\n[GRADER] Adding:(The Confusions of Young Törless, Robert Musil, 3.69)\n[GRADER] Adding:(My Life, Oswald Mosley, 3.85)\n[GRADER] Adding:(The Hero With a Thousand Faces, Joseph Campbell, 4.14)\n[GRADER] Printing book collection:\nBOOK: Animal Dreams BY: Barbara Kingsolver RATING: 4.06\nBOOK: Cheaper by the Dozen BY: Frank B. Gilbreth Jr. RATING: 3.99\nBOOK: Heartburn BY: Nora Ephron RATING: 3.6\nBOOK: How It Is BY: Samuel Beckett RATING: 4\nBOOK: My Life BY: Oswald Mosley RATING: 3.85\nBOOK: The Confusions of Young Törless BY: Robert Musil RATING: 3.69\nBOOK: The Hero With a Thousand Faces BY: Joseph Campbell RATING: 4.14\nBOOK: Tripwire BY: Lee Child RATING: 4.11\n\n[GRADER] No leaked memory (Good).\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
}

// TestShowBook
// Grade Points: 10
TEST_F(test_x, TestShowBook){
	string bookNames[] = {"Harry Potter: Chamber of Secrets", "Animal Farm", "Brave New World", "Winnie-the-Pooh"};
	string authorNames[] = {"J.K. Rowling", "George Orwell", "Aldous Huxley", "A.A. Milne"};
	double ratings[] = {4.58, 3.98, 3.99, 4.35};
	int len = 4;

	string actual = test_show_book(bookNames, authorNames, ratings, len, "Animal Farm");
	string expected = "Book:\n==================\nName :Animal Farm\nAuthor :George Orwell\nRating :3.98\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string bookNames_2[] = {"Harry Potter: Chamber of Secrets", "Harry Potter and the Sorcerer's Stone", "Harry Potter and the Prisoner of Azkaban", "Winnie-the-Pooh"};
	string authorNames_2[] = {"J.K. Rowling", "J.K. Rowling", "J.K. Rowling", "A.A. Milne"};
	double ratings_2[] = {4.58, 4.47, 4.59, 4.35};

	actual = test_show_book(bookNames_2, authorNames_2, ratings_2, len, "Zdarzenia na brygu Banbury");
	expected = "Book not found.\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
}

// TestShowBooksByAuthor (Books displayed in sorted order)
// Grade Points: 15
TEST_F(test_x, TestShowBooksByAuthors){
	string bookNames[] = {"Harry Potter: Chamber of Secrets", "Animal Farm", "Brave New World", "Winnie-the-Pooh"};
	string authorNames[] = {"J.K. Rowling", "George Orwell", "Aldous Huxley", "A.A. Milne"};
	double ratings[] = {4.58, 3.98, 3.99, 4.35};
	int len = 4;

	string actual = test_show_book_by_author(bookNames, authorNames, ratings, len, "J.K. Rowling");
	string expected = "Books By: J.K. Rowling\nHarry Potter: Chamber of Secrets RATING: 4.58\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string bookNames_2[] = {"Harry Potter: Chamber of Secrets", "Harry Potter and the Sorcerer's Stone", "Harry Potter and the Prisoner of Azkaban", "Winnie-the-Pooh"};
	string authorNames_2[] = {"J.K. Rowling", "J.K. Rowling", "J.K. Rowling", "A.A. Milne"};
	double ratings_2[] = {4.58, 4.47, 4.59, 4.35};

	actual = test_show_book_by_author(bookNames_2, authorNames_2, ratings_2, len, "J.K. Rowling");
	expected = "Books By: J.K. Rowling\nHarry Potter and the Prisoner of Azkaban RATING: 4.59\nHarry Potter and the Sorcerer's Stone RATING: 4.47\nHarry Potter: Chamber of Secrets RATING: 4.58\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string bookNames_3[] = {"Harry Potter: Chamber of Secrets", "Harry Potter and the Sorcerer's Stone", "Harry Potter and the Prisoner of Azkaban", "Winnie-the-Pooh"};
	string authorNames_3[] = {"J.K. Rowling", "J.K. Rowling", "J.K. Rowling", "A.A. Milne"};
	double ratings_3[] = {4.58, 4.47, 4.59, 4.35};

	actual = test_show_book_by_author(bookNames_3, authorNames_3, ratings_3, len, "L.M. Montgomery");
	expected = "Books By: L.M. Montgomery\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
}

// TestShowHighestRatedBooks (Books displayed in sorted order)
// Grade Points: 15
TEST_F(test_x, TestShowHighestRatedBooks){

	string bookNames[] = {"Harry Potter: Chamber of Secrets", "Animal Farm", "Brave New World", "Winnie-the-Pooh"};
	string authorNames[] = {"J.K. Rowling", "George Orwell", "Aldous Huxley", "A.A. Milne"};
	double ratings[] = {4.58, 3.98, 3.99, 4.35};
	int len = 4;

	string actual = test_show_highest_rated_books(bookNames, authorNames, ratings, len);
	string expected = "Highest Rating: 4.58\nHarry Potter: Chamber of Secrets BY: J.K. Rowling\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string bookNames_2[] = {"Harry Potter and the Chamber of Secrets", "Harry Potter and the Sorcerer's Stone", "Harry Potter and the Prisoner of Azkaban", "Winnie-the-Pooh"};
	string authorNames_2[] = {"J.K. Rowling", "J.K. Rowling", "J.K. Rowling", "A.A. Milne"};
	double ratings_2[] = {4.58, 4.47, 4.58, 4.35};

	actual = test_show_highest_rated_books(bookNames_2, authorNames_2, ratings_2, len);
	expected = "Highest Rating: 4.58\nHarry Potter and the Chamber of Secrets BY: J.K. Rowling\nHarry Potter and the Prisoner of Azkaban BY: J.K. Rowling\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string bookNames_3[] = {""};
	string authorNames_3[] = {""};
	double ratings_3[] = {};
	len = 0;

	actual = test_show_highest_rated_books(bookNames_3, authorNames_3, ratings_3, len);
	expected = "Collection is empty.\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
}

// TestGetHeightOfBookCollection
// Grade Points: 15
TEST_F(test_x, TestGetHeightOfCollection){

	string bookNames[] = {"Harry Potter: Chamber of Secrets", "Animal Farm", "Brave New World", "Winnie-the-Pooh"};
	string authorNames[] = {"J.K. Rowling", "George Orwell", "Aldous Huxley", "A.A. Milne"};
	double ratings[] = {4.58, 3.98, 3.99, 4.35};
	int len = 4;

	string actual = test_get_height_of_book_collection(bookNames, authorNames, ratings, len);
	string expected = "[GRADER]Height of Book Collection:3\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string bookNames_2[] = {"Harry Potter and the Chamber of Secrets"};
	string authorNames_2[] = {"J.K. Rowling"};
	double ratings_2[] = {4.58};
	len = 1;

	actual = test_get_height_of_book_collection(bookNames_2, authorNames_2, ratings_2, len);
	expected = "[GRADER]Height of Book Collection:1\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);

	string bookNames_3[] = {""};
	string authorNames_3[] = {""};
	double ratings_3[] = {};
	len = 0;

	actual = test_get_height_of_book_collection(bookNames_3, authorNames_3, ratings_3, len);
	expected = "[GRADER]Height of Book Collection:0\n\n[GRADER] No leaked memory (Good).\n";
	ASSERT_EQ(expected, actual);
    add_points_to_grade(5);
}

// TestMain
// Grade Points: 15
TEST_F(test_x, TestMain)
{
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
