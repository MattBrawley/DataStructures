#include <iostream>
#include <vector>
#include "../code/worldMap.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv) {

    WorldMap* wmap = new WorldMap; 
    wmap->createWorldMap(argv[1]);
    wmap->printWorldMap();

    wmap->convertWorldMapToAdjacencyListGraph();
    wmap->displayEdges();
    cout << "\n" << endl;
    cout << wmap->findNumOfIslands() << endl;


    return 0;
}