#ifndef WORLD_MAP_H
#define WORLD_MAP_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;


struct Region;

struct NeighboringRegion {
    Region *region;
};

struct Region {
    int x;
    int y;
    bool visited = false;
    vector <NeighboringRegion> neighbors;
};

class WorldMap {
    public:
        WorldMap(); 
        ~WorldMap(); 
        void createWorldMap(string);
        void printWorldMap(); 
        void addRegion(int, int);
        void addEdgeBetweenRegions(int, int, int, int);
        void displayEdges();
        vector<vector<int>> findAdjacentLandRegions(int, int);
        void convertWorldMapToAdjacencyListGraph(); 
        int findNumOfIslands(); 

        // Used for testing
        vector<Region*>& getRegions();

    private:
        int rows, cols;
        int **worldMap;  
        vector<Region*> regions; 
};

#endif // WORLD_MAP_H
