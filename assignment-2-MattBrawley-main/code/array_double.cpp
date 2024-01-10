#include "array_double.hpp"
#include <sstream>

void parseFile(ifstream& input,string queryParams[], CovidCase *&cases, int &arrCapacity,  int &recordIdx, int &doublingCounter){
    string line;

    string targetLocation = queryParams[0]; //Boulder
    string targetVariant = queryParams[1]; //Delta
    int targetAgeMin = stoi(queryParams[2]); //20
    int targetAgeMax = stoi(queryParams[3]); //25

    while (getline(input, line)) {
        stringstream ss(line); // Example line: Santonio Olsen,Alpha,A-Basin,81
        string buf;
        
        if (recordIdx == arrCapacity) {
            doublingCounter++;
            //cout << "Resizing " << doublingCounter << endl;
            resizeArr(cases, &arrCapacity);
            //cout << "arrCapacity = " << arrCapacity << endl; // Double checking that arrCapacity got doubled
        }
        
        CovidCase covidCase[arrCapacity];

        int j = 0;
        while (getline(ss, buf, ',')) {
            if (j == 0) {
                covidCase[recordIdx].name = buf;
            }
            else if(j == 1){
                covidCase[recordIdx].variant = buf;
            } 
            else if(j == 2){
                covidCase[recordIdx].location = buf;
            } 
            else if(j == 3){
                covidCase[recordIdx].age= stoi (buf);
            } 
            j++;
            if(j == 4){
                if (isCaseQueried(covidCase[recordIdx], targetLocation, targetVariant, targetAgeMin, targetAgeMax)){
                    addCase(cases, covidCase[recordIdx], arrCapacity, recordIdx, doublingCounter); //Keeps overwriting unless it passes the boolean function
                }
            }
        }
    }

    sortCases(cases, recordIdx);

    // Outputting
    cout << "Array doubled: " << doublingCounter << endl;
    cout << "Total number of cases returned after the query: " << recordIdx << endl;
    printQueriedCases(cases, recordIdx);
}

bool isCaseQueried(CovidCase covidCase, string queryLocation, string queryVariant, int startAge, int endAge){
    if ((covidCase.location == queryLocation && covidCase.variant == queryVariant) && (covidCase.age >= startAge && covidCase.age <= endAge)){
        return true;
    }
    return false;
}

void resizeArr(CovidCase *&cases, int *arraySize) {
    int newSize = *arraySize * 2;
    CovidCase *tempArray = new CovidCase[newSize];
    for (int i = 0; i < *arraySize; i++) {
        tempArray[i] = cases[i];
    }
    *arraySize = newSize;
    delete[] cases;   
    cases = tempArray;
}

void addCase(CovidCase *&cases, CovidCase covidCase, int &arrCapacity, int &recordIdx, int &doublingCounter){

    if (recordIdx == arrCapacity) {
        doublingCounter++;
        cout << "Resizing " << doublingCounter << endl;
        resizeArr(cases, &arrCapacity);
        //cout << "arrCapacity = " << arrCapacity << endl; // Double checking that arrCapacity got doubled
    }
    //cout << "recordIdx = " << recordIdx << endl;
    cases[recordIdx] = covidCase;
    recordIdx++;
}

void sortCases(CovidCase* cases, int length){
    for (int i = 1; i < length; i++) {
        for (int j = 0; j < length-1; j++) {
            if (cases[j].age > cases[j+1].age || (cases[j].age == cases[j+1].age && cases[j].name > cases[j+1].name)) { // checks if earlier index is larger than later index OR if alphabetically in order
                int tempAge = cases[j].age;
                cases[j].age = cases[j+1].age; // puts smaller value in earlier index
                cases[j+1].age = tempAge; // puts larger value in later index

                string tempVariant = cases[j].variant; // Swapping variant
                cases[j].variant = cases[j+1].variant;
                cases[j+1].variant = tempVariant;

                string tempName = cases[j].name; // Swapping name
                cases[j].name = cases[j+1].name;
                cases[j+1].name = tempName;

                string tempLocation = cases[j].location; // Swapping Location
                cases[j].location = cases[j+1].location;
                cases[j+1].location = tempLocation;                              
            }
        }
    }
}

void printQueriedCases(CovidCase* cases, int numOfRecords){
    cout << "Queried Cases\n---------------------------------------" << endl;
    for (int i = 0; i < numOfRecords; i++){
        cout << cases[i].name << " " << cases[i].age << endl;
    } 
}