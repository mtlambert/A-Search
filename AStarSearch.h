#pragma once

#include <vector>
#include <array>
#include <string>

class AStar {
private:
	std::array<int, 2> start;
	std::array<int, 2> goal;
	std::vector<std::vector<int>> maze;
	enum class State {kOpen, kObsticle, kPath, kVisited, kStart, kGoal};
	std::vector<std::vector<State>> grid;
	
public:
	struct node;

	AStar (std::array<int, 2> s, std::array<int, 2> g, std::string file_name);

	std::vector<int> ParseLine(std::string line);

	std::vector<std::vector<int>> LoadMaze (std::string file_name);

	void TranslateMaze ();

	void PrintMaze();
	
	void PrintGrid();
	
	int CalcH(std::array<int, 2> y_x);
	
	void SetFVal(AStar::node &update_node);
	
	static bool CompareF(AStar::node node1, AStar::node node2);
	
	void SortOpen(std::vector<AStar::node> &open_nodes);
	
	std::vector<AStar::node> ExpandNode (AStar::node &expand_node);
	
	void Search();
	
	
};