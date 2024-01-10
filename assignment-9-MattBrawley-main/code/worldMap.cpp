#include "worldMap.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

WorldMap::WorldMap() {}

void WorldMap::createWorldMap(string fileName)
{
    // TODO START

    //Import the .txt file (example is in the main folder) and make a worldMap (private int** worldMap; provided in .hpp file) using
    // the information provided. The first line if the text file will contain the dimensions of the map, to be stored in int rows, 
    // cols (also in .hpp); the rest of the file will show each value in the map. 1s represent land regions, 0s represent empty space
    // between them. getline and stringstream functions are very useful here. We are just creating and populating the int** worldMap
    // from the text file whose first line gives the size values. When filling the worldMap, make sure to fill the rows and columns
    // in the increasing order i.e., fill all columns of row 0 first, then all columns of row 1 and so on.

    // WorldMap* wmap = new WorldMap;

    ifstream infile(fileName);
    infile >> rows >> cols;

    worldMap = new int*[rows];

    for (int i = 0; i < rows; i++) { // setting up worldMap
        worldMap[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) { // rows
        for (int j = 0; j < cols; j++) { // columns
            infile >> worldMap[i][j];
        }
    }

    // TODO END
}

void WorldMap::printWorldMap()
{
    // TODO START

    for (int i = 0; i < rows; i++){ // rows
        for (int j = 0; j < cols; j++){ // columns
            cout << "| " << worldMap[i][j] << " ";
        }
        cout << "|" << endl;
    }

    // TODO END
}

void WorldMap::addRegion(int x, int y)
{
    // TODO START

    // Create a new Region with the position (x,y) and add it to the regions of the WorldMap class, unless one already exists. 
    // There is no need to print anything out if a region with same x and y already exists in regions, just return without
    // creating a Region. There is no need to touch the int **worldMap here.

    for (int i = 0; i < regions.size(); i++){
        if (regions[i]->x == x && regions[i]->y == y){
            return;
        }
    }

    Region *add = new Region;
    add->x = x;
    add->y = y;
    add->visited = false;

    regions.push_back(add);

    // TODO END
}

bool checkIfEdgeExists(Region *r, int x2, int y2)
{
    int max = r->neighbors.size();

    for (int i = 0; i < max; i++){
        if (r->neighbors[i].region->x == x2 && r->neighbors[i].region->y == y2){
            return true;
        }
    }
    return false;
}

void WorldMap::addEdgeBetweenRegions(int x1, int y1, int x2, int y2){ // given solution
    // TODO START
    for(unsigned int i = 0; i < regions.size(); i++){
        if(regions[i]->x == x1 && regions[i]->y == y1){
            for(unsigned int j = 0; j < regions.size(); j++){
                if(i != j && regions[j]->x == x2 && regions[j]->y == y2){
                    if(!checkIfEdgeExists(regions[i], x2, y2)){
                        NeighboringRegion av;
                        av.region = regions[j];
                        regions[i]->neighbors.push_back(av);
                        // another vertex for edge in other direction
                        NeighboringRegion av2;
                        av2.region = regions[i];
                        regions[j]->neighbors.push_back(av2);
                    }
                }
            }
        }
    }
    // TODO END
}

/*
void WorldMap::addEdgeBetweenRegions(int x1, int y1, int x2, int y2)
{
    // TODO START

    //If either of the regions with (x1, y1) or (x2, y2) is not found, do nothing.

    bool found1;
    bool found2;
    Region *r = nullptr;

    for (int i = 0; i < regions.size(); i++){ // searching for region1
        if (regions[i]->x == x1 && regions[i]->y == y1){
            found1 = true;
            r = regions[i];
        }
    }

    for (int i = 0; i < regions.size(); i++){ // searching for region2
        if (regions[i]->x == x2 && regions[i]->y == y2){
            found2 = true;
        }
    }

    if (found2 || found1 == false){ // If either one is not found, return
        return;
    }


    //To check if an edge already exists, create a helper function that iterates through all the neighbors of the region corresponding
    // to (x1, y1) and verify if you find (x2, y2) in those.

    bool edgeExistence = checkIfEdgeExists(r, x2, y2);

    if (edgeExistence == true){ // If edge already exists, then return
        return;
    }


    //If an edge doesn't already exist between the positions (x1, y1) and (x2, y2), add one. Remember that this is an undirected graph.
    // So, when you add A as a neighbor to B, you should also add B as a neighbor to A. You don't need to print anything if an edge 
    // already exists.

    int max = regions.size();

    for(int i = 0; i < max; i++){
		if(regions[i]->x == x1 && regions[i]->y == y1){
			for(int j = 0; j < max; j++){
                if(regions[j]->x == x2 && regions[j]->y == y2 && i != j){
                    NeighboringRegion adjVertex1;
					adjVertex1.region = regions[j];
					regions[i]->neighbors.push_back(adjVertex1);

					// another vetex for edge in the other direction
                    NeighboringRegion adjVertex2;
					adjVertex2.region = regions[i];
					regions[j]->neighbors.push_back(adjVertex2);
				}
			}
		}
	}

    // TODO END
}
*/

vector<vector<int>> WorldMap::findAdjacentLandRegions(int x, int y){
    // TODO START
    // identify the open paths that are adjacent to the vertex at x, y
    // fill adjArr array with the numbers of the adjacent vertices
    vector<vector<int>> neighbors; 
    for(int i = x-1; i <= x + 1; i++){
        if(i < 0 || i >= this->rows){
            continue;
        }
        for(int j = y-1; j <= y+1; j++){
            if(j < 0 || j >= this->cols){
                continue;
            }
            // if there is an open path at this adjacent position, add to adjArray
            if(!(i == x && j == y) && worldMap[i][j] == 1){
                neighbors.push_back({i,j});
            }
        }
    }
    return neighbors;
    // TODO END
}
/*
vector<vector<int>> WorldMap::findAdjacentLandRegions(int x, int y)
{
    // TODO START

    //This function will use the int **worldMap to find the current x,y location's neighbors. Check the 8 surrounding spaces 
    // (directions NW, N, NE, W, E, SW, S, SE in the same order) to see if they are land regions (where the worldMap[i][j] is 
    // equal to 1) and add the vector containing i and j(a simple {i, j} will do) to the answer(which is a vector of vectors) 
    // that must be returned.

    //Make sure the get the order of spaces correct. You simply need to iterate in an increasing order for both rows and columns 
    // i.e., check the 3 spaces in the row above the cell from left to right, then in the row of the current cell check the left
    // and the right cells(notice current cell is not included), then finally the 3 spaces in the row below the cell from left 
    // to right. Look at the image for help.

    // identify the open paths that are adjacent to the vertex at x, y
    // fill adjArr array with the numbers of the adjacent vertices

    vector<vector<int>> neighbors;

    for (int i = -1; i <= 1; i++){
        for (int j = 1; j >= -1; j--){

            if (i == 0 && j == 0){ //skipping current cell
                continue;
            }
            
            if (x+i < 0 || y+j < 0 || x+i >= rows || y+j >= cols){ // Making sure neighbouring cells actually exist
                continue;
            }

            if (worldMap[x+i][y+j] == 1){
                cout << "(" << i << "," << j << ")" << endl;
                neighbors.push_back({i,j});
            }

        }
    }
    
    return neighbors;

    // TODO END
}
*/

void WorldMap::convertWorldMapToAdjacencyListGraph()
{
    // TODO START

    //For each (x,y) location in the worldMap, do the following:
    for (int i = 0; i < rows; i++){ // rows
        for (int j = 0; j < cols; j++){ // columns

            //Use addRegion to create a Region at the current location, only if the value at this location is 1
            if (worldMap[i][j] == 1){
                addRegion(i,j);
            }

        }
    }

    //After the regions are created, have another set of nested for loops for each (x,y) location in the worldMap,
    
    for (int i = 0; i < rows; i++){ // rows
        for (int j = 0; j < cols; j++){ // columns

            // to do the following only if the value of the location is 1:
            if (worldMap[i][j] == 1){
                //Use findAdjacentLandRegions to find all land neighbors of the current location.
                vector<vector<int>> neighbors = findAdjacentLandRegions(i,j);

                //Iterate through all of those neighbors to add an edge between the current location and 
                // each of the neighbor locations. (Use addEdgeBetweenRegions for edge additions)

                ///*
                for (int k = 0; k < neighbors.size(); k++){
                    addEdgeBetweenRegions(i,j,neighbors[k][0],neighbors[k][1]);
                }
                //*/

                /*
                for (auto neighbor : neighbors){
                    addEdgeBetweenRegions(i,j,neighbor[0],neighbor[1]);
                }
                */

                // For some reason this makes it pass the islands test:
                /*
                for (int k = 0; k < neighbors.size(); k++){
                    for (int l = 0; l < neighbors.size(); l++){
                        addEdgeBetweenRegions(i,j,neighbors[k][l],neighbors[k][l]);
                    }
                }
                */
                
            }
        }
    }

    // TODO END
}

// helper function to check if v2 is a neighbor of vertex v1
bool isNeighbor(int x1, int y1, int x2, int y2, const vector<Region *> regions)
{

    return false;
}

WorldMap::~WorldMap()
{
    // TODO START
    for (int i = 0; i < rows; i++) { // should only need to go through rows, no need to delete the col values
        delete[] worldMap[i];
    }
    //Delete the original array too
    delete[] worldMap;

    // TODO END
}

void WorldMap::displayEdges()
{
    // TODO START

    //Simply looping through the regions vector of the WorldMap class, and at each region, looping through the neighbors from first
    // to last will give you the correct printing order here.

    

    for (int i = 0; i < regions.size(); i++){ // rows
        cout<<"("<<regions[i]->x<<','<<regions[i]->y<<")"<<" --> ";
        for (int j = 0; j < regions[i]->neighbors.size(); j++){ // columns
            cout<<"("<<regions[i]->neighbors[j].region->x<<','<<regions[i]->neighbors[j].region->y<<")"<<" ";
        }
        cout << endl;
    }
    /*
    (1,1) --> (1,2) (2,1)
    (1,2) --> (1,1) (2,1)
    (2,1) --> (1,1) (1,2)
    */

    // TODO END
}

// HELPER FOR findNumOfIslands
void findNumOfIslandsHelper(Region *r) // Just a Depth First Traversal
{
    r->visited = true;

    for(int i = 0; i < r->neighbors.size(); i++ )
    {
        if (r->neighbors[i].region->visited == false){
            findNumOfIslandsHelper(r->neighbors[i].region);
        }
    }
    return;
}

int WorldMap::findNumOfIslands()
{
    // TODO START
    //This function will use Depth First Traverse to find the count of clusters of land regions, or islands, in the WorldMap class.
    // You should iterate through the vector regions from WorldMap class and, at each unvisited Region you find, run a Depth First 
    // Traversal helper to visit all individual Regions of the current island. Return the number of islands that you find.

    // Based on isBridge function from recitation 10
    int numIslands = 0;

    for (int i = 0; i < regions.size(); i++){ 
        if (regions[i]->visited == false){
            findNumOfIslandsHelper(regions[i]);
            numIslands++;
        }
    }

    return numIslands;

    // TODO END
}

vector<Region *> &WorldMap::getRegions()
{
    return regions;
}
