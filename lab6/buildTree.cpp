#include "binaryTree.h"
 
/* Is there a more efficient way to return this tree?
So we don't have to return it by value? By reference
not good since it is a local variable.
*/
 
BinaryTree buildTree()
{
    BinaryTree question_tree(
        BinaryTree("Is it a mammal?",
            BinaryTree("Does it have stripes?",
                BinaryTree("Is it a carnivore?",
                    BinaryTree("It is a tiger."),
                    BinaryTree("It is a zebra.")),
                BinaryTree("It is a pig.")),
            BinaryTree("Does it fly?",
                BinaryTree("It is an eagle."),
                BinaryTree("Does it swim?",
                    BinaryTree("It is a penguin."),
                    BinaryTree("It is an ostrich.")))));
    return question_tree;
}
