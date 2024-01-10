#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code/LinkedInNetwork.hpp"


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


string test_addProfessional(string* name,int len)
{
    LinkedInNetwork g;
    testing::internal::CaptureStdout();
    
   for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding:" <<name[i]<< endl;
        g.addProfessional(name[i]);
    }
    
    vector<Professional*> professionals = g.getProfessionals();
    cout<<"added professionals are:"<<endl;
    for(unsigned int i=0; i < professionals.size(); i++){
        cout<< professionals[i]->name << endl;
    }
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_addShowConnection(string* name,int len, string* connection, int elen)
{
    LinkedInNetwork g;
    testing::internal::CaptureStdout();
    string delimiter = "->";
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding Professional:" <<name[i]<< endl;
        g.addProfessional(name[i]);
    }
    
    for(int i=0;i<elen;i++)
    {
        int pos = connection[i].find(delimiter);
        string v1 = connection[i].substr(0, pos-1);
        string v2 = connection[i].substr(pos + delimiter.length(), connection[i].length());
        cout<< "[GRADER] Adding connection between: "<<v1<<"   "<<v2<<endl;
        g.addConnection(v1,v2);
    
    }
    g.displayConnections();
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_bfs(string* name,int len, string* connection, int elen, string st)
{
    LinkedInNetwork g;
    testing::internal::CaptureStdout();
    string delimiter = "->";
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding Professional:" <<name[i]<< endl;
        g.addProfessional(name[i]);
    }
    
    for(int i=0;i<elen;i++)
    {
        int pos = connection[i].find(delimiter);
        string v1 = connection[i].substr(0, pos-1);
        string v2 = connection[i].substr(pos + delimiter.length(), connection[i].length());
        cout<< "[GRADER] Adding connection between: "<<v1<<"   "<<v2<<endl;
        g.addConnection(v1,v2);
    
    }
    g.displayConnections();
    g.breadthFirstTraverse(st);
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_suggestProfessionals(string* name, int len, string* connection, int elen, string src, int k)
{
    LinkedInNetwork g;
    testing::internal::CaptureStdout();
    string delimiter = "->";
    for(int i=0;i<len;i++)
    {
        cout << "[GRADER] Adding Professional:" <<name[i]<< endl;
        g.addProfessional(name[i]);
    }
    
    for(int i=0;i<elen;i++)
    {
        int pos = connection[i].find(delimiter);
        string v1 = connection[i].substr(0, pos-1);
        string v2 = connection[i].substr(pos + delimiter.length(), connection[i].length());
        cout<< "[GRADER] Adding connection between: "<<v1<<"   "<<v2<<endl;
        g.addConnection(v1,v2);
    
    }
    g.displayConnections();
    vector <string> connections = g.suggestProfessionalsWithinKthOrder(src, k);

    int numConnections = connections.size();
    if (numConnections > 0) {
        cout << "[GRADER] The professionals within kth order are: ";
        for (int i = 0; i < numConnections - 1; i++) cout << connections[i] << ",";
        cout << connections[numConnections - 1] << "\n";
    } else {
        cout << "[GRADER] No reachable connections.\n";
    }
    string output = testing::internal::GetCapturedStdout();
    return output;
}

    