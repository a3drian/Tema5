/*
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Data structure to store a Binary Tree node
struct Node
{
	int key;
	struct Node *left, *right;
};

// Function to create a new binary tree node having given key
struct Node* newNode(int key)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->left = node->right = NULL;

	return node;
}

// Recursive function to perform inorder traversal of a binary tree
void inorder(struct Node* root)
{
	if (root == NULL)
		return;

	inorder(root->left);
	printf("%c ", root->key);
	inorder(root->right);
}

// Recursive function to build a BST from a preorder sequence
struct Node* constructBST(int preorder[], int start, int end)
{
	// base case
	if (start > end)
		return NULL;

	// Construct the root node of the sub-tree formed by keys of the
	// preorder sequence in range [start, end]
	struct Node *node = newNode(preorder[start]);

	// search the index of first element in current range of preorder
	// sequence which is larger than the value of root node
	int i;
	for (i = start; i <= end; i++) {
		if (preorder[i] > node->key)
			break;
	}

	// recursively construct the left sub-tree
	node->left = constructBST(preorder, start + 1, i - 1);

	// recursively construct the right sub-tree
	node->right = constructBST(preorder, i, end);

	// return current node
	return node;
}

// main function
int main(void)
{
	// Construct below BST
	//		  15
	//		/    \
	//	   /      \
	//	  10       20
	//	 /  \     /  \
	//	/    \   /    \
	//   8     12 16    25
	//

	int preorder[] = { 65, 66, 67, 68, 69, 70, 71 };
	int n = sizeof(preorder) / sizeof(preorder[0]);

	// construct the BST
	struct Node* root = constructBST(preorder, 0, n - 1);

	// print the BST
	printf("Inorder Traversal of BST is : ");

	// inorder on the BST always returns a sorted sequence
	inorder(root);

	std::cout << "\n";

	system("pause");
	return 0;
}
*/

/*
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Data structure to store a Binary Tree node
struct Node {
	int data;
	Node *left, *right;
};

// Function to create a new binary tree node having given key
Node* newNode(int key)
{
	Node* node = new Node;
	node->data = key;
	node->left = node->right = nullptr;

	return node;
}

// Function to print the inorder traversal of a binary tree
void inorder(Node* root)
{
	if (root == nullptr)
		return;

	inorder(root->left);
	char a = root->data;
	cout << a << ' ';
	inorder(root->right);
}

// Recursive function to build a BST from a preorder sequence
Node* buildTree(vector<int> const &preorder, int& pIndex,
	int min, int max)
{
	// Base case
	if (pIndex == preorder.size())
		return nullptr;

	// Return if next element of preorder traversal is not in the valid range
	int val = preorder[pIndex];
	if (val < min || val > max)
		return nullptr;

	// Construct the root node and increment pIndex
	Node* root = newNode(val);
	pIndex++;

	// Since all elements in the left sub-tree of a BST must be less
	// than the value of root node, set range as [min, val-1] and recur
	root->left = buildTree(preorder, pIndex, min, val - 1);

	// Since all elements in the right sub-tree of a BST must be greater
	// than the value of root node, set range as [val+1..max] and recur
	root->right = buildTree(preorder, pIndex, val + 1, max);

	return root;
}

// Build a BST from a preorder sequence
Node* buildTree(vector<int> const &preorder)
{
	// start from the root node (first element in preorder sequence)
	int pIndex = 0;

	// set range of the root node as [INT_MIN, INT_MAX] and recur
	return buildTree(preorder, pIndex, INT_MIN, INT_MAX);
}

// main function
int main()
{
	// Construct below BST
	//		  15
	//		/    \
	//	   /      \
	//	  10       20
	//	 /  \     /  \
	//	/    \   /    \
	//   8     12 16    25
	//

	// preorder traversal of BST
	//vector<int> preorder = { 65, 66, 67, 68, 69, 70, 71 };
	vector<char> preorder = { 'a', 'b', 'c', 'd', 'e', 'f' };

	// construct the BST
	Node* root = buildTree(preorder);

	// print the BST
	cout << "Inorder Traversal of BST is : ";

	// inorder on the BST always returns a sorted sequence
	inorder(root);

	cout << "\n";

	system("pause");
	return 0;
}
*/

#include <iostream>
#include <queue>

class Nod {
public:

	char info;
	Nod * left;
	Nod * right;
	Nod * parent;

	Nod(char key = 0) {
		this->info = key;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
};

class Arbore {
public:
	Nod * root;

	Arbore() {
		this->root = nullptr;
	}

	//Print
	void print(unsigned short option) const {
		switch (option) {
			case 1: //preordine
				{
					std::cout << "Preordine: ";
					preordine(this->root);
					std::cout << "\n";
					break;
				}
			case 2: //inordine
				{
					std::cout << "Inordine: ";
					inordine(this->root);
					std::cout << "\n";
					break;
				}
			case 3: //postordine
				{
					std::cout << "Postordine: ";
					postordine(this->root);
					std::cout << "\n";
					break;
				}
			case 4: //printare pe nivel
				{
					printLevelByLevel(this->root);
					std::cout << "\n";
					break;
				}
		}
	}

	void preordine(Nod*) const{
		if (root == nullptr) {
			return;
		}

		std::cout << root->info << " ";
		preordine(root->left);
		preordine(root->right);
	}
	void inordine(Nod*) const{
		if (root == nullptr) {
			return;
		}

		inordine(root->left);
		std::cout << root->info << " ";
		inordine(root->right);
	}
	void postordine(Nod*) const{
		if (root == nullptr) {
			return;
		}
		postordine(root->left);
		postordine(root->right);
		std::cout << root->info << " ";
	}
	void printLevelByLevel(Nod*) const{
		std::queue<Nod *> q;

		// add root to the queue
		q.push(root);

		// add null as marker
		q.push(nullptr);

		while (!q.empty()) {

			Nod * n = q.front();

			q.pop();
			// check if n is null, if yes, we have reached to the end of the
			// current level, increment the height by 1, and add the another
			// null as marker for next level
			if (n == nullptr) {
				// before adding null, check if queue is empty, which means we
				// have traveled all the levels
				if (!q.empty()) {
					q.push(nullptr);
				}
			} else {
				std::cout << n->info << " ";
				// else add the children of extracted node.
				if (n->left != nullptr) {
					q.push(n->left);
				}
				if (n->right != nullptr) {
					q.push(n->right);
				}
			}
		}
	}
};

#include <iostream>
#include <vector>

int main() {

	int n;
	n = 7;

	std::vector<Nod *> noduri = std::vector<Nod *>(n);

	for (int i = 0; i < n; i++) {
		Nod * leaf = new Nod(65 + i);
		noduri[i] = leaf;
	}

	Arbore a = Arbore();

	a.root = noduri[0];
	a.root->left = noduri[1];
	a.root->left->left = noduri[2];

	a.root->right = noduri[3];
	a.root->right->right = noduri[4];
	a.root->right->right->right = noduri[5];
	a.root->right->right->right->right = noduri[6];

	a.inordine(a.root);

	//a.print(1); //preordine
	//a.print(2); //inordine
	//a.print(3); //postordine		
	//a.print(4); //level-order

	std::cout << "\n";

	system("pause");
	return 0;
}