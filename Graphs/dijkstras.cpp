#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

struct Vertex
{
	int data, distance;
	Vertex* parent;
	
};

struct Compare
{
	inline bool operator() (const Vertex* v1, const Vertex* v2)
	{
		return (v1->distance < v2->distance);
	}
};

class Graph
{
	std::ofstream out;
	//maps the data of vertex to pointer to it
	std::map<int, Vertex*> all_vertices;
	//adjacency list of graph
	std::map<int, std::vector<std::pair<int, int>>> adjacency_list;

public:
	Graph(std::vector<int> input)
	{
		//input file consists of numbers: start end weight
		//using temp to find all vertices
		std::map<int, int> temp;
		for(auto it = input.begin(); it != input.end(); ++ it)
		{
			int start = *it;
			int end = *++ it;
			int weight = *++ it;

			std::pair<int, int> temp_pair(end, weight);
			adjacency_list[start].push_back(temp_pair);

			++ temp[start];
			++ temp[end];
		}
		for(auto it = temp.begin(); it != temp.end(); ++ it)
		{
			Vertex* vertex = new Vertex;
			vertex->data = it->first;
			//using 1073741823 as infinity
			vertex->distance = 1073741823;
			vertex->parent = nullptr;
			all_vertices[it->first] = vertex;
		}
		out.open("dijkstra.txt");
	}
	void dijkstra(int source)
	{
		for(auto it = adjacency_list.begin(); it != adjacency_list.end(); ++ it)
		{
			out<<it->first<<" ";
			for(auto itr = it->second.begin(); itr != it->second.end(); ++ itr)
				out<<itr->first<<" ";
			out<<std::endl;
		}
		std::vector<Vertex*> pq;
		all_vertices[source]->distance = 0;
		for(auto it = all_vertices.begin(); it != all_vertices.end(); ++ it)
			pq.push_back(it->second);
		while(!pq.empty())
		{
			/*for(auto it = pq.begin(); it != pq.end(); ++ it)
				out<<(*it)->distance<<" ";
			out<<std::endl;*/
			std::sort(pq.begin(), pq.end(), Compare());
			/*for(auto it = pq.begin(); it != pq.end(); ++ it)
				out<<(*it)->distance<<" ";
			out<<std::endl;*/
			Vertex* u = *pq.begin();
			for(auto it = adjacency_list[u->data].begin(); it != adjacency_list[u->data].end(); ++ it)
			{
				Vertex* v = all_vertices[it->first];
				if(u->distance + it->second < v->distance)
				{
					v->distance = u->distance + it->second;
					v->parent = u;
				}
			}
			pq.erase(pq.begin());
		}
		for(auto it = all_vertices.begin(); it != all_vertices.end(); ++ it)
		{
			if(it->second->distance == 1073741823)
				it->second->distance = -1;
			out<<it->first<<" "<<it->second->distance<<std::endl;
		}
	}
};

int main(int argc, char const *argv[])
{
	std::ifstream cin1(argv[1]);
	std::istream_iterator<std::string> it(cin1);
	std::istream_iterator<std::string> eos;
	std::vector<int> input;
	while(it != eos)
		input.push_back(stoi(*it ++));
	Graph g(input);
	g.dijkstra(std::stoi(argv[2]));
	return 0;
}