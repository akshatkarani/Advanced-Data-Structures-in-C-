#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <cstdlib>

using namespace std;
struct Node
{
	int data;
	Node* left;
	Node* right;
	Node* parent;
};

class binarySearchTree
{   
	int nothing;
	// This is just for fun
	// Please merge this.
	ofstream out;
	Node* root;
	void print_traversal(Node* temp,int num)
	{
		if(temp == nullptr)
			return;
		if(num == 1)
		{
			print_traversal(temp->left,1);
			out<<temp->data<<" ";
			print_traversal(temp->right,1);			
		}
		else if(num == 2)
		{
			out<<temp->data<<" ";
			print_traversal(temp->left,2);
			print_traversal(temp->right,2);
		}
		else if(num == 3)
		{			
			print_traversal(temp->left,3);
			print_traversal(temp->right,3);
			out<<temp->data<<" ";
		}		
	}

	Node* search_tree(Node* temp,int data)
	{
		if(temp == nullptr)
			return temp;
		if(temp->data == data)
			return temp;
		else if(data < temp->data)
			return search_tree(temp->left,data);
		else
			return search_tree(temp->right,data);
	}

	Node* maxima(Node* temp)
	{
		while(temp->right != nullptr)
			temp = temp->right;
		return temp;
	}

	Node* minima(Node* temp)
	{
		while(temp->left != nullptr)
			temp = temp->left;
		return temp;
	}

	void transplant(Node* &root,Node* u,Node* v)
	{
		if(u->parent == nullptr)
			root = v;
		else if(u->parent->left == u)
			u->parent->left = v;
		else
			u->parent->right = v;
		if(v != nullptr)
			v->parent = u->parent;
	}

public:
	binarySearchTree()
	{
		root = nullptr;
		out.open("tempFile.out");
	}

	void in_order()
	{
		if(this->root != nullptr)
			print_traversal(this->root,1);
		out<<endl;
	}
	void pre_order()
	{
		if(this->root != nullptr)
			print_traversal(this->root,2);
		out<<endl;
	}
	void post_order()
	{
		if(this->root != nullptr)
			print_traversal(this->root,3);
		out<<endl;
	}

	void insert(int data)
	{
		Node* temp = new Node;
		temp->data = data;
		if(this->root == nullptr)
		{			
			temp->parent = nullptr;
			temp->left = nullptr;
			temp->right = nullptr;
			this->root = temp;
		}
		else
		{
			Node* x = this->root;
			Node* y = nullptr;
			while(x != nullptr)
			{
				y = x;
				if(data < x->data)
					x = x->left;
				else
					x = x->right;
			}
			temp->parent = y;
			if(data < y->data)
				y->left = temp;
			else
				y->right = temp;
		}		
		out<<data<<" inserted"<<endl;
	}

	void search(int data)
	{
		if(this->root == nullptr)
			out<<data<<" not found"<<endl;
		else
		{
			Node* found = search_tree(this->root,data);
			if(found == nullptr)
				out<<data<<" not found"<<endl;
			else
				out<<data<<" found"<<endl;
		}		
	}

	void minimum()
	{
		if(this->root == nullptr)
			out<<endl;
		else
		{
			Node* min = minima(this->root);
			out<<min->data<<endl;
		}
	}

	void maximum()
	{
		if(this->root == nullptr)
			out<<endl;
		else
		{
			Node* max = maxima(this->root);
			out<<max->data<<endl;
		}
	}

	void successor(int data)
	{
		if(this->root == nullptr)
			out<<data<<" does not exist"<<endl;			
		else	
		{
			Node* temp = search_tree(this->root,data);
			Node* max = maxima(this->root);
			if(max == temp)
				out<<"successor of "<<data<<" does not exist"<<endl;
			else
			{				
				if(temp == nullptr)
					out<<data<<" does not exist"<<endl;
				else
				{
					if(temp->right != nullptr)
						out<<minima(temp->right)->data<<endl;
					else
					{
						Node* y = temp->parent;
						while(y != nullptr && y->right == temp)
						{
							temp = y;
							y = y->parent;
						}
						out<<y->data<<endl;
					}				
				}	
			}			
		}
	}

	void predecessor(int data)
	{
		if(this->root == nullptr)
			out<<data<<" does not exist"<<endl;		
		else
		{
			Node* temp = search_tree(this->root,data);
			Node* min = minima(this->root);
			if(min == temp)
				out<<"predecessor of "<<data<<" does not exist"<<endl;
			else
			{				
				if(temp == nullptr)
					out<<data<<" does not exist"<<endl;
				else
				{
					if(temp->left != nullptr)
						out<<maxima(temp->left)->data<<endl;
					else
					{
						Node* y = temp->parent;
						while(y != nullptr && y->left == temp)
						{
							temp = y;
							y = y->parent;
						}
						out<<y->data<<endl;
					}
				}
			}
		}
	}

	void dele(int data)
	{
		if(this->root == nullptr)
			out<<data<<" does not exist"<<endl;
		else if(search_tree(this->root,data) == nullptr)
			out<<data<<" does not exist"<<endl;
		else
		{
			Node* temp = search_tree(this->root,data);
			if(temp->left == nullptr)
				transplant(this->root,temp,temp->right);
			else if(temp->right == nullptr)
				transplant(this->root,temp,temp->left);
			else
			{
				Node* y = minima(temp->right);
				if(y->parent != temp)
				{
					transplant(this->root,y,y->right);
					y->right = temp->right;
					y->right->parent = y;					
				}
				transplant(this->root,temp,y);
				y->left = temp->left;
				y->left->parent = y;
			}
			out<<data<<" deleted"<<endl;
		}
	}
};

int main(int argc, char const *argv[])
{
	ifstream cin1(argv[1]);
	istream_iterator<string> itr(cin1);
	istream_iterator<string> eos;

	binarySearchTree bst;
	while(itr != eos)
	{
		if(*itr == "insert")
		{
			itr++;
			bst.insert(stoi(*itr));
		}
		else if(*itr == "in-order")
			bst.in_order();
		else if(*itr == "pre-order")
			bst.pre_order();
		else if(*itr == "post-order")
			bst.post_order();
		else if(*itr == "search")
		{
			itr++;
			bst.search(stoi(*itr));
		}
		else if(*itr == "minimum")
			bst.minimum();
		else if(*itr == "maximum")
			bst.maximum();
		else if(*itr == "successor")
		{
			itr++;
			bst.successor(stoi(*itr));
		}
		else if(*itr == "predecessor")
		{
			itr++;
			bst.predecessor(stoi(*itr));
		}
		else if(*itr == "delete")
		{
			itr++;
			bst.dele(stoi(*itr));
		}
		itr++;
	}
	system("awk -f removeSpace tempFile.out");
	return 0;
}