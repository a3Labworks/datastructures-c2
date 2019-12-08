#pragma once

#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;

// node data structure
struct MyHeapNode {
	int data; // contains the key
	int degree; // number of children 
	MyHeapNode* p; // pointer to parent
	MyHeapNode* child; // pointer to the leftmost child
	MyHeapNode* sibling; // pointer to the right sibling
};

typedef MyHeapNode* MyNodePtr;


// Class that represents Binomial heap data structure
class MyBinomialHeap {
private:
	// head points to the root of the leftmost binomial tree
	MyNodePtr head;

	// initializes  the node with default values
	// all pointers are initialized to nullptr
	void initializeNode(MyNodePtr node, int data, int degree) {
		node->data = data;
		node->degree = degree;
		node->p = nullptr;
		node->child = nullptr;
		node->sibling = nullptr;
	}

	// merge two binomial trees of same degree
	static void linkBinomialTrees(MyNodePtr x, MyNodePtr y) {
		// x must be parent of y
		y->p = x;
		y->sibling = x->child;
		x->child = y;

		// increase the degree of x
		x->degree += 1;
	}

public:
	MyBinomialHeap() {
		head = nullptr;
	}

	// find the node with mininum data
	MyNodePtr findMinimum() {
		// traverse all the roots and find compare
		int min = 999999;
		MyNodePtr currPtr = head;
		MyNodePtr minPtr = nullptr;

		while (currPtr != nullptr) {
			if (currPtr->data < min) {
				min = currPtr->data;
				minPtr = currPtr;
			}
			currPtr = currPtr->sibling;
		}

		return minPtr;

	}

	// create sample heap (given in figure 5) with three trees for testing
	void createSampleHeap1() {
		// B0
		MyNodePtr node1 = new MyHeapNode;
		initializeNode(node1, 5, 0);
		head = node1;

		// B1
		MyNodePtr node2 = new MyHeapNode;
		initializeNode(node2, 17, 1);
		MyNodePtr node3 = new MyHeapNode;
		initializeNode(node3, 27, 0);
		node2->child = node3;
		node3->p = node2;

		// link B0 and B1
		node1->sibling = node2;

		// B3
		MyNodePtr node4 = new MyHeapNode;
		initializeNode(node4, 12, 3);
		MyNodePtr node5 = new MyHeapNode;
		initializeNode(node5, 18, 2);
		MyNodePtr node6 = new MyHeapNode;
		initializeNode(node6, 16, 1);
		MyNodePtr node7 = new MyHeapNode;
		initializeNode(node7, 15, 0);
		MyNodePtr node8 = new MyHeapNode;
		initializeNode(node8, 23, 1);
		MyNodePtr node9 = new MyHeapNode;
		initializeNode(node9, 30, 0);
		MyNodePtr node10 = new MyHeapNode;
		initializeNode(node10, 22, 0);
		MyNodePtr node11 = new MyHeapNode;
		initializeNode(node11, 25, 0);
		node4->child = node5;
		node5->p = node4;
		node6->p = node4;
		node7->p = node4;
		node5->child = node8;
		node5->sibling = node6;
		node6->child = node10;
		node6->sibling = node7;
		node8->p = node5;
		node9->p = node5;
		node10->p = node6;
		node8->child = node11;
		node8->sibling = node9;
		node11->p = node8;

		// link B1 and B3
		node2->sibling = node4;
	}

	// create sample heap (tas binomial B1 dans le laboratoire)
	void createSampleHeap2() {
		// B0
		MyNodePtr node1 = new MyHeapNode;
		initializeNode(node1, 5, 0);
		head = node1;

		// B2
		MyNodePtr node2 = new MyHeapNode;
		initializeNode(node2, 6, 2);
		MyNodePtr node3 = new MyHeapNode;
		initializeNode(node3, 12, 1);
		MyNodePtr node4 = new MyHeapNode;
		initializeNode(node4, 34, 0);
		MyNodePtr node5 = new MyHeapNode;
		initializeNode(node5, 33, 0);
		node2->child = node3;
		node3->p = node2;
		node4->p = node2;
		node3->child = node5;
		node3->sibling = node4;
		node5->p = node3;

		// link B0 and B1
		node1->sibling = node2;

		// B3
		MyNodePtr node6 = new MyHeapNode;
		initializeNode(node6, 1, 3);
		MyNodePtr node7 = new MyHeapNode;
		initializeNode(node7, 2, 2);
		MyNodePtr node8 = new MyHeapNode;
		initializeNode(node8, 12, 1);
		MyNodePtr node9 = new MyHeapNode;
		initializeNode(node9, 6, 0);
		MyNodePtr node10 = new MyHeapNode;
		initializeNode(node10, 4, 1);
		MyNodePtr node11 = new MyHeapNode;
		initializeNode(node11, 13, 0);
		MyNodePtr node12 = new MyHeapNode;
		initializeNode(node12, 18, 0);
		MyNodePtr node13 = new MyHeapNode;
		initializeNode(node13, 7, 0);
		node6->child = node7;
		node7->p = node6;
		node8->p = node6;
		node7->p = node6;
		node7->child = node10;
		node7->sibling = node8;
		node8->child = node12;
		node8->sibling = node9;
		node10->p = node7;
		node11->p = node7;
		node12->p = node8;
		node10->child = node13;
		node10->sibling = node11;
		node13->p = node10;

		// link B1 and B3
		node2->sibling = node6;
	}

	// crete sample heap (tas binomial B2 dans le laboratoire)
	void createSampleHeap3() {
		// B1
		MyNodePtr node1 = new MyHeapNode;
		initializeNode(node1, 29, 1);
		MyNodePtr node2 = new MyHeapNode;
		initializeNode(node2, 33, 0);
		node1->child = node2;
		node2->p = node1;
		head = node1;

		// B2
		MyNodePtr node3 = new MyHeapNode;
		initializeNode(node3, 21, 2);
		MyNodePtr node4 = new MyHeapNode;
		initializeNode(node4, 23, 1);
		MyNodePtr node5 = new MyHeapNode;
		initializeNode(node5, 78, 0);
		MyNodePtr node6 = new MyHeapNode;
		initializeNode(node6, 50, 0);
		node3->child = node4;
		node4->p = node3;
		node5->p = node3;
		node4->child = node6;
		node4->sibling = node5;
		node6->p = node4;

		// link B1 and B2
		node1->sibling = node3;

	}

	// insert a node to the heap
	void insert(int data) {
		// TODO
	}

	// print the binomial heap with all the trees
	void printHeap() {
		MyNodePtr currPtr = head;
		while (currPtr != nullptr) {
			cout << "Tree of order " << currPtr->degree << endl;
			cout << "There are " << pow(2, currPtr->degree) << " nodes in this tree" << endl;
			cout << "The level order traversal is" << endl;
			queue<MyNodePtr> q;
			q.push(currPtr);
			while (!q.empty()) {
				MyNodePtr p = q.front();
				q.pop();
				cout << p->data << " ";

				if (p->child != nullptr) {
					MyNodePtr tempPtr = p->child;
					while (tempPtr != nullptr) {
						q.push(tempPtr);
						tempPtr = tempPtr->sibling;
					}
				}
			}
			currPtr = currPtr->sibling;
			cout << endl << endl;
		}
	}

	// returns the head pointer
	MyNodePtr getHead() {
		return head;
	}

	// setter for head
	void setHead(MyNodePtr head) {
		this->head = head;
	}

	// merge two binomial heaps H and H'
	// resulting heap will be H
	void merge(MyBinomialHeap h1) {
		// TODO
	}

	// deletes the smallest node from the heap
	MyNodePtr deleteMin() {
		MyNodePtr curr = head;
		MyNodePtr prevMin = nullptr;
		// find the root with minimum key
		MyNodePtr minPtr = nullptr;
		MyNodePtr prevPtr = nullptr;
		int min = 999999;

		while (curr != nullptr) {
			if (curr->data <= min) {
				min = curr->data;
				prevMin = prevPtr;
				minPtr = curr;
			}
			prevPtr = curr;
			curr = curr->sibling;
		}

		// delete the node pointed by minPtr
		if (prevMin != nullptr && minPtr->sibling != nullptr) {
			prevMin->sibling = minPtr->sibling;
		}
		else if (prevMin != nullptr && minPtr->sibling == nullptr) {
			prevMin->sibling = nullptr;
		}

		// remove parent reference from all its child
		MyNodePtr childPtr = minPtr->child;
		while (childPtr != nullptr) {
			childPtr->p = nullptr;
			childPtr = childPtr->sibling;
		}

		// reverse the order 
		stack<MyNodePtr> s;
		childPtr = minPtr->child;
		while (childPtr != nullptr) {
			s.push(childPtr);
			childPtr = childPtr->sibling;
		}

		curr = s.top();
		MyNodePtr temp = curr;
		s.pop();

		while (!s.empty()) {
			curr->sibling = s.top();
			s.pop();
			curr = curr->sibling;
		}

		curr->sibling = nullptr;

		MyBinomialHeap h;
		h.setHead(temp);

		// merge 
		merge(h);

		// return the min root
		return minPtr;
	}
};

