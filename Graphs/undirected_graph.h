#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_set>
#include <unordered_map>

#include "vertex.h"

template <typename T = int>
class undirected_graph
{

public:

	// maps value of vertex to a vertex
	std::unordered_map<T, vertex<T>> vertices;

	// key is vertex and value is set of it's edges
	// edges is a pair, first is vertex and second is weight of vertex
	std::unordered_map<T, std::unordered_set<std::pair<T, int>>> adjacency_list;

	void _add_edges(std::vector<T>& edges)
	{
		auto start = edges.begin();
		while(start != edges.end())
		{
			T vertex1 = *start;
			T vertex2 = *(++start);
			adjacency_list[vertex1].insert(vertex2);
			adjacency_list[vertex2].insert(vertex1);
		}
	}

	undirected_graph(std::vector<T> vertices)
	{
		for (auto it = vertices.begin(); it != vertices.end(); ++it)
		{
			vertex v = new vertex;
			v->value = *it;
			this->vertices[*it] = v;
		}
	}

	undirected_graph(int no_of_vertices)
	{
		for (int i = 1; i != no_of_vertices+1 ; ++i)
		{
			vertex v = new vertex;
			v->value = i;
			vertices[i] = v;
		}
	}

	undirected_graph(std::vector<T> vertices,
					 std::vector<T> edges)
	{
		this->vertices = vertices;
		_add_edges(edges);
	}

	void remove_vertex(T vertex)
	{
		vertices.erase(vertex);
		for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it)
		{
			it->second.erase(vertex);
		}
	}

	void remove_edge(T vertex1, T vertex2)
	{
		adjacency_list[vertex1].erase(vertex2);
		adjacency_list[vertex2].erase(vertex1);
	}

	void add_vertex(T vertex)
	{
		vertices.insert(vertex);
	}

	void add_vertices(std::vector<T> vertices)
	{
		for (auto vertex: vertices)
		{
			this->vertices.insert(vertex);
		}
	}

	void add_edge(T vertex1, T vertex2)
	{
		_add_edges({vertex1, vertex2});
	}

	void add_edges(std::vector<T> edges)
	{
		_add_edges(edges);
	}

	std::vector<std::vector<T>> get_adjacency_matrix()
	{

	}
}

#endif