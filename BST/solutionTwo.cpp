#include <float.h>
#include <cmath>
#include <iostream>

using namespace std;

class BST {
    public:
    int value;
    BST* left;
    BST* right;
    //long constructor
    BST(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }

    //берем объект по ссылке для изменения оригинала экземпляра класса
    BST& insert(int val) {
        if(val <= value) {
            if(left == nullptr){
                left = new BST(val);
            }
            else
            { 
                left->insert(val);
                
            }
            
        }
        if(val >= value) {
            if(right == nullptr) {
                right = new BST(val);
            }
            else
            right->insert(val);
        }
        //возвращаем указатель адреса в памяти, потому что нужно уметь указывать на пустоту
        return *this;


    }
    void printInOrder() {
        if(left != nullptr)
        left->printInOrder();

        cout<<value<<" ";
        
        if(right != nullptr)
        right->printInOrder();
        else cout<<" "<<endl;

    }

    //short constructor
    //BST(int val) : value(val), left(nullptr), right(nullptr)
};
int findClosestValueInBST(BST* tree, int target);
int findClosestValueInBSTHelper(BST* tree, int target, int closest);



int findClosestValueInBST(BST* tree, int target) {
    return findClosestValueInBSTHelper(tree, target, tree->value);
}

int findClosestValueInBSTHelper(BST* tree, int target, int closest) {
    
    BST* currentNode = tree;
    while(currentNode != nullptr) {
        if(tree == nullptr) return closest;
        if(abs(target - currentNode->value) < abs(target - closest) )
        closest = currentNode->value;
        if(target < currentNode->value) {
            currentNode = currentNode->left;
        }
        else if(target > currentNode->value) {
            currentNode = currentNode->right;
        }
        else break;
    }
    return (int)closest;
}

int main() {
    BST* tree = new BST(0);
    tree->insert(10).insert(20).insert(9).insert(40).insert(-1);
    tree->printInOrder();
    int target = -3;
    cout<<" "<<endl;
    cout<<"The target number is: "<<target<<endl;
    cout<<"The closest value is "<<findClosestValueInBST(tree, target)<<endl;
    delete tree;//do not forget to deallocate memory
    return 0;
}