#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);
string test_addProfessional(string* name,int len);
string test_addShowConnection(string* name,int len, string* edge, int elen);
string test_bfs(string* name,int len, string* edge, int elen, string st);
string test_suggestProfessionals(string* name, int len, string* edge, int elen, string src, int k);
#endif // TEST_H__