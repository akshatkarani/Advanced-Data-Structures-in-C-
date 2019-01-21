#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <algorithm>

struct Node
{
	Node* parent;
	int data;
	int rank;
};

class DisjointSet
{
	std::map<int, Node*> all_sets;

	Node* path_compression(Node* temp)
	{
		if(temp != temp->parent)
			temp->parent = path_compression(temp->parent);
		return temp->parent;
	}
public:

	void make_set(int data)
	{
		Node* temp = new Node;
		temp->data = data;
		temp->parent = temp;
		temp->rank = 0;
		all_sets[data] = temp;
	}

	void union_set(int num1, int num2)
	{
		Node* root1 = this->find_set(num1);
		Node* root2 = this->find_set(num2);
		if(root1->rank > root2->rank)
		{
			root2->parent = root1;
		}
		else
		{
			root1->parent = root2;
			if(root1->rank == root2->rank)
				++ root2->rank;
		}
	}

	Node* find_set(int data)
	{
		return this->path_compression(all_sets[data]);
	}
};

struct less_than
{
	inline bool operator() (std::map<std::pair<int, int>, int>::iterator map1, std::map<std::pair<int, int>, int>::iterator map2)
	{
		return map1->second < map2->second;
	}
};

class Graph
{
public:
	std::vector<int> vertices;
	std::map<std::pair<int,int>, int> edges;
	std::map<int, std::vector<int>> adjacency_list;
	Graph(std::map<int, int> vertice, std::vector<int> edge)
	{
		for(auto it = vertice.begin(); it != vertice.end(); ++it)
			this->vertices.push_back(it->first);

		for(auto it = edge.begin(); it != edge.end(); ++it)
		{
			int a = *it;
			int b = *++it;
			adjacency_list[a].push_back(b);
			adjacency_list[b].push_back(a);
			std::pair<int, int> temp(a,b);
			edges[temp] = *++it;
		}
	}

	std::map<std::pair<int, int>, int> mst()
	{
		std::vector<std::map<std::pair<int, int>, int>::iterator> v;
		for(auto it = edges.begin(); it != edges.end(); ++it)
			v.push_back(it);
		
		std::sort(v.begin(), v.end(), less_than());

		DisjointSet djs;
		std::map<std::pair<int, int>, int> setA;
		for(auto it = vertices.begin(); it != vertices.end(); ++it)
			djs.make_set(*it);
		for(auto it = v.begin(); it != v.end(); ++it)
		{
			if(djs.find_set(((*it)->first).first)->data != djs.find_set(((*it)->first).second)->data)
			{
				setA[(*it)->first] = (*it)->second;
				djs.union_set(((*it)->first).first, ((*it)->first).second);
			}
		}
		return setA;
	}	
};

int main(int argc, char const *argv[])
{	
	std::ifstream cin1(argv[1]);
	std::istream_iterator<std::string> it(cin1);
	std::istream_iterator<std::string> eos;
	std::ofstream out;
	out.open("mst.txt");

	std::vector<int> edges;
	std::map<int, int> vertices;
	while(it != eos)
	{
		edges.push_back(stoi(*it));
		++vertices[stoi(*it)];
		++it;
	}
	
	Graph g(vertices, edges);
	
	std::map<std::pair<int, int>, int> setA = g.mst();
	for(auto it = setA.begin(); it != setA.end(); ++it)
		out<<it->first.first<<" "<<it->first.second<<" "<<it->second<<std::endl;
	return 0;
}