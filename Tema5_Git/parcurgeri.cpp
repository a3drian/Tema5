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
	/* Construct below BST
			  15
			/    \
		   /      \
		  10       20
		 /  \     /  \
		/    \   /    \
	   8     12 16    25
	*/

	// preorder traversal of BST
	vector<int> preorder = { 65, 66, 67, 68, 69, 70, 71 };

	// construct the BST
	Node* root = buildTree(preorder);

	// print the BST
	cout << "Inorder Traversal of BST is : ";

	// inorder on the BST always returns a sorted sequence
	inorder(root);

	system("pause");
	return 0;
}