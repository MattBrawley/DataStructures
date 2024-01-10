// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/array_double.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <iomanip>

using namespace std;

class test_arrayDouble : public ::testing::Test {
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

double test_arrayDouble::total_grade = 0;
double test_arrayDouble::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

bool compare_arrays(string a[], string b[], int size){
  bool pass = true;
  for(int i = 0; i<size; ++i){
    if(a[i] != b[i])
      pass = false;
  }
  return pass;
}

void compare_arrays_structs(CovidCase a[], CovidCase b[], int size){
  for(int i = 0; i<size; ++i){
	  ASSERT_EQ(a[i].name, b[i].name) << "Array differs at index i=" << i;
	  ASSERT_EQ(a[i].age, b[i].age) << "Array differs at index i=" << i;
	  ASSERT_EQ(a[i].location, b[i].location) << "Array differs at index i=" << i;
	  ASSERT_EQ(a[i].variant, b[i].variant) << "Array differs at index i=" << i;
  }
  return;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void genStructArray(CovidCase *&structArray, string nameArray[], int ages[], string locArray[], string variantArray[], int l){
	for(int i = 0; i<l; i++){
		CovidCase newstruct = CovidCase();
		newstruct.name = nameArray[i];
		newstruct.age = ages[i];
		newstruct.location = locArray[i];
		newstruct.variant = variantArray[i];
		structArray[i] = newstruct;
	}
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

std::string readFileInto(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////


/////////////////////////////////////////
// Test Case Variables Start Here
/////////////////////////////////////////
//Example Case
CovidCase exampleCase = {"John Doe", "Boulder", "Omicron", 24};
// exampleCase.name = "John Doe";
// exampleCase.age = 24;
// exampleCase.location = "Boulder";
// exampleCase.variant = "Omicron";


string array_A_names_unsorted[] = {"Jane Doe", "Dorcey M", "Katrina Teressa", "Zack Snyder", "James Kimmel"};
int array_A_ages_unsorted[] = {24, 36, 54, 23, 45};
string array_A_locations_unsorted[] = {"Boulder", "Atlanta", "Aspen", "CopperMountain", "WinterPark"};
string array_A_variants_unsorted[] = {"Omnicron", "Delta", "Alpha", "Omega", "Beta"};
int testArrLength_A = 5;

string array_A_names_sorted[] = {"Zack Snyder", "Jane Doe", "Dorcey M", "James Kimmel", "Katrina Teressa"};
int array_A_ages_sorted[] = {23, 24, 36, 45, 54};
string array_A_locations_sorted[] = {"CopperMountain", "Boulder", "Atlanta", "WinterPark", "Aspen"};
string array_A_variants_sorted[] = {"Omega", "Omnicron", "Delta", "Beta", "Alpha"};
  
string array_B_names_unsorted[] = {"Jane Doe", "Dorcey M", "Katrina Teressa", "Zack Dane", "James Kimmel",  
                 "Jake Black", "Judy Duty", "Belatrix Honors", "Harry Triplets", "Adam Eve",
                "Alan Turing", "Trevor Adams", "Amy Green", "Sheldon MacBeth", "Ron Snape"};
int array_B_ages_unsorted[] = {36, 54, 23, 45, 33, 
                         12, 19, 89, 65, 71,
                         23, 87, 67, 34, 34};
string array_B_locations_unsorted[] = {"CopperMountain", "WinterPark", "Eldora", "A-Basin", "Lake Tahoe", 
                              "Aspen", "Loveland", "Vail", "Breckenridge", "Boulder", 
                             "SanFrancisco", "San Jose", "San Diego", "LA", "New York"};
string array_B_variants_unsorted[] = {"Omnicron", "Delta", "Alpha", "Omega", "Beta", 
                             "Omnicron", "Delta", "Alpha", "Omega", "Beta",
                            	"Omnicron", "Delta", "Alpha", "Omega", "Beta"};
int testArrLength_B = 15;

string array_B_names_sorted[] = {"Jake Black", "Judy Duty", "Alan Turing", "Katrina Teressa", "James Kimmel",  
                 "Ron Snape", "Sheldon MacBeth", "Jane Doe", "Zack Dane", "Dorcey M",
                "Harry Triplets", "Amy Green", "Adam Eve", "Trevor Adams", "Belatrix Honors"};
int array_B_ages_sorted[] = {12, 19, 23, 23, 33, 
                         34, 34, 36, 45, 54,
                         65, 67, 71, 87, 89};
string array_B_locations_sorted[] = {"Aspen", "Loveland", "SanFrancisco", "Eldora", "Lake Tahoe", 
                              "New York", "LA", "CopperMountain", "A-Basin", "WinterPark", 
                             "Breckenridge", "San Diego", "Boulder", "San Jose", "Vail"};
string array_B_variants_sorted[] = {"Omnicron", "Delta", "Omnicron", "Alpha", "Beta", 
                             "Beta", "Omega", "Omnicron", "Omega", "Delta",
                            	"Omega", "Alpha", "Beta", "Delta", "Alpha"};

//TODO: Update these prints based on the print function of latest
string array_A_print = "Queried Cases\n---------------------------------------\nZack Snyder 23\nJane Doe 24\nDorcey M 36\nJames Kimmel 45\nKatrina Teressa 54\n";
string array_B_print = "Queried Cases\n---------------------------------------\nJake Black 12\nJudy Duty 19\nAlan Turing 23\nKatrina Teressa 23\nJames Kimmel 33\nRon Snape 34\nSheldon MacBeth 34\nJane Doe 36\nZack Dane 45\nDorcey M 54\nHarry Triplets 65\nAmy Green 67\nAdam Eve 71\nTrevor Adams 87\nBelatrix Honors 89\n";

/////////////////////////////////////////
// Test Case Variables End Here
/////////////////////////////////////////


// Test the isCaseQueried() function [10 POINTS]
TEST_F(test_arrayDouble, TestIsCaseQueried){
	bool isValid;
  
	// test case 1: check for happy path
	isValid = isCaseQueried(exampleCase, "Boulder", "Omicron", 20, 30);
	ASSERT_EQ(true, isValid);
	add_points_to_grade(2);
  
  	// test case 2: check for invalid location error path
  	isValid = isCaseQueried(exampleCase, "Denver", "Omicron", 20, 30);
	ASSERT_EQ(false, isValid);
	add_points_to_grade(2);
  
  	// test case 3: check for invalid variant error path
  	isValid = isCaseQueried(exampleCase, "Boulder", "Delta", 20, 30);
	ASSERT_EQ(false, isValid);
	add_points_to_grade(2);
  
  	// test case 4: check for invalid startAge error path
  	isValid = isCaseQueried(exampleCase, "Boulder", "Omicron", 25, 50);
	ASSERT_EQ(false, isValid);
	add_points_to_grade(2);
  
  	// test case 5: check for invalid endAge error path
  	isValid = isCaseQueried(exampleCase, "Boulder", "Omicron", 13, 23);
	ASSERT_EQ(false, isValid);
	add_points_to_grade(2);
}


// Test the resizeArr() function [14 POINTS]
TEST_F(test_arrayDouble, TestResizeArr){
	// Generate an unsorted array of structs:
	CovidCase* testArr_A = new CovidCase[testArrLength_A];
	genStructArray(testArr_A, array_A_names_unsorted, array_A_ages_unsorted, 
					array_A_locations_unsorted, array_A_variants_unsorted, testArrLength_A);
	int initialArrCapacity_A = testArrLength_A;
	//double the array
	resizeArr(testArr_A, &testArrLength_A);
	// Compare the array length:
	ASSERT_EQ(testArrLength_A, initialArrCapacity_A * 2) << "Array has incorrect length";
	add_points_to_grade(7);
	delete[] testArr_A;

	CovidCase* testArr_B = new CovidCase[testArrLength_B];
	genStructArray(testArr_B, array_B_names_unsorted, array_B_ages_unsorted, 
					array_B_locations_unsorted, array_B_variants_unsorted, testArrLength_B);
	int initialArrCapacity_B = testArrLength_B;
	//double the array
	resizeArr(testArr_B, &testArrLength_B);
	// Compare the array length:
	ASSERT_EQ(testArrLength_B, initialArrCapacity_B * 2) << "Array has incorrect length";
	add_points_to_grade(7);
	delete[] testArr_B;
}


// Test the addCase() function [20 POINTS]
TEST_F(test_arrayDouble, TestAddCase){
	testArrLength_A = 5;
	testArrLength_B = 15;
	
	//Test Case 1: Array is not full yet; add a new case
  	CovidCase* testArr_A = new CovidCase[testArrLength_A + 5];
	genStructArray(testArr_A, array_A_names_unsorted, array_A_ages_unsorted, 
  					array_A_locations_unsorted, array_A_variants_unsorted, testArrLength_A);
	int initialArrCapacity_A = testArrLength_A + 5;
	int recordIndex = 5;
	int doubleCounter = 0;
  
  	addCase(testArr_A, exampleCase, initialArrCapacity_A, recordIndex, doubleCounter);
  	ASSERT_EQ(testArrLength_A + 5, initialArrCapacity_A) << "Array has incorrect length";
  	ASSERT_EQ(doubleCounter, 0) << "New Case hasn't been added to the array";
  	add_points_to_grade(10);


  	//Test Case 2: Array is full; add a new case
  	CovidCase* testArr_B = new CovidCase[testArrLength_B];
	genStructArray(testArr_B, array_B_names_unsorted, array_B_ages_unsorted, 
  					array_B_locations_unsorted, array_B_variants_unsorted, testArrLength_B);
	int initialArrCapacity_B = testArrLength_B;
	recordIndex = 15;

  	addCase(testArr_B, exampleCase, testArrLength_B, recordIndex, doubleCounter);
	ASSERT_EQ(testArrLength_B, initialArrCapacity_B * 2) << "Array has incorrect length";
	ASSERT_EQ(doubleCounter, 1) << "New case hasn't been added to the array";
  	add_points_to_grade(10);
}


// Test the sortCases() function [10 POINTS]
TEST_F(test_arrayDouble, TestSortCases){
	testArrLength_A = 5;
	testArrLength_B = 15;

	// Generate an unsorted array of structs:
	CovidCase* testArr_A = new CovidCase[testArrLength_A];
  	genStructArray(testArr_A, array_A_names_unsorted, array_A_ages_unsorted, 
  					array_A_locations_unsorted, array_A_variants_unsorted, testArrLength_A);
  
	// Sort the array to test if sortArray() is working
	sortCases(testArr_A, testArrLength_A);
	// Generate the correctly sorted array of structs:
	CovidCase* sortedArrayOfStructs_A = new CovidCase[testArrLength_A];
	genStructArray(sortedArrayOfStructs_A, array_A_names_sorted, array_A_ages_sorted, 
  					array_A_locations_sorted, array_A_variants_sorted, testArrLength_A);
	
  	// Compare the two arrays:
	ASSERT_EQ(sizeof(testArr_A), sizeof(sortedArrayOfStructs_A)) << "Array has incorrect length";
	compare_arrays_structs(testArr_A, sortedArrayOfStructs_A, testArrLength_A);
	add_points_to_grade(5);
	delete[] testArr_A;
	delete[] sortedArrayOfStructs_A;

	// Generate an unsorted array of structs:
	CovidCase* testArr_B = new CovidCase[testArrLength_B];
  	genStructArray(testArr_B, array_B_names_unsorted, array_B_ages_unsorted, 
  					array_B_locations_unsorted, array_B_variants_unsorted, testArrLength_B);
	// Sort the array to test if sortArray() is working
	sortCases(testArr_B,testArrLength_B);		
	// Generate the correctly sorted array of structs:
	CovidCase* sortedArrayOfStructs_B = new CovidCase[testArrLength_B];
	genStructArray(sortedArrayOfStructs_B, array_B_names_sorted, array_B_ages_sorted, 
  					array_B_locations_sorted, array_B_variants_sorted, testArrLength_B);
	
  	// Compare the two arrays:
	ASSERT_EQ(sizeof(testArr_B), sizeof(sortedArrayOfStructs_B)) << "Array has incorrect length";
	compare_arrays_structs(testArr_B, sortedArrayOfStructs_B, testArrLength_B);
	add_points_to_grade(5);
	delete[] testArr_B;
	delete[] sortedArrayOfStructs_B;
}



// Test the printQueriedCases() function [6 POINTS]
TEST_F(test_arrayDouble, TestPrintQueriedCases){
	testArrLength_A = 5;
	testArrLength_B = 15;

	// Generate the correctly sorted array of structs:
	CovidCase* sortedArrayOfStructs_A = new CovidCase[testArrLength_A];
	genStructArray(sortedArrayOfStructs_A, array_A_names_sorted, array_A_ages_sorted, 
                	array_A_locations_sorted, array_A_variants_sorted, testArrLength_A);
	// Use the following to redirect the standard output
	testing::internal::CaptureStdout();
	// Call the function
	printQueriedCases(sortedArrayOfStructs_A, testArrLength_A);
	// Record the functions std output to a sting variable
	string output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, array_A_print);
	add_points_to_grade(3);

	// Generate the correctly sorted array of structs:
	CovidCase* sortedArrayOfStructs_B = new CovidCase[testArrLength_B];
	genStructArray(sortedArrayOfStructs_B, array_B_names_sorted, array_B_ages_sorted, 
  					array_B_locations_sorted, array_B_variants_sorted, testArrLength_B);
	// Use the following to redirect the standard output
	testing::internal::CaptureStdout();
	// Call the function
	printQueriedCases(sortedArrayOfStructs_B, testArrLength_B);
	// Record the functions std output to a sting variable
	output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, array_B_print);
	add_points_to_grade(3);
}

// Test the main() function [40 POINTS]
TEST_F(test_arrayDouble, TestApp){
  
	string desired = readFileIntoString("../tests/expected_1.txt");
	string resp = exec("./run_app ../tests/covid_cases_1.txt Boulder Delta 20 40");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_2.txt");
	resp = exec("./run_app ../tests/covid_cases_2.txt Eldora Delta 20 60");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_3.txt");
	resp = exec("./run_app ../tests/covid_cases_3.txt Chicago Omicron 20 90");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);

	desired = readFileIntoString("../tests/expected_4.txt");
	resp = exec("./run_app ../tests/covid_cases_4.txt Boston Omega 20 90");
	ASSERT_EQ(desired, resp);
  	add_points_to_grade(10);
}

