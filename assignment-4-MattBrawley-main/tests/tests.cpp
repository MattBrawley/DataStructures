// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/BrowserHistory.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <sstream>

using namespace std;

class test : public ::testing::Test 
{
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

double test::total_grade = 0;
double test::max_grade = 100;

/////////////////////////////////////////
// Test Helper Functions
/////////////////////////////////////////

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

// Test the findDefectLength function [30 POINTS]
TEST_F(test, TestFindDefectLength) {
	BrowserHistory browserHistory;

	// check answer for empty list
	int expectedLength = -1;
	int receivedLength = browserHistory.findDefectLength();
	ASSERT_EQ(receivedLength, expectedLength);
	add_points_to_grade(10);

	// After Building the list but no defect yet.
	testing::internal::CaptureStdout();
	browserHistory.buildBrowserHistory();
	string check = testing::internal::GetCapturedStdout(); //Ignore. 
	expectedLength = -1;
	receivedLength = browserHistory.findDefectLength();
	ASSERT_EQ(receivedLength, expectedLength);
	add_points_to_grade(10);

	// After Building but also adding defect of length = 4.
	browserHistory.produceGlitch("https://www.wikipedia.org/");
	expectedLength = 4;
	receivedLength = browserHistory.findDefectLength();
	ASSERT_EQ(receivedLength, expectedLength);
	add_points_to_grade(10);
}

// Test the removeWebPages function [35 POINTS]
TEST_F(test, TestRemoveWebPages) {
	BrowserHistory browserHistory;

	// Check for empty list
	testing::internal::CaptureStdout();
	browserHistory.removeWebPages(10, 20);
	string receivedOut = testing::internal::GetCapturedStdout();
	string expectedOut = "Browsing history is Empty\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(1);

	testing::internal::CaptureStdout();
	browserHistory.buildBrowserHistory();
	string check = testing::internal::GetCapturedStdout(); //Ignore. 

	// After Building but with bad start and end
	testing::internal::CaptureStdout();
	browserHistory.removeWebPages(0, 6);
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "Invalid start or end values\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(2);

	// After building but start > end
	testing::internal::CaptureStdout();
	browserHistory.removeWebPages(4, 2);
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "Invalid start or end values\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(2);

	// After building, delete just one node
	testing::internal::CaptureStdout();
	browserHistory.removeWebPages(3, 3);
	browserHistory.displayHistory();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "== CURRENT BROWSER HISTORY ==\n[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> NULL\n===\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);

	// After building, delete list except head and tail
	testing::internal::CaptureStdout();
	browserHistory.removeWebPages(2, 3);
	browserHistory.displayHistory();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "== CURRENT BROWSER HISTORY ==\n[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> NULL\n===\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);

	// After building with good start and end deleting whole list
	testing::internal::CaptureStdout();
	browserHistory.removeWebPages(1, 2);
	browserHistory.displayHistory();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "== CURRENT BROWSER HISTORY ==\nEmpty History\nNULL\n===\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);

	// making another for a few more tests
	BrowserHistory browserHistory2;
	testing::internal::CaptureStdout();
	browserHistory2.buildBrowserHistory();
	check = testing::internal::GetCapturedStdout(); //Ignore. 

	// after building, delete just the head
	testing::internal::CaptureStdout();
	browserHistory2.removeWebPages(1, 1);
	browserHistory2.displayHistory();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "== CURRENT BROWSER HISTORY ==\n[ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> NULL\n===\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);

	// after building, delete just the tail
	testing::internal::CaptureStdout();
	browserHistory2.removeWebPages(4, 4);
	browserHistory2.displayHistory();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "== CURRENT BROWSER HISTORY ==\n[ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> NULL\n===\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(6);
}

// Test the mergeTwoHistories function [35 POINTS]
TEST_F(test, TestMergeTwoHistories) {
	BrowserHistory browserHistory1;
	BrowserHistory browserHistory2;
	BrowserHistory browserHistorymerged;

	testing::internal::CaptureStdout();
	WebPage* cello = new WebPage {200, 0, "https://www.cello.com/", "", nullptr};
	browserHistorymerged.addWebPage(nullptr, cello);
	string check = testing::internal::GetCapturedStdout(); //Ignore. 
	
	// Check for merging 2 empty lists 
	testing::internal::CaptureStdout();
	browserHistorymerged.mergeTwoHistories(browserHistory1.searchPageByID(-1), browserHistory2.searchPageByID(-1));
	browserHistorymerged.displayHistory();
	string receivedOut = testing::internal::GetCapturedStdout();
	string expectedOut = "== CURRENT BROWSER HISTORY ==\nEmpty History\nNULL\n===\n";
	ASSERT_EQ(receivedOut, expectedOut);
	add_points_to_grade(8);

	// check for merging 1 built and one empty list
	testing::internal::CaptureStdout();
	browserHistory1.buildBrowserHistory();
	check = testing::internal::GetCapturedStdout(); //Ignore. 
	testing::internal::CaptureStdout();
	// 10 is the ID of the colorado page which is the head
	browserHistorymerged.mergeTwoHistories(browserHistory1.searchPageByID(10), browserHistory2.searchPageByID(-1));
	browserHistorymerged.displayHistory();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "== CURRENT BROWSER HISTORY ==\n[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> NULL\n===\n";
	ASSERT_EQ(receivedOut, expectedOut);
	WebPage *mergedHead = browserHistorymerged.searchPageByID(10);
	WebPage *oneHead = browserHistory1.searchPageByID(10);
	// Has to be the same node, not just having the same contents
	ASSERT_EQ(mergedHead, oneHead);
	add_points_to_grade(9);

	// check for merging 2 built lists
	testing::internal::CaptureStdout();
	WebPage* guitar = new WebPage {20, 0, "https://www.guitartricks.com/", "", nullptr};
    WebPage* piano = new WebPage {21, 0, "https://www.pianomarvel.com/", "", nullptr};
    WebPage* violin = new WebPage {22, 0, "https://reddesertviolin.com/", "", nullptr};
    WebPage* irish = new WebPage {23, 0, "https://www.oaim.ie/", "", nullptr};
    WebPage* drums = new WebPage {24, 0, "https://www.drumeo.com/", "", nullptr};
	browserHistory2.addWebPage(nullptr, guitar);
    browserHistory2.addWebPage(guitar, piano);
    browserHistory2.addWebPage(piano, violin);
    browserHistory2.addWebPage(violin, irish);
    browserHistory2.addWebPage(irish, drums);
	check = testing::internal::GetCapturedStdout(); //Ignore. 
	testing::internal::CaptureStdout();
	// 10, 20 are the IDs of the colorado, guitar page which are the heads
	browserHistorymerged.mergeTwoHistories(browserHistory1.searchPageByID(10), browserHistory2.searchPageByID(20));
	browserHistorymerged.displayHistory();
	receivedOut = testing::internal::GetCapturedStdout();
	expectedOut = "== CURRENT BROWSER HISTORY ==\n[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 20]-(URL::https://www.guitartricks.com/) -> [ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 21]-(URL::https://www.pianomarvel.com/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 22]-(URL::https://reddesertviolin.com/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> [ID:: 23]-(URL::https://www.oaim.ie/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> [ID:: 24]-(URL::https://www.drumeo.com/) -> NULL\n===\n";
	ASSERT_EQ(receivedOut, expectedOut);
	mergedHead = browserHistorymerged.searchPageByID(10);
	oneHead = browserHistory1.searchPageByID(10);
	// Has to be the same node, not just having the same contents
	ASSERT_EQ(mergedHead, oneHead);
	add_points_to_grade(9);

	// check for merging 2 built lists of unequal length
	// 10 is the ID of the colorado page which is the head
	BrowserHistory browserHistory3;
	BrowserHistory browserHistory4;
	testing::internal::CaptureStdout();
	browserHistory3.buildBrowserHistory();
	guitar = new WebPage {20, 0, "https://www.guitartricks.com/", "", nullptr};
    piano = new WebPage {21, 0, "https://www.pianomarvel.com/", "", nullptr};
    violin = new WebPage {22, 0, "https://reddesertviolin.com/", "", nullptr};
    irish = new WebPage {23, 0, "https://www.oaim.ie/", "", nullptr};
    drums = new WebPage {24, 0, "https://www.drumeo.com/", "", nullptr};
	browserHistory4.addWebPage(nullptr, guitar);
    browserHistory4.addWebPage(guitar, piano);
    browserHistory4.addWebPage(piano, violin);
    browserHistory4.addWebPage(violin, irish);
    browserHistory4.addWebPage(irish, drums);
	check = testing::internal::GetCapturedStdout(); //Ignore. 
	testing::internal::CaptureStdout();
	browserHistorymerged.mergeTwoHistories(browserHistory3.searchPageByID(10), browserHistory4.searchPageByID(22));
	browserHistorymerged.displayHistory();
	receivedOut = testing::internal::GetCapturedStdout();
	// 10 22 11 23 12 24 13 14
	expectedOut = "== CURRENT BROWSER HISTORY ==\n[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 22]-(URL::https://reddesertviolin.com/) -> [ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 23]-(URL::https://www.oaim.ie/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 24]-(URL::https://www.drumeo.com/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> NULL\n===\n";
	ASSERT_EQ(receivedOut, expectedOut);
	WebPage *mergedSecondNode = browserHistorymerged.searchPageByID(22);
	WebPage *twoHead = browserHistory4.searchPageByID(22);
	// Has to be the same node, not just having the same contents
	ASSERT_EQ(mergedSecondNode, twoHead);
	add_points_to_grade(9);

	
}

// NOTE! THESE ARE THE OLD TESTS FROM LAST WE REPLACE WITH NEW ONES

// // Test the addWebPage function [20 POINTS]
// TEST_F(test, TestAddWebPage) {
// 	BrowserHistory browserHistory;

//     WebPage* colorado = new WebPage {10, 0, "https://www.colorado.edu", "", nullptr};
//     WebPage* wikipedia = new WebPage {11, 0, "https://www.wikipedia.org/", "", nullptr};
// 	WebPage* brilliant = new WebPage {12, 0, "https://brilliant.org/", "", nullptr};
// 	WebPage* khan = new WebPage {13, 0, "https://www.khanacademy.org/", "", nullptr};

// 	// When previousPage is null
// 	// When the list is empty
// 	testing::internal::CaptureStdout();
// 	browserHistory.addWebPage(nullptr, colorado);
// 	browserHistory.displayHistory();
// 	string addPageOut = testing::internal::GetCapturedStdout();
// 	string expectedAddWebPageOut = "adding: [10]-https://www.colorado.edu (HEAD)\n== CURRENT BROWSER HISTORY ==\n[ID:: 10]-(URL::https://www.colorado.edu) -> NULL\n===\n";
// 	ASSERT_EQ(expectedAddWebPageOut, addPageOut);
// 	add_points_to_grade(5);

// 	// When previousPage is null
// 	// and the list is not empty.
// 	testing::internal::CaptureStdout();
// 	browserHistory.addWebPage(NULL, wikipedia);
// 	browserHistory.displayHistory();
// 	addPageOut = testing::internal::GetCapturedStdout();
// 	expectedAddWebPageOut = "adding: [11]-https://www.wikipedia.org/ (HEAD)\n== CURRENT BROWSER HISTORY ==\n[ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 10]-(URL::https://www.colorado.edu) -> NULL\n===\n";
// 	ASSERT_EQ(expectedAddWebPageOut, addPageOut);
// 	add_points_to_grade(5);

// 	// Insert somewhere in the middle.
// 	testing::internal::CaptureStdout();
// 	browserHistory.addWebPage(wikipedia, brilliant);
// 	browserHistory.displayHistory();
// 	addPageOut = testing::internal::GetCapturedStdout();
// 	expectedAddWebPageOut = "adding: [12]-https://brilliant.org/ (prev: [11])\n== CURRENT BROWSER HISTORY ==\n[ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 10]-(URL::https://www.colorado.edu) -> NULL\n===\n";
// 	ASSERT_EQ(expectedAddWebPageOut, addPageOut);
// 	add_points_to_grade(5);

// 	// Insert at the end.
// 	testing::internal::CaptureStdout();
// 	browserHistory.addWebPage(colorado, khan);
// 	browserHistory.displayHistory();
// 	addPageOut = testing::internal::GetCapturedStdout();
// 	expectedAddWebPageOut = "adding: [13]-https://www.khanacademy.org/ (prev: [10])\n== CURRENT BROWSER HISTORY ==\n[ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 10]-(URL::https://www.colorado.edu) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> NULL\n===\n";
// 	ASSERT_EQ(expectedAddWebPageOut, addPageOut);
// 	add_points_to_grade(5);
// }

// // Test the buildBrowserHistory function [5 POINTS]
// TEST_F(test, TestBuildBrowserHistory) {
// 	BrowserHistory browserHistory;
// 	testing::internal::CaptureStdout();
// 	browserHistory.buildBrowserHistory();
// 	string receivedOut = testing::internal::GetCapturedStdout();
// 	string expectedOut = "adding: [10]-https://www.colorado.edu/ (HEAD)\nadding: [11]-https://www.wikipedia.org/ (prev: [10])\nadding: [12]-https://brilliant.org/ (prev: [11])\nadding: [13]-https://www.khanacademy.org/ (prev: [12])\nadding: [14]-https://www.numberphile.com/ (prev: [13])\n";

// 	ASSERT_EQ(receivedOut, expectedOut);
// 	add_points_to_grade(5);
// }

// // Test the isEmpty() function [5 POINTS]
// TEST_F(test, TestIsEmpty) {
// 	BrowserHistory browserHistory;
	
// 	bool isEmptyValue = browserHistory.isEmpty();
// 	ASSERT_EQ(isEmptyValue, true);
// 	add_points_to_grade(2.5);

// 	testing::internal::CaptureStdout();
// 	browserHistory.buildBrowserHistory();
	
// 	// Not using it, but have to capture for proper
// 	// compilation.
// 	string check = testing::internal::GetCapturedStdout();
	
// 	isEmptyValue = browserHistory.isEmpty();
// 	ASSERT_EQ(isEmptyValue, false);
// 	add_points_to_grade(2.5);
// }

// // Test the displayHistory function [10 POINTS]
// TEST_F(test, TestDisplayHistory) {
// 	BrowserHistory browserHistory;

// 	// Check for empty list
// 	testing::internal::CaptureStdout();
// 	browserHistory.displayHistory();
// 	string receivedOut = testing::internal::GetCapturedStdout();
// 	string expectedOut = "== CURRENT BROWSER HISTORY ==\nEmpty History\nNULL\n===\n";
// 	ASSERT_EQ(receivedOut, expectedOut);
// 	add_points_to_grade(5);

// 	// After Building once.
// 	testing::internal::CaptureStdout();
// 	browserHistory.buildBrowserHistory();
// 	string check = testing::internal::GetCapturedStdout(); //Ignore. 

// 	testing::internal::CaptureStdout();
// 	browserHistory.displayHistory();
// 	receivedOut = testing::internal::GetCapturedStdout();
// 	expectedOut = "== CURRENT BROWSER HISTORY ==\n[ID:: 10]-(URL::https://www.colorado.edu/) -> [ID:: 11]-(URL::https://www.wikipedia.org/) -> [ID:: 12]-(URL::https://brilliant.org/) -> [ID:: 13]-(URL::https://www.khanacademy.org/) -> [ID:: 14]-(URL::https://www.numberphile.com/) -> NULL\n===\n";

// 	ASSERT_EQ(receivedOut, expectedOut);
// 	add_points_to_grade(5);
// }

// // Test the searchPageByID function [5 POINTS]
// TEST_F(test, TestSearchPageByID) {
// 	BrowserHistory browserHistory;

// 	// Check for empty list.
// 	WebPage* historyPtr = browserHistory.searchPageByID(11);
// 	ASSERT_EQ(historyPtr, nullptr);
// 	add_points_to_grade(1);

// 	// Build a list
// 	testing::internal::CaptureStdout();
// 	browserHistory.buildBrowserHistory();
// 	string browserHistoryOut = testing::internal::GetCapturedStdout(); // Ignore

// 	// Hit case.
// 	historyPtr = browserHistory.searchPageByID(11);
// 	ASSERT_NE(historyPtr, nullptr);
// 	ASSERT_EQ(historyPtr->url, "https://www.wikipedia.org/");
// 	add_points_to_grade(2);

// 	// Miss case.
// 	historyPtr = browserHistory.searchPageByID(999);
// 	ASSERT_EQ(historyPtr, nullptr);
// 	add_points_to_grade(2);
// }

// // Test the searchPageByURL function [5 POINTS]
// TEST_F(test, TestSearchPageByURL) {
// 	BrowserHistory browserHistory;

// 	// Check for empty list.
// 	WebPage* historyPtr = browserHistory.searchPageByURL("https://www.khanacademy.org/");
// 	ASSERT_EQ(historyPtr, nullptr);
// 	add_points_to_grade(1);

// 	// Build a list
// 	testing::internal::CaptureStdout();
// 	browserHistory.buildBrowserHistory();
// 	string browserHistoryOut = testing::internal::GetCapturedStdout(); // Ignore

// 	// Hit case.
// 	historyPtr = browserHistory.searchPageByURL("https://www.khanacademy.org/");
// 	ASSERT_NE(historyPtr, nullptr);
// 	ASSERT_EQ(historyPtr->id, 13);
// 	ASSERT_EQ(historyPtr->url, "https://www.khanacademy.org/");
// 	add_points_to_grade(2);

// 	// Miss case.
// 	historyPtr = browserHistory.searchPageByURL("https://www.netflix.com/");
// 	ASSERT_EQ(historyPtr, nullptr);
// 	add_points_to_grade(2);
// }

// TEST_F(test, TestAddOwner) {
// 	BrowserHistory browserHistory;

//     WebPage* colorado = new WebPage {10, 0, "https://www.colorado.edu", "", nullptr};

// 	testing::internal::CaptureStdout();
// 	browserHistory.addOwner("https://www.colorado.edu", "Alan Turing");
// 	string addOwnerOut = testing::internal::GetCapturedStdout();
// 	string expectedAddOwnerOut = "Page not found\n";
// 	ASSERT_EQ(expectedAddOwnerOut, addOwnerOut);
// 	add_points_to_grade(5);

// 	testing::internal::CaptureStdout();
// 	browserHistory.addWebPage(NULL, colorado);
// 	browserHistory.addOwner("https://www.colorado.edu", "Alan Turing");
// 	addOwnerOut = testing::internal::GetCapturedStdout();
// 	expectedAddOwnerOut = "adding: [10]-https://www.colorado.edu (HEAD)\nThe owner (Alan Turing) has been added for the ID - 10\n";
// 	ASSERT_EQ(expectedAddOwnerOut, addOwnerOut);
// 	add_points_to_grade(5);

// 	testing::internal::CaptureStdout();
// 	browserHistory.buildBrowserHistory();
// 	browserHistory.addOwner("https://www.colorado.edu/", "Grace Hopper");
// 	browserHistory.addOwner("https://www.wikipedia.org/", "Ada Lovelace");
// 	browserHistory.addOwner("https://brilliant.org/", "Margaret Hamilton");
// 	browserHistory.addOwner("https://www.khanacademy.org/", "Katherine Johnson");
// 	browserHistory.addOwner("https://www.numberphile.com/", "Radia Perlman");
// 	addOwnerOut = testing::internal::GetCapturedStdout();
// 	expectedAddOwnerOut = "adding: [10]-https://www.colorado.edu/ (HEAD)\nadding: [11]-https://www.wikipedia.org/ (prev: [10])\nadding: [12]-https://brilliant.org/ (prev: [11])\nadding: [13]-https://www.khanacademy.org/ (prev: [12])\nadding: [14]-https://www.numberphile.com/ (prev: [13])\nThe owner (Grace Hopper) has been added for the ID - 10\nThe owner (Ada Lovelace) has been added for the ID - 11\nThe owner (Margaret Hamilton) has been added for the ID - 12\nThe owner (Katherine Johnson) has been added for the ID - 13\nThe owner (Radia Perlman) has been added for the ID - 14\n";
// 	ASSERT_EQ(expectedAddOwnerOut, addOwnerOut);
// 	add_points_to_grade(10);
// }