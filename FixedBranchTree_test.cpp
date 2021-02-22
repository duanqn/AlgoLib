#include "FixedBranchTree.hpp"

int main(){
    AlgoLib::DataStructure::BinaryTree<int> binaryTree;
    binaryTree.setRoot(0);
    auto root = binaryTree.getRoot();
    binaryTree.insert(1, root);
    return 0;
}