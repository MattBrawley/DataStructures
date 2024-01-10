// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"
#include "../code/LinkedInNetwork.hpp"

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

TEST_F(test_x, AddProfessional){
    string result;
    string expected;
    
    string names[] = {"Jackson", "Hendrix", "Marley", "Presley", "Dylan", "Bowie"};
    int len = 6;
    result = test_addProfessional(names,len);
    expected = "[GRADER] Adding:Jackson\n[GRADER] Adding:Hendrix\n[GRADER] Adding:Marley\n[GRADER] Adding:Presley\n[GRADER] Adding:Dylan\n[GRADER] Adding:Bowie\nadded professionals are:\nJackson\nHendrix\nMarley\nPresley\nDylan\nBowie\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
    
    string names1[] = {"Lennon", "Wonder", "Jackson", "Hendrix", "Marley", "Presley", "Dylan", "Bowie"};
    int len1 = 8;
    result = test_addProfessional(names1,len1);
    expected = "[GRADER] Adding:Lennon\n[GRADER] Adding:Wonder\n[GRADER] Adding:Jackson\n[GRADER] Adding:Hendrix\n[GRADER] Adding:Marley\n[GRADER] Adding:Presley\n[GRADER] Adding:Dylan\n[GRADER] Adding:Bowie\nadded professionals are:\nLennon\nWonder\nJackson\nHendrix\nMarley\nPresley\nDylan\nBowie\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
    string names2[] = {""};
    int len2 = 0;
    result = test_addProfessional(names2,len2);
    expected = "added professionals are:\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
    string names3[] = {"Jackson"};
    int len3 = 1;
    result = test_addProfessional(names3,len3);
    expected = "[GRADER] Adding:Jackson\nadded professionals are:\nJackson\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(1);
}



TEST_F(test_x, AddShowConnection){
    string result;
    string expected;
    
    string names[] = {"Jackson", "Marley", "Presley", "Dylan", "Lennon", "McCartney"};
    int len = 6;
    string edges[] = {"Presley-->Dylan", "Presley-->McCartney", "Jackson-->Marley" };
    int elen = 3;
    result = test_addShowConnection(names,len, edges, elen);
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Presley   Dylan\n[GRADER] Adding connection between: Presley   McCartney\n[GRADER] Adding connection between: Jackson   Marley\nJackson --> Marley \nMarley --> Jackson \nPresley --> Dylan McCartney \nDylan --> Presley \nLennon --> \nMcCartney --> Presley \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
    string names1[] = {"Jackson", "Marley", "Presley", "Dylan", "Lennon", "McCartney"};
    int len1 = 6;
    string edges1[] = {"Marley-->Dylan", "Dylan-->Lennon", "McCartney-->Lennon" };
    int elen1 = 3;
    result = test_addShowConnection(names1,len1, edges1, elen1);
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Marley   Dylan\n[GRADER] Adding connection between: Dylan   Lennon\n[GRADER] Adding connection between: McCartney   Lennon\nJackson --> \nMarley --> Dylan \nPresley --> \nDylan --> Marley Lennon \nLennon --> Dylan McCartney \nMcCartney --> Lennon \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    string names2[] = {"Jackson", "Marley", "Presley"};
    int len2 = 3;
    string edges2[] = {"Presley-->Jackson", "Jackson-->Marley", "Marley-->Presley" };
    int elen2 = 3;
    result = test_addShowConnection(names2,len2, edges2, elen2);
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding connection between: Presley   Jackson\n[GRADER] Adding connection between: Jackson   Marley\n[GRADER] Adding connection between: Marley   Presley\nJackson --> Presley Marley \nMarley --> Jackson Presley \nPresley --> Jackson Marley \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
    string names3[] = {"Jackson", "Marley", "Presley"};
    int len3 = 3;
    string edges3[] = {"Jackson-->Presley"};
    int elen3 = 1;
    result = test_addShowConnection(names3,len3, edges3, elen3);
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding connection between: Jackson   Presley\nJackson --> Presley \nMarley --> \nPresley --> Jackson \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
}



TEST_F(test_x, test_bfs){
    string result;
    string expected;
    
    string names[] = {"Jackson", "Marley", "Presley", "Dylan", "Lennon", "McCartney"};
    int len = 6;
    string edges[] = {"Marley-->Dylan", "Dylan-->Lennon", "McCartney-->Lennon", "Lennon-->Presley", "Presley-->Dylan"};
    int elen = 5;
    result = test_bfs(names,len, edges, elen, "Jackson");
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Marley   Dylan\n[GRADER] Adding connection between: Dylan   Lennon\n[GRADER] Adding connection between: McCartney   Lennon\n[GRADER] Adding connection between: Lennon   Presley\n[GRADER] Adding connection between: Presley   Dylan\nJackson --> \nMarley --> Dylan \nPresley --> Lennon Dylan \nDylan --> Marley Lennon Presley \nLennon --> Dylan McCartney Presley \nMcCartney --> Lennon \nStarting Professional (root): Jackson-> ";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    
    result = test_bfs(names,len, edges, elen, "Marley");
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Marley   Dylan\n[GRADER] Adding connection between: Dylan   Lennon\n[GRADER] Adding connection between: McCartney   Lennon\n[GRADER] Adding connection between: Lennon   Presley\n[GRADER] Adding connection between: Presley   Dylan\nJackson --> \nMarley --> Dylan \nPresley --> Lennon Dylan \nDylan --> Marley Lennon Presley \nLennon --> Dylan McCartney Presley \nMcCartney --> Lennon \nStarting Professional (root): Marley-> Dylan(1) Lennon(2) Presley(2) McCartney(3) ";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    
    result = test_bfs(names,len, edges, elen, "Dylan");
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Marley   Dylan\n[GRADER] Adding connection between: Dylan   Lennon\n[GRADER] Adding connection between: McCartney   Lennon\n[GRADER] Adding connection between: Lennon   Presley\n[GRADER] Adding connection between: Presley   Dylan\nJackson --> \nMarley --> Dylan \nPresley --> Lennon Dylan \nDylan --> Marley Lennon Presley \nLennon --> Dylan McCartney Presley \nMcCartney --> Lennon \nStarting Professional (root): Dylan-> Marley(1) Lennon(1) Presley(1) McCartney(2) ";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    result = test_bfs(names,len, edges, elen, "McCartney");
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Marley   Dylan\n[GRADER] Adding connection between: Dylan   Lennon\n[GRADER] Adding connection between: McCartney   Lennon\n[GRADER] Adding connection between: Lennon   Presley\n[GRADER] Adding connection between: Presley   Dylan\nJackson --> \nMarley --> Dylan \nPresley --> Lennon Dylan \nDylan --> Marley Lennon Presley \nLennon --> Dylan McCartney Presley \nMcCartney --> Lennon \nStarting Professional (root): McCartney-> Lennon(1) Dylan(2) Presley(2) Marley(3) ";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);

    result = test_bfs(names,len, edges, elen, "Presley");
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Marley   Dylan\n[GRADER] Adding connection between: Dylan   Lennon\n[GRADER] Adding connection between: McCartney   Lennon\n[GRADER] Adding connection between: Lennon   Presley\n[GRADER] Adding connection between: Presley   Dylan\nJackson --> \nMarley --> Dylan \nPresley --> Lennon Dylan \nDylan --> Marley Lennon Presley \nLennon --> Dylan McCartney Presley \nMcCartney --> Lennon \nStarting Professional (root): Presley-> Lennon(1) Dylan(1) McCartney(2) Marley(2) ";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
}


TEST_F(test_x, suggestProfessionals){
    string result;
    string expected;
    
    string names[] = {"Jackson", "Marley", "Presley", "Dylan", "Lennon", "McCartney"};
    int len = 6;
    string edges[] = {"Marley-->Dylan", "Dylan-->Lennon", "McCartney-->Lennon", "Lennon-->Presley", "Presley-->Dylan"};
    int elen = 5;
    string source = "Jackson";
    result = test_suggestProfessionals(names,len, edges, elen, source, 1);
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Marley   Dylan\n[GRADER] Adding connection between: Dylan   Lennon\n[GRADER] Adding connection between: McCartney   Lennon\n[GRADER] Adding connection between: Lennon   Presley\n[GRADER] Adding connection between: Presley   Dylan\nJackson --> \nMarley --> Dylan \nPresley --> Lennon Dylan \nDylan --> Marley Lennon Presley \nLennon --> Dylan McCartney Presley \nMcCartney --> Lennon \n[GRADER] No reachable connections.\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);

    string names1[] = {"Jackson", "Marley", "Presley", "Dylan", "Lennon", "McCartney"};
    int len1 = 6;
    string edges1[] = {"Marley-->Dylan", "Dylan-->Lennon", "McCartney-->Lennon", "Lennon-->Presley", "Presley-->Dylan"};
    int elen1 = 5;
    string source1 = "Presley";
    result = test_suggestProfessionals(names1,len1, edges1, elen1, source1, 1);
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Marley   Dylan\n[GRADER] Adding connection between: Dylan   Lennon\n[GRADER] Adding connection between: McCartney   Lennon\n[GRADER] Adding connection between: Lennon   Presley\n[GRADER] Adding connection between: Presley   Dylan\nJackson --> \nMarley --> Dylan \nPresley --> Lennon Dylan \nDylan --> Marley Lennon Presley \nLennon --> Dylan McCartney Presley \nMcCartney --> Lennon \n[GRADER] The professionals within kth order are: Dylan,Lennon\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);
    

    string names2[] = {"Jackson", "Marley", "Presley", "Dylan", "Lennon", "McCartney"};
    int len2 = 6;
    string edges2[] = {"Marley-->Dylan", "Dylan-->Lennon", "McCartney-->Lennon", "Lennon-->Presley", "Presley-->Dylan"};
    int elen2 = 5;
    string source2 = "Dylan";
    result = test_suggestProfessionals(names2,len2, edges2, elen2, source2, 2);
    expected = "[GRADER] Adding Professional:Jackson\n[GRADER] Adding Professional:Marley\n[GRADER] Adding Professional:Presley\n[GRADER] Adding Professional:Dylan\n[GRADER] Adding Professional:Lennon\n[GRADER] Adding Professional:McCartney\n[GRADER] Adding connection between: Marley   Dylan\n[GRADER] Adding connection between: Dylan   Lennon\n[GRADER] Adding connection between: McCartney   Lennon\n[GRADER] Adding connection between: Lennon   Presley\n[GRADER] Adding connection between: Presley   Dylan\nJackson --> \nMarley --> Dylan \nPresley --> Lennon Dylan \nDylan --> Marley Lennon Presley \nLennon --> Dylan McCartney Presley \nMcCartney --> Lennon \n[GRADER] The professionals within kth order are: Marley,Presley,Lennon,McCartney\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(15);
    
    
}