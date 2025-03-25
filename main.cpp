#include "avl.h"
#include "filehandler.h"
#include <iostream>
using namespace std;

int main() {
    int choice;
    cout << "Select key for AVL Tree sorting:\n";
    cout << "1. Roll Number\n";
    cout << "2. CGPA\n";
    cout << "Enter choice: ";
    cin >> choice;

    KeyType keyType = (choice == 2) ? CGPA : ROLL_NO;
    AVL tree(keyType);

    // Process the input file
    FileHandler::processFile("input_avl.txt", tree);

    cout << "\nFinal AVL Tree (In-Order Traversal):\n";
    tree.printInOrder();


    return 0;
}
