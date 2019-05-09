#include <iostream>
#include <string>
#include "binaryTree.h"
 
std::string getResponse(BinaryTree t)
{
    std::string r;
    do
    {
        cout << t.data() << " (y/n): ";
        cin >> r;
    } while (r != "y" && r != "n");
    return r;
}
