#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <string>

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

int main(int argc, char const *argv[])
{
	std::ifstream cin1(argv[1]);	
	std::istream_iterator<std::string> it(cin1);
	std::istream_iterator<std::string> eos;
	std::vector<int> inputdata;
	while(it != eos)
		inputdata.push_back(stoi(*it++));

	std::map<int, int> vertices;
	for(auto it = inputdata.begin(); it != inputdata.end(); ++it)
		++ vertices[*it];

	DisjointSet graph;
	for(auto it = vertices.begin(); it != vertices.end(); ++it)
		graph.make_set(it->first);

	for(auto it = inputdata.begin(); it != inputdata.end(); ++it)
	{
		int num1 = *it;
		it ++;
		int num2 = *it;
		graph.union_set(num1,num2);
	}

	std::map<int, std::vector<int>> components;
	for(auto it = vertices.begin(); it != vertices.end(); ++it)
	{
		int representative = (graph.find_set(it->first))->data;
		(components[representative]).push_back(it->first);
	}

	std::ofstream out;
	out.open("components.txt");
	for(auto it = components.begin(); it != components.end(); ++it)
	{
		for(auto itr = it->second.begin(); itr != it->second.end(); ++itr)
			out<<*itr<<" ";
		out<<std::endl;
	}

	return 0;
}