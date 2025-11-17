#include "AVLTree.h"

#include <optional>
#include <string>
#include <vector>

size_t AVLTree::AVLNode::numChildren() const {
    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}

bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}

//---------------------------------------------------------------

//Inserts a new key-value pair into the tree. After a successful insert the tree is rebalanced if needed.
//No duplicates. Should return true if insertion was successful and false if not
//Time complexity must be 0(log2 n)
bool AVLTree::insert(const std::string& key, size_t value){

}

//if the key exists remove will delete the key-value pair from the tree. Memory allocated to the node that
//gets removed is released. After removing the key-value pair is rebalanced if necessary. If key gets removed
//then returns true, false otherwise.
//Time complexity must be 0(log2 n)
bool AVLTree::remove(const std::string& key) {

}

//Returns true if the key is in the tree and false otherwise
//Time complexity must be 0(log2 n)
bool AVLTree::contains(const std::string& key) const {

}

//if the key is found get will return the value associated with the key. If the key is not found it will
//return std::nullopt. If it is found it will return std::optional<size_t>
//time complexity must be O(log2 n)
std::optional<size_t> AVLTree::get(const std::string& key) const {

}

//returns the value stored in the node with the current key
//can retrieve value by saying "int idNum = avlTree["James"];
//can also update value associated with key by "avlTree["James"] = 1234;
//does not need to handle missing or invalid keys
//time complexity must be O(log2 n)
std::string& AVLTree::operator[] (const size_t& key) {

}

//will return a std::vector of size_t containing all the values associated with keys >= lowKey and keys
//<= highKey. For each key found in the given range, there will be one value in the vector. If no matching
//key-value pairs are found the function should return an empty vector.
vector<std::string> AVLTree::findRange(const std::string& lowKey, const std::string& highKey) const {

}

//returns a vector with all the keys currently in the tree. The length of the vector should be the same
//as the size of the tree
std::vector<std::string> AVLTree::keys() const {

}

//returns how many key-value pairs are in the tree
//time complexity should be O(1)
size_t AVLTree::size() const {

}

