#include "LinkedInNetwork.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <bits/stdc++.h>///////////////////////

using namespace std;

void LinkedInNetwork::addProfessional(string name){
    //TODO
    // Add new professional (i.e., a vertex) with name to the graph unless something with the same name exists. 
    // If a professional already exists with the same name, print out the following:

    int check = 0;
    int max = professionals.size();
    for (int i = 0; i < max; i++){ // goes through and checks if name is already in list
        if (name == professionals[i]->name){
            check = 1;
        }
    }
    
    if (check == 0){
        // add struct to vector
        Professional *add = new Professional;
        add->name = name;
        professionals.push_back(add);
    }
    else{
        cout << name << " found." << endl;
    }
}

void LinkedInNetwork::addConnection(string v1, string v2){
    //TODO
    // Add a connection (i.e., an edge) between professionals named v1 and v2. It is guaranteed that there will 
    // be vertices with names 'v1' and 'v2' in the graph. Remember that this is an undirected graph. So if you
    // are adding 'B' to the neighbors of 'A', then you also have to add 'A' to the neighbors of 'B'.

    // Used code from lecture as base.
    int max = professionals.size();

    for(int i = 0; i < max; i++){
		if(professionals[i]->name == v1){
			for(int j = 0; j < max; j++){
				if(professionals[j]->name == v2 && i != j){
                    neighbor adjVertex1;
					adjVertex1.v = professionals[j];
					professionals[i]->neighbors.push_back(adjVertex1);

					// another vetex for edge in the other direction
                    neighbor adjVertex2;
					adjVertex2.v = professionals[i];
					professionals[j]->neighbors.push_back(adjVertex2);
				}
			}
		}
	}
}

void LinkedInNetwork::displayConnections(){
    //TODO
    //Display all the edges in the graph in the following format: Dylan --> Lennon

    int max = professionals.size();

    for(int i = 0; i < max; i++){
        cout << professionals[i]->name << " --> " ;
        for(int j = 0; j < professionals[i]->neighbors.size(); j++){
            cout << professionals[i]->neighbors[j].v->name << " ";
            //cout << professionals[i]->name << " --> " << professionals[i]->neighbors[j].v->name << " ";
		}
        cout << endl;
	}   

}

void bfs_helper(string source, vector<Professional*> &professionals);

void LinkedInNetwork::breadthFirstTraverse(string sourceProfessional){
    //TODO
    // Breadth first traversal from sourceProfessional. Format for printing:

    //// for the source vertex in the network
    //cout << "Starting Professional (root): " << sourceProfessional << "-> ";
    //// for other professional vertex traversed from source professional vertex which is are various connectionOrders
    //cout << n->neighbors[x].v->name <<"("<< n->neighbors[x].v->connectionOrder <<")"<< " ";

    //Starting Professional (root): Marley-> Dylan(1) Lennon(2) Presley(2) McCartney(3) 
    bfs_helper(sourceProfessional, professionals);

}

void bfs_helper(string source, vector<Professional*> &professionals){

    cout << "Starting Professional (root): " << source << "-> ";

    int idx = 0;
    int max = professionals.size();

    for (int i = 0; i < max; i++){ // goes through and checks if name is already in list
        if (source == professionals[i]->name){
            idx = i;
        }
    }

    vector<Professional*> queue;

    int count = 0;
    queue.push_back(professionals[idx]);
    professionals[idx]->visited = true;
    professionals[idx]->connectionOrder = count;

    while (!queue.empty()){
        Professional *current = queue[0];

        count = current->connectionOrder + 1;

        int maxNeighbor = current->neighbors.size();
        for (int j = 0; j < maxNeighbor; j++){
            if (current->neighbors[j].v->visited == 0){
                current->neighbors[j].v->visited = 1;
                current->neighbors[j].v->connectionOrder = count;
                cout << current->neighbors[j].v->name << "(" << current->neighbors[j].v->connectionOrder << ") ";
                queue.push_back(current->neighbors[j].v);
            }  
        }
        queue.erase(queue.begin());
    }
}

vector<string> bfs_helper2(string source, vector<Professional*> &professionals, int k);

vector<string> LinkedInNetwork::suggestProfessionalsWithinKthOrder(string professionalName, int k){
    /*
    vector<string> professionalsWithinK;

    // Imagine that professionalName has joined linkedIn recently, and have added a few connections. Therefore, 
    //to increase activity (i.e., sending a direct message to his connections and/or send new connection requests), 
    //the linkedIn platform wants to show all the professionals who professionalName might know. This function returns
    //the list of professionals who are a maximum of Kth order of connection from professionalName. The order of the
    //names of vertices is the same as the order in which they were added to the linkedIn network.

    // Note that for every test run, we make a new graph entirely. So there is no need to reset the visited booleans to
    // false or the conectionOrders to zero.

    professionalsWithinK = bfs_helper2(professionalName, professionals, k);

    return professionalsWithinK;
    */
    vector<string> professionalsWithinK;
    vector<Professional*> professionalsWithinK_pointers;

    int idx = 0;
    int max = professionals.size();
    string names [max];

    for (int i = 0; i < max; i++){ // goes through and checks if name is already in list
        if (professionalName == professionals[i]->name){
            idx = i;
        }
        names[i] = professionals[i]->name;
    }

    queue<Professional*> queue;

    int count = 0;
    queue.push(professionals[idx]);
    professionals[idx]->visited = true;
    professionals[idx]->connectionOrder = count;

    while (!queue.empty()){
        //Professional *current = queue[0]; // Was a vector before but now its a queue

        Professional *current = queue.front();
        count = current->connectionOrder + 1;

        //queue.erase(queue.begin());
        queue.pop();

        int maxNeighbor = current->neighbors.size();
        //for (int j = maxNeighbor-1; j >= 0; j--){ // Trying reverse order
        for (int j = 0; j < maxNeighbor; j++){

            if (current->neighbors[j].v->visited == 0){
                current->neighbors[j].v->visited = 1;
                queue.push(current->neighbors[j].v);
                //professionalsWithinK.push_back(current->neighbors[j].v->name);
                current->neighbors[j].v->connectionOrder = count;
                //cout << current->neighbors[j].v->name << "(" << current->neighbors[j].v->connectionOrder << ") ";

                //professionalsWithinK.push_back(current->neighbors[j].v->name); // Just the names
                professionalsWithinK_pointers.push_back(current->neighbors[j].v);
                
                /*
                if (current->neighbors[j].v->connectionOrder <= k){
                    professionalsWithinK.push_back(current->neighbors[j].v->name);
                }
                */
                
            }
        }
        // queue.erase(queue.begin());
    }

    //sort(professionalsWithinK.begin(), professionalsWithinK.end()); // Trying alphabetical

    
    //Professional *current = queue.front();
    /*
    for (int l = 0; l < professionalsWithinK_pointers.size(); l++){
        if (professionalsWithinK_pointers[l]->connectionOrder <= k){
            professionalsWithinK.push_back(professionalsWithinK_pointers[l]->name);
        }
    }
    */
    for (int m = 0; m < max; m++){
        for (int l = 0; l < professionalsWithinK_pointers.size(); l++){
            if (names[m] == professionalsWithinK_pointers[l]->name){
                if (professionalsWithinK_pointers[l]->connectionOrder <= k){
                    professionalsWithinK.push_back(professionalsWithinK_pointers[l]->name);
                }
            }
        }
    }

    return professionalsWithinK;
}

/*
vector<string> bfs_helper2(string source, vector<Professional*>& professionals, int k)
{
    vector<string> professionalsWithinK;
    vector<Professional*> professionalsWithinK_pointers;

    int idx = -1;

    // Find the index of the starting professional
    for (int i = 0; i < professionals.size(); i++)
    {
        if (source == professionals[i]->name)
        {
            idx = i;
            break;
        }
    }

    // If the starting professional is not found, return empty vector
    if (idx == -1)
    {
        return professionalsWithinK;
    }

    queue<Professional*> queue;
    int count = 0;
    queue.push(professionals[idx]);
    professionals[idx]->visited = true;
    professionals[idx]->connectionOrder = count;

    while (!queue.empty())
    {
        Professional* current = queue.front();
        count = current->connectionOrder + 1;

        queue.pop();

        int maxNeighbor = current->neighbors.size();
        for (int j = 0; j < maxNeighbor; j++)
        {
            if (current->neighbors[j].v->visited == false)
            {
                current->neighbors[j].v->visited = true;
                queue.push(current->neighbors[j].v);
                current->neighbors[j].v->connectionOrder = count;

                if (count <= k)
                {
                    professionalsWithinK_pointers.push_back(current->neighbors[j].v);
                }
            }
        }
    }

    // Sort the pointers based on connection order
    sort(professionalsWithinK_pointers.begin(), professionalsWithinK_pointers.end(),
         [](Professional* p1, Professional* p2) { return p1->connectionOrder < p2->connectionOrder; });

    // Add the names of professionals within kth order to the output vector
    for (int l = 0; l < professionalsWithinK_pointers.size(); l++)
    {
        if (professionalsWithinK_pointers[l]->connectionOrder <= k)
        {
            professionalsWithinK.push_back(professionalsWithinK_pointers[l]->name);
        }
    }

    sort(professionalsWithinK.begin(), professionalsWithinK.end(),
         [](string p1, string p2) { return p1 < p2; });
    
    // Reset visited and connectionOrder flags for all professionals
    for (int i = 0; i < professionals.size(); i++)
    {
        professionals[i]->visited = false;
        professionals[i]->connectionOrder = -1;
    }

    return professionalsWithinK;
}
*/

/*
vector<string> bfs_helper2(string source, vector<Professional*> &professionals, int k){

    vector<string> professionalsWithinK;
    vector<Professional*> professionalsWithinK_pointers;

    int idx = 0;
    int max = professionals.size();

    for (int i = 0; i < max; i++){ // goes through and checks if name is already in list
        if (source == professionals[i]->name){
            idx = i;
        }
    }

    queue<Professional*> queue;

    int count = 0;
    queue.push(professionals[idx]);
    professionals[idx]->visited = true;
    professionals[idx]->connectionOrder = count;

    while (!queue.empty()){
        //Professional *current = queue[0]; // Was a vector before but now its a queue

        Professional *current = queue.front();
        count = current->connectionOrder + 1;

        //queue.erase(queue.begin());
        queue.pop();

        int maxNeighbor = current->neighbors.size();
        //for (int j = maxNeighbor-1; j >= 0; j--){ // Trying reverse order
        for (int j = 0; j < maxNeighbor; j++){

            if (current->neighbors[j].v->visited == 0){
                current->neighbors[j].v->visited = 1;
                queue.push(current->neighbors[j].v);
                //professionalsWithinK.push_back(current->neighbors[j].v->name);
                current->neighbors[j].v->connectionOrder = count;
                //cout << current->neighbors[j].v->name << "(" << current->neighbors[j].v->connectionOrder << ") ";

                //professionalsWithinK.push_back(current->neighbors[j].v->name); // Just the names
                professionalsWithinK_pointers.push_back(current->neighbors[j].v);
                
                
                if (current->neighbors[j].v->connectionOrder <= k){
                    professionalsWithinK.push_back(current->neighbors[j].v->name);
                }
                
            }
        }
        // queue.erase(queue.begin());
    }

    sort(professionalsWithinK.begin(), professionalsWithinK.end()); // Trying alphabetical

    //Professional *current = queue.front();
    for (int l = 0; l < professionalsWithinK_pointers.size(); l++){
        if (professionalsWithinK_pointers[l]->connectionOrder <= k){
            professionalsWithinK.push_back(professionalsWithinK_pointers[l]->name);
        }
    }

    return professionalsWithinK;
}
*/