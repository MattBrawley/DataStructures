#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code/worldMap.hpp"


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

string test_createMap(std::string fileName) {
    testing::internal::CaptureStdout();
    WorldMap world_map;

    world_map.createWorldMap(fileName);
    world_map.printWorldMap();
    
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_printMap(WorldMap &wm) {
    testing::internal::CaptureStdout();

    wm.printWorldMap();

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_printEdges(WorldMap &wm) {
    testing::internal::CaptureStdout();

    wm.displayEdges();

    string output = testing::internal::GetCapturedStdout();
    return output;
}

int test_findNumOfIslands(WorldMap &wm) {
    testing::internal::CaptureStdout();

    int output = wm.findNumOfIslands();

   testing::internal::GetCapturedStdout(); // Discard console output

    return output;
}