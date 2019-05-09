/*
GOAL --> In this lab we are studying the API, implementation and application 
of a binary decision tree. The author gives us all the code needed to build 
the tree and play a guessing game with the computer trying to guess our 
chosen animal from its decision tree. We are enhancing that game by: 
Add new member function to BinaryTree to modify the Node of the object that 
calls it (data, left, and right).
\newpage
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <string>
 
using namespace std;
 
class Node
{
    private:
   
        string data;
        Node* left;
        Node* right;
        friend class BinaryTree;  
 
};
 
/*   A binary tree in which each node has two children.*/
class BinaryTree
{
 
/********************************************************/
 
    public:
   
        /** Constructs an empty tree.   */
        BinaryTree();
       
        /********************************************************/
       
        /** Constructs a tree with one node and no children. */
        BinaryTree(string root_data);   /* @param rootdata the data for the root */
        BinaryTree(string root_data);   /* @param rootdata the data for the root */
       
        /********************************************************/
       
        /* Constructs a binary tree. */
        BinaryTree(string root_data, BinaryTree left, BinaryTree right);
            /* @param rootdata the data for the root
               @param left the left subtree
             @param right the right subtree */
       
        /********************************************************/
       
        /* Returns the height of this tree. */
        int height() const; /** returns the height */
       
        /********************************************************/
       
        /** Checks whether this tree is empty.*/
        bool empty() const; /** @return true if this tree is empty */
   
        /********************************************************/
       
        /** Gets the data at the root of this tree. */
        string data() const;    /** @return the root data */
       
        /********************************************************/
       
        /** Gets the left subtree of this tree. */
        BinaryTree left() const;    /** @return the left child of the root */
 
        /********************************************************/
 
        /** Gets the right subtree of this tree. */
        BinaryTree right() const;   /** @return the right child of the root */
        /*
        void setLeft(std::string l);
        void setRight(std::string r);
        void setData(std::string d);
        */
 
/********************************************************/
 
    private:
   
        /** Returns the height of the subtree whose root is the given node. */
        int height(const Node* n) const;
            /* @param n a node or nullptr
			   @return the height of the subtree, or 0 if n is nullptr */
       
        /********************************************************/
       
        Node* root;
};
 
#endif
