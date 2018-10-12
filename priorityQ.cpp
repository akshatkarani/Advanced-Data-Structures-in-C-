/*  ----- README -----
The awk file named removeSpaces.awk is to remove 
the last space when printing the sorted elements after input read is "sort".
No need to run the awk file manually. 
'main.cpp' will run it as long as awk is installed on the system.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstdlib>

class priorityQueue
{
	typedef std::vector<int>::size_type index;
	std::vector<int> heap;
	index heap_size;

	index parent(index i)
	{
		return (i-1)/2;
	}
	index left_child(index i)
	{
		return 2*i+1;
	}
	index right_child(index i)
	{
		return 2*i+2;
	}
	void max_heapify(index i, std::vector<int>& h, index size)
	{
		index left = left_child(i);
		index right = right_child(i);
		index largest;
		if(left < size && h[i] < h[left])
			largest = left;
		else
			largest = i;
		if(right < size && h[largest] < h[right])
			largest = right;
		if(largest != i)
		{
			int temp = h[largest];
			h[largest] = h [i];
			h[i] = temp;
			max_heapify(largest,h,size);
		}
	}
	void increase_key(index i,int num)
	{
		heap[i] = num;
		while(i > 0 && heap[i] > heap[parent(i)])
		{
			int temp = heap[i];
			heap[i] = heap[parent(i)];
			i = parent(i);
			heap[i] = temp;
		}
	}
	std::ofstream out;
public:
	priorityQueue()
	{
		heap_size = 0;
		out.open("tempFile.out");
	}
	void maxima()
	{
		if(heap_size == 0)
			out<<std::endl;
		else
			out<<heap[0]<<std::endl;
	}
	void extract_max()
	{
		if(heap_size == 0)
			out<<std::endl;
		else
		{
			out<<heap[0]<<std::endl;
			heap[0] = heap[heap_size-1];
			heap_size--;
			heap.pop_back();			
			max_heapify(0, heap, heap_size);			
		}
	}
	void insert(int num)
	{
		heap_size ++;
		heap.push_back(num);
		increase_key(heap_size-1,num);
		out<<num<<" inserted"<<std::endl;
	}
	void print_increase(index i,int num)
	{
		if(num < heap[i])
			out<<num<<" is less than the current key at "<<i<<std::endl;
		else
		{
			increase_key(i,num);
			out<<"Key at "<<i<<" changed to "<<num<<std::endl;
		}
	}
	void heap_sort()
	{
		index length = heap_size;  
		if(length != 0)
		{
			std::vector<int> v = heap;
			while(length > 0)
			{
				length--;
				int temp = v[0];
				v[0] = v[length];
				v[length] = temp;
				max_heapify(0, v, length);
			}
			for(auto i = v.begin(); i != v.end(); i++)
				out<<*i<<" ";	
		}
		out<<std::endl;
	}
};

int main(int argc, char const *argv[])
{
	std::ifstream cin1(argv[1]);
	std::istream_iterator<std::string> itr(cin1);
	std::istream_iterator<std::string> eos;
	priorityQueue q;
	while(itr != eos)
	{
		if(*itr == "insert")
		{
			itr++;
			q.insert(stoi(*itr));
		}
		else if(*itr == "maximum")
			q.maxima();
		else if(*itr == "extract-max")
			q.extract_max();
		else if(*itr == "increase-key")
		{
			itr++;
			int i = stoi(*itr);
			itr++;
			q.print_increase(i,stoi(*itr));
		}
		else if(*itr == "sort")
		{
			q.heap_sort();
		}
		itr++;
	}
	system("awk -f removeSpace tempFile.out");
	return 0;
}