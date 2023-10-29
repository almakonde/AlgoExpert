#include <cmath>
#include<float.h>
#include<iostream>
class BST {
    public:
    int value;
    BST* left;
    BST* right;
    BST(int val): value(val), left(nullptr), right(nullptr) {}
    BST& insert(int val){
        if(val <= value) {
            if(left == nullptr) {
                left = new BST(val);
            }
            else
            left->insert(val);
        
        }
        if(val >= value) {
            if(right == nullptr) {
                right = new BST(val);
            }
            else
            right->insert(val);
        }
        return *this;

    }
};
int findClosestValueInBST(BST* tree, int target);
int findClosestValueInBSTHelper(BST* tree, int target, int closest);

int findClosestValueInBST(BST* tree, int target) {

    return findClosestValueInBSTHelper(tree, target, tree->value);
}
int findClosestValueInBSTHelper(BST* tree, int target, int closest) {
    if(abs(target - closest) > abs(target - tree->value))
    closest = tree->value;
    //recursive left search in tree
    if(target < tree->value && tree->left != nullptr) {
        return findClosestValueInBSTHelper(tree->left, target, closest);
    }
    //recursive right search in tree
    if(target > tree->value && tree->right != nullptr) {
        return findClosestValueInBSTHelper(tree->right, target, closest);
    }
    else
    return closest;
}
int main() {
    BST* tree = new BST(100);
    tree->insert(5);
    tree->insert(15);
    tree->insert(-18);
    tree->insert(5-2);
    tree->insert(10);
    tree->insert(2);
    tree->insert(7);

    int target = 0;

    int closestValue = findClosestValueInBST(tree, target);
    std::cout<<target<<std::endl;
    std::cout<<closestValue<<std::endl;


    delete tree;
    return 0;



    
}


