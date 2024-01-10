#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;

int main(int argc, char* argv[])
{   
    if(argc != 6){
		// cout<< "No CLA passed" << endl;
        cout << "Usage: ./run_app <inputfilename> <Query_Location> <Query_Variant> <Query_Start_Age> <Query_End_Age>" << endl;
        return -1;
	}

    ifstream file(argv[1]);
    string line;

    /*
    string targetLocation = argv[2]; //Boulder
    string targetVariant = argv[3]; //Delta
    int targetAgeMin = argv[4]; //20
    int targetAgeMax = argv[5]; //25
    */

    string queryParams [] = {argv[2], argv[3], argv[4], argv[5]};
    
    int size = 10;
    CovidCase *array = new CovidCase[size];
    // CovidCase *array = NULL;
    int count = 0;
    int numTimesResized = 0;

    parseFile (file, queryParams, array, size, count, numTimesResized);
    
    //delete[] array;
    return 0;
}