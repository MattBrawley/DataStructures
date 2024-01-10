// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"
#include "../code/worldMap.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;

/////////////////////////////////////////
// Tests start here for Assn-9
/////////////////////////////////////////

TEST_F(test_x, Test_CreateMap) {
    string result, expected;

    // Test A
    string test_a_path = "../tests/data/test_a.txt";
    result = test_createMap(test_a_path);
    expected = "| 1 | 0 | 1 |\n| 0 | 0 | 1 |\n| 0 | 1 | 1 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);

    // Test B
    string test_b_path = "../tests/data/test_b.txt";
    result = test_createMap(test_b_path);
    expected = "| 1 | 0 | 1 | 0 | 0 |\n| 0 | 0 | 0 | 1 | 1 |\n| 1 | 1 | 1 | 0 | 1 |\n| 0 | 0 | 0 | 1 | 0 |\n| 1 | 1 | 0 | 1 | 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);

    // Test C
    string test_c_path = "../tests/data/test_c.txt";
    result = test_createMap(test_c_path);
    expected = "| 1 | 0 | 1 | 1 |\n| 1 | 0 | 0 | 1 |\n| 1 | 0 | 1 | 1 |\n| 0 | 0 | 0 | 1 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);
}

TEST_F(test_x, Test_PrintWorldMap)
{
    string result, expected;

    // Test A
    string test_a = "../tests/data/test_a.txt";
    WorldMap world_map_a;
    world_map_a.createWorldMap(test_a);

    result = test_printMap(world_map_a);
    expected = "| 1 | 0 | 1 |\n| 0 | 0 | 1 |\n| 0 | 1 | 1 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);

    // Test B
    string test_b = "../tests/data/test_b.txt";
    WorldMap world_map_b;
    world_map_b.createWorldMap(test_b);

    result = test_printMap(world_map_b);
    expected = "| 1 | 0 | 1 | 0 | 0 |\n| 0 | 0 | 0 | 1 | 1 |\n| 1 | 1 | 1 | 0 | 1 |\n| 0 | 0 | 0 | 1 | 0 |\n| 1 | 1 | 0 | 1 | 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);

    // Test C
    string test_c = "../tests/data/test_c.txt";
    WorldMap world_map_c;
    world_map_c.createWorldMap(test_c);

    result = test_printMap(world_map_c);
    expected = "| 1 | 0 | 1 | 1 |\n| 1 | 0 | 0 | 1 |\n| 1 | 0 | 1 | 1 |\n| 0 | 0 | 0 | 1 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);
    
}

TEST_F(test_x, Test_AddRegion) {
    string result, expected;

    // Test A
    string test_default = "../tests/data/test_a.txt";
    WorldMap world_map_a;
    world_map_a.createWorldMap(test_default);
    world_map_a.addRegion(0, 0);
    world_map_a.addRegion(0, 2);
    world_map_a.addRegion(2, 2);

    auto regions = world_map_a.getRegions();

    ASSERT_TRUE(regions.size() > 0);
    ASSERT_TRUE(regions[0]->x == 0 && regions[0]->y == 0);
    add_points_to_grade(4.0);

    // Test B
    string test_b = "../tests/data/test_b.txt";
    WorldMap world_map_b;
    world_map_b.createWorldMap(test_b);
    world_map_b.addRegion(0, 0);
    world_map_b.addRegion(0, 2);
    world_map_b.addRegion(2, 2);
    world_map_b.addRegion(4, 4);
    world_map_b.addRegion(4, 0);

    regions = world_map_b.getRegions();

    ASSERT_TRUE(regions[0]->x == 0 && regions[0]->y == 0);
    ASSERT_TRUE(regions[1]->x == 0 && regions[1]->y == 2);
    ASSERT_TRUE(regions[2]->x == 2 && regions[2]->y == 2);
    ASSERT_TRUE(regions[3]->x == 4 && regions[3]->y == 4);
    ASSERT_TRUE(regions[4]->x == 4 && regions[4]->y == 0);
    add_points_to_grade(4.0);

    // Test C
    string test_c = "../tests/data/test_c.txt";
    WorldMap world_map_c;
    world_map_c.createWorldMap(test_c);
    world_map_c.addRegion(0, 0);
    world_map_c.addRegion(0, 2);
    world_map_c.addRegion(2, 2);
    world_map_c.addRegion(3, 3);

    regions = world_map_c.getRegions();

    ASSERT_TRUE(regions[0]->x == 0 && regions[0]->y == 0);
    ASSERT_TRUE(regions[1]->x == 0 && regions[1]->y == 2);
    ASSERT_TRUE(regions[2]->x == 2 && regions[2]->y == 2);
    ASSERT_TRUE(regions[3]->x == 3 && regions[3]->y == 3);
    add_points_to_grade(4.0);
}

TEST_F(test_x, Test_FindAdjacentLandRegions)
{
    string result, expected;

    // Test A
    string test_a = "../tests/data/test_a.txt";
    WorldMap world_map_a;
    world_map_a.createWorldMap(test_a);
    world_map_a.addRegion(0, 0);
    world_map_a.addRegion(0, 2);
    world_map_a.addRegion(1, 2);
    world_map_a.addRegion(2, 1);
    world_map_a.addRegion(2, 2);

    auto adjacent_regions = world_map_a.findAdjacentLandRegions(0, 0);
    ASSERT_TRUE(adjacent_regions.size() == 0); // Node 0,0 has no adjacent land regions

    adjacent_regions = world_map_a.findAdjacentLandRegions(0, 2);
    ASSERT_TRUE(adjacent_regions.size() == 1); // Node 0,2 has 1 adjacent land region
    add_points_to_grade(4.0);

    // Test B
    string test_b = "../tests/data/test_b.txt";
    WorldMap world_map_b;
    world_map_b.createWorldMap(test_b);
    world_map_b.addRegion(0, 0);
    world_map_b.addRegion(0, 2);
    world_map_b.addRegion(1, 3);
    world_map_b.addRegion(1, 3);
    world_map_b.addRegion(2, 0);
    world_map_b.addRegion(2, 1);
    world_map_b.addRegion(2, 2);
    world_map_b.addRegion(2, 4);
    world_map_b.addRegion(3, 3);
    world_map_b.addRegion(4, 0);
    world_map_b.addRegion(4, 1);
    world_map_b.addRegion(4, 3);


    adjacent_regions = world_map_b.findAdjacentLandRegions(2, 2);
    ASSERT_TRUE(adjacent_regions.size() == 3); // Node 2,2 has 3 adjacent land regions

    adjacent_regions = world_map_b.findAdjacentLandRegions(0, 4);
    ASSERT_TRUE(adjacent_regions.size() == 2); // Node 4,0 has 2 adjacent land regions
    add_points_to_grade(4.0);

    // Test C
    string test_c = "../tests/data/test_c.txt";
    WorldMap world_map_c;
    world_map_c.createWorldMap(test_c);
    world_map_c.addRegion(0, 0);
    world_map_c.addRegion(0, 2);
    world_map_c.addRegion(0, 3);
    world_map_c.addRegion(1, 0);
    world_map_c.addRegion(1, 3);
    world_map_c.addRegion(2, 0);
    world_map_c.addRegion(2, 2);
    world_map_c.addRegion(2, 3);
    world_map_c.addRegion(3, 3);

    adjacent_regions = world_map_c.findAdjacentLandRegions(2, 2);
    ASSERT_TRUE(adjacent_regions.size() == 3); // Node 2,2 has 3 adjacent land regions

    adjacent_regions = world_map_c.findAdjacentLandRegions(0, 4);
    ASSERT_TRUE(adjacent_regions.size() == 2); // Node 4,0 has 2 adjacent land regions
    add_points_to_grade(4.0);
}

TEST_F(test_x, Test_DisplayEdges)
{
    string result, expected;

    // Test A
    string test_a = "../tests/data/test_a.txt";
    WorldMap world_map_a;
    world_map_a.createWorldMap(test_a);
    world_map_a.addRegion(0, 0);
    world_map_a.addRegion(0, 2);
    world_map_a.addRegion(1, 2);
    world_map_a.addRegion(2, 1);
    world_map_a.addRegion(2, 2);

    result = test_printEdges(world_map_a);
    expected = "(0,0) --> \n(0,2) --> \n(1,2) --> \n(2,1) --> \n(2,2) --> \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);

    // Test B
    string test_b = "../tests/data/test_b.txt";
    WorldMap world_map_b;
    world_map_b.createWorldMap(test_b);
    world_map_b.addRegion(0, 0);
    world_map_b.addRegion(0, 2);
    world_map_b.addRegion(1, 3);
    world_map_b.addRegion(1, 3);
    world_map_b.addRegion(2, 0);
    world_map_b.addRegion(2, 1);
    world_map_b.addRegion(2, 2);
    world_map_b.addRegion(2, 4);
    world_map_b.addRegion(3, 3);
    world_map_b.addRegion(4, 0);
    world_map_b.addRegion(4, 1);
    world_map_b.addRegion(4, 3);

    result = test_printEdges(world_map_b);
    expected = "(0,0) --> \n(0,2) --> \n(1,3) --> \n(2,0) --> \n(2,1) --> \n(2,2) --> \n(2,4) --> \n(3,3) --> \n(4,0) --> \n(4,1) --> \n(4,3) --> \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);

    // Test C
    string test_c = "../tests/data/test_c.txt";
    WorldMap world_map_c;
    world_map_c.createWorldMap(test_c);
    world_map_c.addRegion(0, 0);
    world_map_c.addRegion(0, 2);
    world_map_c.addRegion(0, 3);
    world_map_c.addRegion(1, 0);
    world_map_c.addRegion(1, 3);
    world_map_c.addRegion(2, 0);
    world_map_c.addRegion(2, 2);
    world_map_c.addRegion(2, 3);
    world_map_c.addRegion(3, 3);

    result = test_printEdges(world_map_c);
    expected = "(0,0) --> \n(0,2) --> \n(0,3) --> \n(1,0) --> \n(1,3) --> \n(2,0) --> \n(2,2) --> \n(2,3) --> \n(3,3) --> \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);
}

TEST_F(test_x, Test_AddEdgeBetweenRegions)
{
    // Test A
    string test_a = "../tests/data/test_a.txt";
    WorldMap world_map_a;
    world_map_a.createWorldMap(test_a);
    world_map_a.addRegion(0, 0);
    world_map_a.addRegion(0, 2);
    world_map_a.addRegion(1, 2);
    world_map_a.addRegion(2, 1);
    world_map_a.addRegion(2, 2);

    world_map_a.addEdgeBetweenRegions(0, 2, 1, 2);
    world_map_a.addEdgeBetweenRegions(1, 2, 2, 2);

    string result = test_printEdges(world_map_a);
    string expected = "(0,0) --> \n(0,2) --> (1,2) \n(1,2) --> (0,2) (2,2) \n(2,1) --> \n(2,2) --> (1,2) \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);

    // Test B
    string test_b = "../tests/data/test_b.txt";
    WorldMap world_map_b;
    world_map_b.createWorldMap(test_b);
    world_map_b.addRegion(0, 0);
    world_map_b.addRegion(0, 2);
    world_map_b.addRegion(1, 3);
    world_map_b.addRegion(1, 3);
    world_map_b.addRegion(2, 0);
    world_map_b.addRegion(2, 1);
    world_map_b.addRegion(2, 2);
    world_map_b.addRegion(2, 4);
    world_map_b.addRegion(3, 3);
    world_map_b.addRegion(4, 0);
    world_map_b.addRegion(4, 1);
    world_map_b.addRegion(4, 3);

    world_map_b.addEdgeBetweenRegions(0, 2, 1, 3);
    world_map_b.addEdgeBetweenRegions(1, 3, 1, 4);

    result = test_printEdges(world_map_b);
    expected = "(0,0) --> \n(0,2) --> (1,3) \n(1,3) --> (0,2) \n(2,0) --> \n(2,1) --> \n(2,2) --> \n(2,4) --> \n(3,3) --> \n(4,0) --> \n(4,1) --> \n(4,3) --> \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);

    // Test C
    string test_c = "../tests/data/test_c.txt";
    WorldMap world_map_c;
    world_map_c.createWorldMap(test_c);
    world_map_c.addRegion(0, 0);
    world_map_c.addRegion(0, 2);
    world_map_c.addRegion(0, 3);
    world_map_c.addRegion(1, 0);
    world_map_c.addRegion(1, 3);
    world_map_c.addRegion(2, 0);
    world_map_c.addRegion(2, 2);
    world_map_c.addRegion(2, 3);
    world_map_c.addRegion(3, 3);

    world_map_c.addEdgeBetweenRegions(0, 0, 1, 0);
    world_map_c.addEdgeBetweenRegions(1, 0, 2, 0);

    result = test_printEdges(world_map_c);
    expected = "(0,0) --> (1,0) \n(0,2) --> \n(0,3) --> \n(1,0) --> (0,0) (2,0) \n(1,3) --> \n(2,0) --> (1,0) \n(2,2) --> \n(2,3) --> \n(3,3) --> \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);
}

TEST_F(test_x, Test_ConvertWorldMapToAdjacencyListGraph)
{
    string result, expected;

    // Test A
    string test_a = "../tests/data/test_a.txt";
    WorldMap world_map_a;
    world_map_a.createWorldMap(test_a);
    world_map_a.convertWorldMapToAdjacencyListGraph();

    result = test_printEdges(world_map_a);
    expected = "(0,0) --> \n(0,2) --> (1,2) \n(1,2) --> (0,2) (2,1) (2,2) \n(2,1) --> (1,2) (2,2) \n(2,2) --> (1,2) (2,1) \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);

    // Test B
    string test_b = "../tests/data/test_b.txt";
    WorldMap world_map_b;
    world_map_b.createWorldMap(test_b);
    world_map_b.convertWorldMapToAdjacencyListGraph();

    result = test_printEdges(world_map_b);
    expected = "(0,0) --> \n(0,2) --> (1,3) \n(1,3) --> (0,2) (1,4) (2,2) (2,4) \n(1,4) --> (1,3) (2,4) \n(2,0) --> (2,1) \n(2,1) --> (2,0) (2,2) \n(2,2) --> (1,3) (2,1) (3,3) \n(2,4) --> (1,3) (1,4) (3,3) \n(3,3) --> (2,2) (2,4) (4,3) \n(4,0) --> (4,1) \n(4,1) --> (4,0) \n(4,3) --> (3,3) \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(5.0);

    // Test C
    string test_c = "../tests/data/test_c.txt";
    WorldMap world_map_c;
    world_map_c.createWorldMap(test_c);
    world_map_c.convertWorldMapToAdjacencyListGraph();

    result = test_printEdges(world_map_c);
    expected = "(0,0) --> (1,0) \n(0,2) --> (0,3) (1,3) \n(0,3) --> (0,2) (1,3) \n(1,0) --> (0,0) (2,0) \n(1,3) --> (0,2) (0,3) (2,2) (2,3) \n(2,0) --> (1,0) \n(2,2) --> (1,3) (2,3) (3,3) \n(2,3) --> (1,3) (2,2) (3,3) \n(3,3) --> (2,2) (2,3) \n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4.0);
}

TEST_F(test_x, Test_FindNumOfIslands)
{
    string result, expected;

    // Test A
    string test_a = "../tests/data/test_a.txt";
    WorldMap world_map_a;
    world_map_a.createWorldMap(test_a);
    world_map_a.convertWorldMapToAdjacencyListGraph();

    int num_islands = test_findNumOfIslands(world_map_a);
    ASSERT_EQ(2, num_islands); // This file should have 2 islands
    add_points_to_grade(5.0);

    // Test B
    string test_b = "../tests/data/test_b.txt";
    WorldMap world_map_b;
    world_map_b.createWorldMap(test_b);
    world_map_b.convertWorldMapToAdjacencyListGraph();

    num_islands = test_findNumOfIslands(world_map_b);
    ASSERT_EQ(3, num_islands); // This file should have 3 islands
    add_points_to_grade(5.0);

    // Test C
    string test_c = "../tests/data/test_c.txt";
    WorldMap world_map_c;
    world_map_c.createWorldMap(test_c);
    world_map_c.convertWorldMapToAdjacencyListGraph();

    num_islands = test_findNumOfIslands(world_map_c);
    ASSERT_EQ(2, num_islands); // This file should have 2 islands
    add_points_to_grade(5.0);
}