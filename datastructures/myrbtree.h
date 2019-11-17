/** C++ implementation for Red-Black Tree Insertion**/
#include <cstddef>
#include <iostream>
#include <queue>
using namespace std;

enum MyColor { MyRED, MyBLACK };

struct MyNode
{
	int data;
	bool color;
	MyNode* left, * right, * parent;

	// Constructor 
	MyNode(int data)
	{
		this->data = data;
		left = right = parent = NULL;
		this->color = MyRED;
	}
};

// Class to represent Red-Black Tree 
class MyRBTree
{
private:
	MyNode* root;
protected:
	void rotateLeft(MyNode*&, MyNode*&);
	void rotateRight(MyNode*&, MyNode*&);
	void fixViolation(MyNode*&, MyNode*&);
public:
	// Constructor 
	MyRBTree() { root = NULL; }
	void insert(const int& n);
	void inorder();
	void levelOrder();
};

// A recursive function to do level order traversal 
void inorderHelper(MyNode* root)
{
	if (root == NULL)
		return;

	inorderHelper(root->left);
	cout << root->data << " ";
	inorderHelper(root->right);
}

/* A utility function to insert a new node with given key in BST */
MyNode* BSTInsert(MyNode* root, MyNode* pt)
{
	/* If the tree is empty, return a new node */
	if (root == NULL)
		return pt;

	/* Otherwise, recur down the tree */
	if (pt->data < root->data)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->data > root->data)
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}

	/* return the (unchanged) node pointer */
	return root;
}

// Utility function to do level order traversal 
void levelOrderHelper(MyNode* root)
{
	if (root == NULL)
		return;

	std::queue<MyNode*> q;
	q.push(root);

	while (!q.empty())
	{
		MyNode* temp = q.front();
		cout << temp->data << " ";
		q.pop();

		if (temp->left != NULL)
			q.push(temp->left);

		if (temp->right != NULL)
			q.push(temp->right);
	}
}

void MyRBTree::rotateLeft(MyNode*& root, MyNode*& pt)
{
	MyNode* pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void MyRBTree::rotateRight(MyNode*& root, MyNode*& pt)
{
	MyNode* pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

// This function fixes violations caused by BST insertion 
void MyRBTree::fixViolation(MyNode*& root, MyNode*& pt)
{
	MyNode* parent_pt = NULL;
	MyNode* grand_parent_pt = NULL;

	// TODO: insérez le code correct, laissez le reste tel quel

	root->color = MyBLACK;
}

// Function to insert a new node with given data 
void MyRBTree::insert(const int& data)
{
	MyNode* pt = new MyNode(data);

	// Do a normal BST insert 
	root = BSTInsert(root, pt);

	// fix Red Black Tree violations 
	fixViolation(root, pt);
}

// Function to do inorder and level order traversals 
void MyRBTree::inorder() { inorderHelper(root); }
void MyRBTree::levelOrder() { levelOrderHelper(root); }


