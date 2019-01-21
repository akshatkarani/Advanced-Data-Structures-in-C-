#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iterator>

struct Node
{
	int vertex;
	std::string color;
	int distance;
};

class Graph
{
	std::map<int, Node*> container;
	std::map<int, std::vector<int>> adjacency_list;
	std::stack<int> topological_sort;
	void reset()
	{
		for(auto it = container.begin(); it != container.end(); ++it)
			it->second->color = "white";
	}
public:
	Graph(std::vector<int> edges, std::map<int, int> vertices)
	{
		for(auto it = vertices.begin(); it != vertices.end(); ++it)
		{
			Node* temp = new Node;
			temp->vertex = it->first;
			temp->color = "white";
			temp->distance = 0;
			container[it->first] = temp;
		}
		for(auto it = edges.begin(); it != edges.end(); ++it)
		{
			adjacency_list[*it].push_back(*++it);
		}
	}

	void breadth_first(int source)
	{
		std::queue<int> breadth_space;
		container[source]->color = "grey";
		breadth_space.push(source);
		while(!breadth_space.empty())
		{			
			int temp = breadth_space.front();
			breadth_space.pop();
			for(auto it = adjacency_list[temp].begin();
				it != adjacency_list[temp].end(); ++it)
			{
				if(container[*it]->color == "white")
				{
					breadth_space.push(*it);
					container[*it]->color = "grey";
					container[*it]->distance = container[temp]->distance + 1;
				}
			}
			container[temp]->color = "black";
		}
	}

	void depth_visit(int num)
	{
		for(auto it = adjacency_list[num].begin(); it != adjacency_list[num].end(); ++it)
		{
			if(container[*it]->color == "white")
			{
				container[*it]->color = "grey";
				depth_visit(*it);
			}
		}
		topological_sort.push(num);
	}

	void depth_first()
	{
		for(auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it)
		{
			if(container[it->first]->color == "white")
			{
				container[it->first]->color = "grey";
				depth_visit(it->first);
				container[it->first]->color = "black";	
			}			
		}
	}

	void print_bfs(std::ofstream& out, int source)
	{
		this->reset();
		this->breadth_first(source);
		for(auto it = container.begin(); it != container.end(); ++it)
		{
			if(it->second->distance == 0)
				it->second->distance = -1;
			container[source]->distance = 0;
			out<<it->second->vertex<<" "<<it->second->distance<<std::endl;
		}
	}

	void print_dfs(std::ofstream& out)
	{
		this->reset();
		this->depth_first();
		while(!topological_sort.empty())
		{
			out<<topological_sort.top()<<std::endl;
			topological_sort.pop();
		}

	}
};

int main(int argc, char const *argv[])
{
	std::ifstream cin1(argv[1]);
	std::istream_iterator<std::string> it(cin1);
	std::istream_iterator<std::string> eos;
	std::vector<int> edges;
	std::map<int, int> vertices;
	while(it != eos)
	{
		++vertices[std::stoi(*it)];
		edges.push_back(std::stoi(*it));
		++it;
	}
	Graph g(edges, vertices);

	std::ofstream out1;
	out1.open("shortest_distance.txt");
	g.print_bfs(out1, std::stoi(argv[2]));

	std::ofstream out2;
	out2.open("topological_sort.txt");
	g.print_dfs(out2);
	return 0;
}