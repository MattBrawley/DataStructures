// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>

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
//Grade Points: 4
TEST_F(test_x, TestPush)
{
    string result, expected;
    int arr[] = {1,2,3,4};
    int len = 4;
    result = test_push(arr,  len);
    expected= "Print stack from top to bottom:\n4\n3\n2\n1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}
//Grade Points 4
TEST_F(test_x, TestPop)
{
    string result, expected;
    int arr[] = {1,2,3,4};
    int len = 4;
    result = test_pop(arr,  len);
    expected= "Print stack from top to bottom:\n4\n3\n2\n1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}

//Grade Points 4
TEST_F(test_x, TestPeek)
{
    string result, expected;
    int arr[] = {1,2,3,4};
    int len = 4;
    result = test_peek(arr,  len);
    expected= "Print stack from top to bottom:\n4\n3\n2\n1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
}

//Grade Points 8
TEST_F(test_x, TestAll)
{
    string result, expected;
    int arr[] = {1,2,3,4};
    int len = 4;
    result = test_all(arr,  len);
    expected= "push: 1\npush: 2\npoping thrice \nStack empty, cannot pop an item!\npush: 3\npush: 4\nPrint stack from top to bottom:\n4\n3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);
}


//Grade Points 4
TEST_F(test_x, TestEnQ)
{
    string result, expected;
    
    int len = 4;
    result = test_enQ("show",  len);
    expected= "Print queue from front to back:\ns\nh\no\nw\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    len = 21;
    result = test_enQ("abcdefghijklmnopqrstu",  len);
    expected= "Queue full, cannot add!\nPrint queue from front to back:\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\nn\no\np\nq\nr\ns\nt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

//Grade Points 4
TEST_F(test_x, TestDeQ)
{
    string result, expected;
    
    int len = 4;
    result = test_deQ("show",  len, 3);
    expected= "dequeuing 3 times\nPrint queue from front to back:\nw\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    
    len = 4;
    result = test_deQ("show", len, 5);
    expected= "dequeuing 5 times\nQueue empty, cannot dequeue!\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

//Grade Points 6
TEST_F(test_x, TestPeekQ)
{
    string result, expected;
    
    int len = 0;
    int dq = 0;
    result = test_peekQ("show",  len, dq);
    expected= "enqueuing 0 elements\ndequeuing 0 times\npeeking in the queue\nQueue empty, cannot peek!\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    
    len = 4;
    result = test_peekQ("show",  len, 3);
    expected= "enqueuing 4 elements\ndequeuing 3 times\npeeking in the queue\nFront of the queue: w\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
    
    len = 4;
    result = test_peekQ("show",  len, 5);
    expected= "enqueuing 4 elements\ndequeuing 5 times\nQueue empty, cannot dequeue!\npeeking in the queue\nQueue empty, cannot peek!\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2);
}

//Grade Points 20
TEST_F(test_x, TestAllQ)
{
    //enQ2 deQ2
    string result, expected;
    string seq1[] = {"E","E","D","D", "P"};
    int len1 = 5;
    result = test_allQ("show",seq1, len1);
    expected = "Enqueue(s)\nEnqueue(h)\nDequeue\nDequeue\nPeek\nQueue empty, cannot peek!\nQueue is full? false\nQueue is empty? true\nQueue size: 0\nQueue front index: -1\nQueue back index: -1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    //enQ20 deQ10 enQ7
    string seq2[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","E","E","E","E","E","E","E"};
    int len2 = 37;
    result = test_allQ("show", seq2, len2);
    expected = "Enqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nQueue is full? false\nQueue is empty? false\nQueue size: 17\nQueue front index: 10\nQueue back index: 6\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
     //enQ20 deQ10 enQ10
    string seq3[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","E","E","E","E","E","E","E","E","E","E"};
    int len3 = 40;
    result = test_allQ("show",seq3, len3);
    expected = "Enqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nQueue is full? true\nQueue is empty? false\nQueue size: 20\nQueue front index: 10\nQueue back index: 9\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    //enQ20 deQ10 enQ10 deQ20
    string seq4[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D","D"};
    int len4 = 60;
    result = test_allQ("show",seq4, len4);
    expected = "Enqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nQueue is full? false\nQueue is empty? true\nQueue size: 0\nQueue front index: -1\nQueue back index: -1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
     //enQ20 deQ9 enQ4 deQ7
    string seq5[] = {"E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","E","D","D","D","D","D","D","D","D","D","E","E","E","E","D","D","D","D","D","D","D"};
    int len5 = 40;
    result = test_allQ("show",seq5, len5);
    expected = "Enqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nEnqueue(h)\nEnqueue(o)\nEnqueue(w)\nEnqueue(s)\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nDequeue\nQueue is full? false\nQueue is empty? false\nQueue size: 8\nQueue front index: 16\nQueue back index: 3\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);

}

// Test points 6
TEST_F(test_x, TestGenerateOperatorQueue)
{
    string test_jumbled_string_1 = "abc&/2sfasf3asfd+utq1er7--";
    string actual_1 = test_generate_operator_queue(test_jumbled_string_1);
    string expected_1 = "+--";
    ASSERT_EQ(expected_1, actual_1);
    add_points_to_grade(3);

    string test_jumbled_string_2 = "abc2cdes5hu*&&7kjahsd8*9ksjdhasd4-++";
    string actual_2 = test_generate_operator_queue(test_jumbled_string_2);
    string expected_2 = "**-++";
    ASSERT_EQ(expected_2, actual_2);
    add_points_to_grade(3);
}

// Test points 10
TEST_F(test_x, TestGeneratePostFix)
{
    string test_jumbled_string_1 = "abc&/2sfasf3asfd+utq1er7--";
    string actual_1 = test_generate_postfix(test_jumbled_string_1);
    string expected_1 = "23+17--";
    ASSERT_EQ(expected_1, actual_1);
    add_points_to_grade(5);

    string test_jumbled_string_2 = "abc2cdes5hu*&&7kjahsd8*9ksjdhasd4-++";
    string actual_2 = test_generate_postfix(test_jumbled_string_2);
    string expected_2 = "25*78*94-++";
    ASSERT_EQ(expected_2, actual_2);
    add_points_to_grade(5);
}


// Test points 10
TEST_F(test_x, TestEvaluatePostFix)
{
    string test_jumbled_string_1 = "abc&/2sfasf3asfd+utq1er7--";
    int actual_1 = test_evaluate_postfix(test_jumbled_string_1);
    int expected_1 = 11;
    ASSERT_EQ(expected_1, actual_1);
    add_points_to_grade(5);

    string test_jumbled_string_2 = "abc2cdes5hu*&&7kjahsd8*9ksjdhasd4-++";
    int actual_2 = test_evaluate_postfix(test_jumbled_string_2);
    int expected_2 = 71;
    ASSERT_EQ(expected_2, actual_2);
    add_points_to_grade(5);
}

// Test points 20
TEST_F(test_x, TestMain)
{
    string desired;
    string resp;
    desired = readFileIntoString("../tests/output_1.txt");
    resp = exec("./run_app ../tests/input_1.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(10);
    
    desired = readFileIntoString("../tests/output_2.txt");
    resp = exec("./run_app ../tests/input_2.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(10);
}

