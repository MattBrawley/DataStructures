#ifndef READFILE_H__
#define READFILE_H__

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct CovidCase 
{
	string name;
	string location;
	string variant;
	int age;
};

void parseFile(ifstream& input,string queryParams[], CovidCase *&cases, int &arrCapacity,  int &recordIdx, int &doublingCounter);
bool isCaseQueried(CovidCase covidCase, string queryLocation, string queryVariant, int startAge, int endAge);
void resizeArr(CovidCase *&cases, int *arraySize);
void addCase(CovidCase *&cases, CovidCase covidCase, int &arrCapacity, int &recordIdx, int &doublingCounter);
void sortCases(CovidCase* cases, int length);
void printQueriedCases(CovidCase* cases, int numOfRecords);

#endif // READFILE_H__