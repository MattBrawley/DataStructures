#ifndef NETWORK_H
#define NETWORK_H
#include<vector>
#include<iostream>
using namespace std;

struct Professional;
struct neighbor{
    Professional *v;
};

struct Professional{

    string name;
    bool visited = false;
    int connectionOrder = 0;
    vector<neighbor> neighbors;
};

class LinkedInNetwork
{
    public:
        void addConnection(string v1, string v2);
        void addProfessional(string name);
        void displayConnections();
        void breadthFirstTraverse(string sourceProfessional);
        vector<string> suggestProfessionalsWithinKthOrder(string professionalName, int k);
        
        vector<Professional*> getProfessionals(){return professionals;}


    private:
        vector<Professional*> professionals;
};

#endif // NETWORK_H
