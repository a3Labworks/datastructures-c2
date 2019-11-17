#include <stdio.h>
#include "btree.h"
#include "mybtree.h"
#include "rbtree.h"
#include "myrbtree.h"


void runRBTree()
{
	RBTree tree;

	tree.insert(7);
	tree.insert(6);
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);

	cout << "Inoder Traversal of Created Tree\n";
	tree.inorder();

	cout << "\n\nLevel Order Traversal of Created Tree\n";
	tree.levelOrder();
}

void runMyRBTree()
{
	MyRBTree tree;

	tree.insert(7);
	tree.insert(6);
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);

	cout << "\n\nInoder Traversal of your Tree\n";
	tree.inorder();

	cout << "\n\nLevel Order Traversal of your Tree\n";
	tree.levelOrder();
}

void runBTree(int degree)
{
	BTree t(degree); // A B-Tree with minium degree 2 (or 3)
	t.insert(10);
	t.insert(20);
	t.insert(5);
	t.insert(6);
	t.insert(12);
	t.insert(30);
	t.insert(7);
	t.insert(17);

	BTreePrinter printer;
	cout << "1) The constucted tree is: \n";
	printer.print(t);

	cout << "\nTraversal of the constucted tree is: ";
	t.traverse();

	int k = 6;
	cout << "\nkey " << k << ": ";
	(t.search(k) != NULL) ? cout << "Present" : cout << "Not Present";

	k = 15;
	cout << "\nkey " << k << ": ";
	(t.search(k) != NULL) ? cout << "Present" : cout << "Not Present";
}

void runMyBTree(int degree)
{
	MyBTree t(degree); // A B-Tree with minium degree 2 (or 3)
	t.insert(10);
	t.insert(20);
	t.insert(5);
	t.insert(6);
	t.insert(12);
	t.insert(30);
	t.insert(7);
	t.insert(17);

	MyBTreePrinter printer;
	cout << "\n\n2) Your tree is: \n";
	printer.print(t);

	cout << "\nTraversal of your tree is: ";
	t.traverse();

	int k = 6;
	cout << "\nkey " << k << ": ";
	(t.search(k) != NULL) ? cout << "Present" : cout << "Not Present";

	k = 15;
	cout << "\nkey " << k << ": ";
	(t.search(k) != NULL) ? cout << "Present" : cout << "Not Present";

	cout << "\n";
}

int main(int argc, char* argv[]) {
	runRBTree(); runMyRBTree();	
	runBTree(2); runMyBTree(2);
}


