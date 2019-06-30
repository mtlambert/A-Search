#include "AStarSearch.h"


struct AStar::node {
	std::array<int, 2> y_x;
	std::vector<std::array<int, 2>> visited;
	int g_val = 0;
	int f_val = 0;
};

AStar::AStar (std::array<int, 2> s, std::array<int, 2> g, std::string file_name) : 
		start(s), goal(g), maze(LoadMaze(file_name)) {TranslateMaze();};

std::vector<int> AStar::ParseLine (std::string line){
	std::vector<int> board_line;
	int num;
	char c;
	std::istringstream new_stream(line);
	while (new_stream >> num >> c){
		board_line.push_back(num);
	}
	return board_line;
}

std::vector<std::vector<int>> AStar::LoadMaze (std::string file_name){
	std::vector<std::vector<int>> return_maze;
	std::ifstream maze_file;
	maze_file.open(file_name, std::fstream::in);
	if (maze_file){
		std::string line;
		while (getline(maze_file, line)){
			return_maze.push_back(ParseLine(line));
		}
	};
	maze_file.close();
	return return_maze;
}

void AStar::TranslateMaze (){
	int x_size = maze[0].size();
	int y_size = maze.size();
	std::vector<State> row;
	
	for (int i = 0; i < y_size; i++){
		for (int j = 0; j < x_size; j++){
			switch (maze[i][j]){
				case 0:
					//std::cout << "Open, ";
					row.push_back(State::kOpen);
					//grid[i][j] = State::kOpen;
					break;
				case 1:
					//std::cout << "Obst, ";
					row.push_back(State::kObsticle);
					//grid[i][j] = State::kObsticle;
					break;
			}
		}
		grid.push_back(row);
		row = {};
	}
	grid[start[0]][start[1]] = State::kStart;
	grid[goal[0]][goal[1]] = State::kGoal;
}

void AStar::PrintMaze (){
	int x_size = maze[0].size();
	int y_size = maze.size();
	for (int i = 0; i < y_size; i++){
		for (int j = 0; j < x_size; j++){
			switch (maze[i][j]){
				case 0:
					std::cout << " .";
					break;
				case 1:
					std::cout << " O";
					break;
			}
		}
		std::cout << std::endl;
	}
}

void AStar::PrintGrid (){
	int x_size = grid[0].size();
	int y_size = grid.size();
	for (int i = 0; i < y_size; i++){
		for (int j = 0; j < x_size; j++){
			switch (grid[i][j]){
				case State::kOpen:
					std::cout << " .";
					break;
				case State::kObsticle:
					std::cout << " O";
					break;
				case State::kPath:
					std::cout << " *";
					break;
				case State::kVisited:
					std::cout << " .";
					break;
				case State::kStart:
					std::cout << " S";
					break;
				case State::kGoal:
					std::cout << " G";
					break;
			}
		}
		std::cout << std::endl;
	}
}

void AStar::PrintSolution(std::vector<std::array<int, 2>> path) {
	std::vector<std::vector<int>> solution = maze;
	for (std::array<int, 2> n: path) {
		solution[n[0]][n[1]] = 2;
	}
	solution[start[0]][start[1]] = 3;
	solution[goal[0]][goal[1]] = 4;
	int x_size = solution[0].size();
	int y_size = solution.size();
	for (int i = 0; i < y_size; i++){
		for (int j = 0; j < x_size; j++){
			switch (solution[i][j]){
				case 0:
					std::cout << " .";
					break;
				case 1:
					std::cout << " O";
					break;
				case 2:
					std::cout << " *";
					break;
				case 3:
					std::cout << " S";
					break;
				case 4:
					std::cout << " G";
					break;
			}
		}
		std::cout << std::endl;
	}
}

int AStar::CalcH(std::array<int, 2> y_x){
	return abs(y_x[0]-goal[0]) + abs(y_x[1]-goal[1]);
}

void AStar::SetFVal(AStar::node& update_node){
	update_node.f_val = update_node.g_val + CalcH(update_node.y_x);
}

bool AStar::CompareF(AStar::node node1, AStar::node node2){
	return node1.f_val > node2.f_val;
}

void AStar::SortOpen(std::vector<AStar::node> &open_nodes){
	sort(open_nodes.begin(), open_nodes.end(), CompareF);
}

std::vector<AStar::node> AStar::ExpandNode (AStar::node &expand_node){
	std::vector<AStar::node> expand_list;
	int x_size = maze[0].size()-1; // 9
	int y_size = maze.size()-1; // 6
	
	// top
	if (expand_node.y_x[0] != 0){
		if (grid[expand_node.y_x[0]-1][expand_node.y_x[1]] == State::kOpen || grid[expand_node.y_x[0]-1][expand_node.y_x[1]] == State::kGoal){
			AStar::node add_node {{expand_node.y_x[0]-1, expand_node.y_x[1]}, {}, expand_node.g_val+1, 0};
			SetFVal(add_node);
			
			for (std::array<int, 2> n: expand_node.visited) {
				add_node.visited.push_back(n);
			}
			add_node.visited.push_back(expand_node.y_x);
			
			expand_list.push_back(add_node);
			grid[expand_node.y_x[0]-1][expand_node.y_x[1]] = State::kVisited;
			//std::cout << "top" << "\n";
		}
	}
	// bottom
	if (expand_node.y_x[0] < y_size){
		if (grid[expand_node.y_x[0]+1][expand_node.y_x[1]] == State::kOpen || grid[expand_node.y_x[0]+1][expand_node.y_x[1]] == State::kGoal){
			AStar::node add_node {{expand_node.y_x[0]+1, expand_node.y_x[1]}, {}, expand_node.g_val+1, 0};
			SetFVal(add_node);
			
			for (std::array<int, 2> n: expand_node.visited) {
				add_node.visited.push_back(n);
			}
			add_node.visited.push_back(expand_node.y_x);
			
			expand_list.push_back(add_node);
			grid[expand_node.y_x[0]+1][expand_node.y_x[1]] = State::kVisited;
			//std::cout << "bottom" << "\n";
		}
	}
	// left
	if (expand_node.y_x[1] != 0){
		if (grid[expand_node.y_x[0]][expand_node.y_x[1]-1] == State::kOpen || grid[expand_node.y_x[0]][expand_node.y_x[1]-1] == State::kGoal){
			AStar::node add_node {{expand_node.y_x[0], expand_node.y_x[1]-1}, {}, expand_node.g_val+1, 0};
			SetFVal(add_node);
			
			for (std::array<int, 2> n: expand_node.visited) {
				add_node.visited.push_back(n);
			}
			add_node.visited.push_back(expand_node.y_x);
			
			expand_list.push_back(add_node);
			grid[expand_node.y_x[0]][expand_node.y_x[1]-1] = State::kVisited;
			//std::cout << "left" << "\n";
		}
	}
	// right
	if (expand_node.y_x[1] < x_size){
		if (grid[expand_node.y_x[0]][expand_node.y_x[1]+1] == State::kOpen || grid[expand_node.y_x[0]][expand_node.y_x[1]+1] == State::kGoal){
			AStar::node add_node {{expand_node.y_x[0], expand_node.y_x[1]+1}, {}, expand_node.g_val+1, 0};
			SetFVal(add_node);
			
			for (std::array<int, 2> n: expand_node.visited) {
				add_node.visited.push_back(n);
			}
			add_node.visited.push_back(expand_node.y_x);
			
			expand_list.push_back(add_node);
			grid[expand_node.y_x[0]][expand_node.y_x[1]+1] = State::kVisited;
			//std::cout << "right" << "\n";
		}
	}
	//std::cout << "\n";
	return expand_list;
}

void AStar::Search(){
	std::vector<AStar::node> open;
	AStar::node start_node {start, {}, 0, 0};
	SetFVal(start_node);
	open.push_back(start_node);
	AStar::node current;
	while (!open.empty()){
		SortOpen(open);
		current = open.back();
		open.pop_back();
		//std::cout << "Current: " << current.y_x[0] << ", " << current.y_x[1] << std::endl;
		if (current.y_x[0] == goal[0] && current.y_x[1] == goal[1]){
			current.visited.push_back(current.y_x);
			std::cout << "Path Found (G=" << current.g_val << ")" << std::endl;
			grid[start[0]][start[1]] = State::kStart;
			grid[goal[0]][goal[1]] = State::kGoal;
			
			// final path saved below for modifying and printinf maze solution
			std::vector<std::array<int, 2>> final_path = current.visited;
			std::cout << "Solution: " << "\n";
			for (std::array<int, 2> n: final_path) {
				std::cout << n[0] << ", " << n[1] << std::endl;
			}
			PrintSolution(final_path);
			
			return;
		}
		grid[current.y_x[0]][current.y_x[1]] = State::kPath;
		std::vector<AStar::node> new_nodes = ExpandNode(current);
		for (AStar::node n: new_nodes){
			open.push_back(n);
		}
	}
	std::cout << "Path not Found" << std::endl;
	grid[start[0]][start[1]] = State::kStart;
	grid[goal[0]][goal[1]] = State::kGoal;
	PrintGrid();
}



// Recursive Search

void AStar::PrintPath(AStar::node finish){
	for (std::array<int, 2> n: finish.visited) {
		std::cout << n[0] << ", " << n[1] << " | ";
	}
	std::cout << std::endl;
}
