/* This program demonstrates a decision tree for an animal guessing game. */
 
#include <fstream>
#include <iostream>
#include <string>
#include "binaryTree.h"
 
using namespace std;
 
BinaryTree buildTree();
std::string getResponse(BinaryTree);
 
 
void preOrder(std::ofstream& o, BinaryTree bt)
{
    if (bt.empty())
    {
        return;
    }
   
    o << bt.data() << std::endl;
   
    preOrder(o, bt.left());
   
    preOrder(o, bt.right());
   
}
 
 
 
int main()
{
    /* Build a binary tree called question tree */
    BinaryTree question_tree = buildTree(); //calls
    BinaryTree tree = question_tree;
   
    std::ofstream ofs("animals");
   
    preOrder(ofs, question_tree);
   
    //preOrder(std::cout, question_tree);
   
    bool done = false;
 
 /*
 In this loop we ask the user some questions.
 the user enters either yes or no.
 based on their answer, we decide which way to go next.
 */
    while (!done)
    {
        BinaryTree left = question_tree.left();
        BinaryTree right = question_tree.right();
 
        if (left.empty() && right.empty())
        {
			char yn;
            cout << question_tree.data() << "(Y/N)" << std::endl;
            cin >> yn;
            /*
            this part of the code is the added part.
            it asks the user a final time if they have the desired result.
            then 
            */
            if(yn == 'y')
				done = true;
			else {
				std::string animal, question;
				cout << "Whats the correct animal?" << std::endl;
				cin >> animal;
				cout << "What would the question leading to this answer be?" << std::endl;
				getline(cin, question);
				
				BinaryTree a(animal); //used constructor that makes no child nodes.
				BinaryTree d(question_tree.data());//same thing with current animal
				BinaryTree n(question, a, d);//making question tree with 2 child nodes and the question u want to replace node with
				question_tree = n; // replacing
				done = true; //exit loop
			}
        }
       
        else
        {
            string response = getResponse(question_tree);
           
            if (response == "y"){question_tree = left;}
           
            else {question_tree = right;}        
        }
    }
    ofstream newtree("result");
    preOrder(newtree, question_tree); //equal to the new tree that was built
    
}

/*\includegraphics[scale=0.9]{first}*/
/*
This first image shows the basic binary tree given to us.
*/
/*\includegraphics[scale=0.9]{second}*/
/*
This second image goes one step beyond and asks the user whether the
answer they received was right or wrong. if the answer was right,
the program ends. if the answer was wrong, the program asks the user
to choose the right answer and also the question that would lead up to
that answer.
\newpage
Due to my surgery, I did not have time to finish all of the lab. i had
to first catch up with people and then work on the rest of the lab. If 
i had more time, the next thing i would do is implement a file system
as mentioned in the lab. I would make the program read the text from a
file. Every single time the user wants to enter another answer, he would
add it to the file with the question pretaining to it. 

Sorry i could not complete all of the lab :( What happened was really
unlucky timing.
*/
