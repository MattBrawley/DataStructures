#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>

#include "../code/worldMap.hpp"

using namespace std;

std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);
string test_createMap(std::string fileName);
string test_printMap(WorldMap&);
string test_printEdges(WorldMap&);
int test_findNumOfIslands(WorldMap&);

#endif // TEST_H__