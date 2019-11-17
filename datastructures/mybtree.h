#pragma once

#include<iostream> 
#include <vector>
#include <sstream>

using namespace std;

// A BTree node 
class MyBTreeNode
{
public:
	int* keys; // An array of keys 
	int t;	 // Minimum degree (defines the range for number of keys) 
	MyBTreeNode** C; // An array of child pointers 
	int n;	 // Current number of keys 
	bool leaf; // Is true when node is leaf. Otherwise false 

	MyBTreeNode(int _t, bool _leaf); // Constructor 

	// A utility function to insert a new key in the subtree rooted with 
	// this node. The assumption is, the node must be non-full when this 
	// function is called 
	void insertNonFull(int k);

	// A utility function to split the child y of this node. i is index of y in 
	// child array C[]. The Child y must be full when this function is called 
	void splitChild(int i, MyBTreeNode* y);

	// A function to traverse all nodes in a subtree rooted with this node 
	void traverse();

	// A function to search a key in the subtree rooted with this node. 
	MyBTreeNode* search(int k); // returns NULL if k is not present. 

	friend class MyBTree;
};

// A BTree 
class MyBTree
{
	int t; // Minimum degree 
public:
	MyBTreeNode* root; // Pointer to root node 

	// Constructor (Initializes tree as empty) 
	MyBTree(int _t)
	{
		root = NULL; t = _t;
	}

	// function to traverse the tree 
	void traverse()
	{
		if (root != NULL) root->traverse();
	}

	// function to search a key in this tree 
	MyBTreeNode* search(int k)
	{
		return (root == NULL) ? NULL : root->search(k);
	}

	// The main function that inserts a new key in this B-Tree 
	void insert(int k);
};

// Constructor for BTreeNode class 
MyBTreeNode::MyBTreeNode(int t1, bool leaf1)
{
	// Copy the given minimum degree and leaf property 
	t = t1;
	leaf = leaf1;

	// Allocate memory for maximum number of possible keys 
	// and child pointers 
	keys = new int[2 * t - 1];
	C = new MyBTreeNode * [2 * t];

	// Initialize the number of keys as 0 
	n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node 
void MyBTreeNode::traverse()
{
	// There are n keys and n+1 children, traverse through n keys 
	// and first n children 
	int i;
	for (i = 0; i < n; i++)
	{
		// If this is not leaf, then before printing key[i], 
		// traverse the subtree rooted with child C[i]. 
		if (leaf == false)
			C[i]->traverse();
		cout << " " << keys[i];
	}

	// Print the subtree rooted with last child 
	if (leaf == false)
		C[i]->traverse();
}

// Function to search key k in subtree rooted with this node 
MyBTreeNode* MyBTreeNode::search(int k)
{
	// TODO
	return NULL;
}

// The main function that inserts a new key in this B-Tree 
void MyBTree::insert(int k)
{
	//TODO: remplacez-le par le code correct
	if (root == NULL)
	{
		root = new MyBTreeNode(t, true);
	}
}

// A utility function to insert a new key in this node 
// The assumption is, the node must be non-full when this 
// function is called 
void MyBTreeNode::insertNonFull(int k)
{
	// Initialize index as index of rightmost element 
	int i = n - 1;

	// If this is a leaf node 
	if (leaf == true)
	{
		// The following loop does two things 
		// a) Finds the location of new key to be inserted 
		// b) Moves all greater keys to one place ahead 
		while (i >= 0 && keys[i] > k)
		{
			keys[i + 1] = keys[i];
			i--;
		}

		// Insert the new key at found location 
		keys[i + 1] = k;
		n = n + 1;
	}
	else // If this node is not leaf 
	{
		// Find the child which is going to have the new key 
		while (i >= 0 && keys[i] > k)
			i--;

		// See if the found child is full 
		if (C[i + 1]->n == 2 * t - 1)
		{
			// If the child is full, then split it 
			splitChild(i + 1, C[i + 1]);

			// After split, the middle key of C[i] goes up and 
			// C[i] is splitted into two. See which of the two 
			// is going to have the new key 
			if (keys[i + 1] < k)
				i++;
		}
		C[i + 1]->insertNonFull(k);
	}
}

// A utility function to split the child y of this node 
// Note that y must be full when this function is called 
void MyBTreeNode::splitChild(int i, MyBTreeNode* y)
{
	// Create a new node which is going to store (t-1) keys 
	// of y 
	MyBTreeNode* z = new MyBTreeNode(y->t, y->leaf);
	z->n = t - 1;

	// Copy the last (t-1) keys of y to z 
	for (int j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j + t];

	// Copy the last t children of y to z 
	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
			z->C[j] = y->C[j + t];
	}

	// Reduce the number of keys in y 
	y->n = t - 1;

	// Since this node is going to have a new child, 
	// create space of new child 
	for (int j = n; j >= i + 1; j--)
		C[j + 1] = C[j];

	// Link the new child to this node 
	C[i + 1] = z;

	// A key of y will move to this node. Find the location of 
	// new key and move all greater keys one space ahead 
	for (int j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	// Copy the middle key of y to this node 
	keys[i] = y->keys[t - 1];

	// Increment count of keys in this node 
	n = n + 1;
}

/**
	Helper class to print a B-Tree
**/
class MyBTreePrinter
{
	struct NodeInfo
	{
		std::string text;
		unsigned text_pos, text_end;  // half-open range
	};

	typedef std::vector<NodeInfo> LevelInfo;

	std::vector<LevelInfo> levels;

	std::string node_text(int const keys[], unsigned key_count);

	void before_traversal()
	{
		levels.resize(0);
		levels.reserve(10);   // far beyond anything that could usefully be printed
	}

	void visit(MyBTreeNode const* node, unsigned level = 0, unsigned child_index = 0);

	void after_traversal();

public:
	void print(MyBTree const& tree)
	{
		before_traversal();
		visit(tree.root);
		after_traversal();
	}

	friend class MyBTree;
};

void MyBTreePrinter::visit(MyBTreeNode const* node, unsigned level, unsigned child_index)
{
	if (level >= levels.size())
		levels.resize(level + 1);

	LevelInfo& level_info = levels[level];
	NodeInfo info;

	info.text_pos = 0;
	if (!level_info.empty())  // one blank between nodes, one extra blank if left-most child
		info.text_pos = level_info.back().text_end + (child_index == 0 ? 2 : 1);

	info.text = node_text(node->keys, unsigned(node->n));

	if (node->leaf)
	{
		info.text_end = info.text_pos + unsigned(info.text.length());
	}
	else // non-leaf -> do all children so that .text_end for the right-most child becomes known
	{
		for (unsigned i = 0, e = unsigned(node->n); i <= e; ++i)  // one more pointer than there are keys
			visit(node->C[i], level + 1, i);

		info.text_end = levels[level + 1].back().text_end;
	}

	levels[level].push_back(info);
}

std::string MyBTreePrinter::node_text(int const keys[], unsigned key_count)
{
	std::ostringstream os;
	char const* sep = "";

	os << "[";
	for (unsigned i = 0; i < key_count; ++i, sep = " ")
		os << sep << keys[i];
	os << "]";

	return os.str();
}

void MyBTreePrinter::after_traversal()
{
	for (std::size_t l = 0, level_count = levels.size(); ; )
	{
		auto const& level = levels[l];
		unsigned prev_end = 0;

		for (auto const& node : level)
		{
			unsigned total = node.text_end - node.text_pos;
			unsigned slack = total - unsigned(node.text.length());
			unsigned blanks_before = node.text_pos - prev_end;

			print_blanks(blanks_before + slack / 2);
			std::cout << node.text;

			if (&node == &level.back())
				break;

			print_blanks(slack - slack / 2);

			prev_end += blanks_before + total;
		}

		if (++l == level_count)
			break;

		std::cout << "\n\n";
	}

	std::cout << "\n";
}





