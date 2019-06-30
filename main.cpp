/*
	To Do List:
	* use a class sub to AStar called Node, AStar::Node::, rather than a struct so each node can have their own values and functions
	    - will require use of pointers and "this" to reference nodes and to have notes interact
	* nake the program more efficient, pass pointers rather than large objects or data structures,


	FYI:
	 * appliation currently saves two copies of maze, "maze" and "grid", this could be wasteful if mazes get large
	 * coordinates are "Y, X", not "X, Y"
*/

#include "AStarSearch.h"
#include <iostream>
#include <array>
#include <vector>
#include <string>

int main()
{
	std::array<int, 2> start1 {0,0};
	std::array<int, 2> goal1 {4,9};
	std::string file1 = "/home/matt/Desktop/CodeLiteProjects/AStarSearch/new_board.txt";
	
	std::array<int, 2> start2 {0,9};
	std::array<int, 2> goal2 {6,0};
	std::string file2 = "/home/matt/Desktop/CodeLiteProjects/AStarSearch/simple_maze.txt";
	
	std::array<int, 2> start3 {0,0};
	std::array<int, 2> goal3 {4,5};
	std::string file3 = "/home/matt/Desktop/CodeLiteProjects/AStarSearch/first_maze.txt";

	AStar new_search(start1, goal1, file1);
	
	new_search.PrintGrid();
	std::cout << "\n";
	new_search.Search();
	
	return 0;
}
