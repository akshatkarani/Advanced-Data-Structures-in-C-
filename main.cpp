#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <memory>

struct Node
{
	std::string data;
	Node* next;
};

class LinkedList
{	
public:
	Node* head;
	LinkedList()
	{
		head = nullptr;
	}
	~LinkedList()
	{
		delete head;
	}
	
	void insert(std::string data)
	{
		Node* temp = new Node;
		temp->data = data;
		if(this->head == nullptr)
			this->head = temp;
		else
		{
			temp->next = this->head;
			this->head = temp;
		}
	}	
};

class HashTable : private LinkedList
{
	int size;
	std::vector<LinkedList*> hash_table;
	std::ofstream out;

	int hash_function(std::string data)
	{
		int hash_value = 0;
		for(unsigned i = 0; i != data.length(); i++)
		{
			hash_value += int(data[i]);
		}
		return hash_value % size;
	}
	bool check_anagram(std::string a, std::string b)
	{
		std::vector<char> v1, v2;
		for(unsigned i = 0; i != a.length(); i++)
			v1.push_back(a[i]);
		for(unsigned i = 0; i != b.length(); i++)
			v2.push_back(b[i]);
		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());
		return v1 == v2;
	}
public:
	HashTable(int m)
	{
		size = m;
		out.open("anagrams.txt");
		for(int i = 0; i != size; i++)
			hash_table.push_back(new LinkedList);
	}
	
	void insert_table(std::string data)
	{
		int key = hash_function(data);
		hash_table[key]->insert(data);
	}
	void print_anagrams(std::string data)
	{
		int key =  hash_function(data);
		Node* temp = hash_table[key]->head;
		while(temp != nullptr)
		{
			bool is_anagram = check_anagram(data, temp->data);
			if(is_anagram)
				out << temp->data<<" ";
			temp = temp->next;
		}
		out << std::endl;
	}
};

int main(int argc, char const *argv[])
{
	std::ifstream cin1(argv[1]);
	int size = std::stoi(argv[2]);
	HashTable table(size);
	std::istream_iterator<std::string> itr1(cin1);
	std::istream_iterator<std::string> eos;
	while(itr1 != eos)
		table.insert_table(*(itr1++));

	std::ifstream cin2(argv[3]);
	std::istream_iterator<std::string> itr2(cin2);
	while(itr2 != eos)
		table.print_anagrams(*(itr2++));

	return 0;
}