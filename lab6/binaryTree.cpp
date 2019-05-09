#include <algorithm>
#include "binaryTree.h"
 
using namespace std;
 
BinaryTree::BinaryTree()
{
    root = nullptr;
}
 
BinaryTree::BinaryTree(string root_data)
{
    root = new Node;
    root->data = root_data;
    root->left = nullptr;
    root->right = nullptr;
}
 
BinaryTree::BinaryTree(string root_data, BinaryTree left, BinaryTree right)
{
    root = new Node;
    root->data = root_data;
    root->left = left.root;
    root->right = right.root;
}
 
int BinaryTree::height(const Node* n) const
{
    if (n == nullptr) { return 0; }
    else { return 1 + max(height(n->left), height(n->right)); }
}
 
int BinaryTree::height() const
{
    return height(root);
}
 
bool BinaryTree::empty() const
{
    return root == nullptr;
}
 
string BinaryTree::data() const
{
    return root->data;
}
 
BinaryTree BinaryTree::left() const
{
    BinaryTree result;
    result.root = root->left;
    return result;
}
 
BinaryTree BinaryTree::right() const
{
    BinaryTree result;
    result.root = root->right;
    return result;
}
/*
void BinaryTree::setLeft(std::string l)
{
	root->left = new BinaryTree(l);
}

void BinaryTree::setRight(string r)
{
	root->right = new BinaryTree(r);
}

void BinaryTree::setData(std::string d)
{
	root->data = d;
}*/
