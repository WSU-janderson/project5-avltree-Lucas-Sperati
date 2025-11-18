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

//todo recursion
//Inserts a new key-value pair into the tree. After a successful insert the tree is rebalanced if needed.
//No duplicates. Should return true if insertion was successful and false if not
//Time complexity must be 0(log2 n)
bool AVLTree::insert(const std::string& key, size_t value) {
    //makes a new node with the key and value
    AVLNode* newNode = new AVLNode(key, value);

    //if the key already exists then the function returns false
    if (contains(key) == true) {
        return false;
    }

    //if the root is nullptr then the node is set to the root
    if (root == nullptr) {
        root = newNode;
    }
    else {
        //calls the other insert function for the recursion stuff
        insertPart2(root, newNode);
    }
    return true;//returns true if gotten to this point since the insert would have been successful.
}

void AVLTree::insertPart2(AVLNode* parent, AVLNode* newNode ) {
    while (newNode != nullptr) {
        //if the newNode is less than the parent key then this runs
        //i currently don't know what the fuck I'm doing so im just going off the zybooks code

        //if the new key to insert is less than the parents key
        if (newNode->key < parent->key) {
            //and if the left child is nullptr
            if (parent->left == nullptr) {
                parent->left = newNode;
                parent = nullptr;
                //todo later set the parent of the newNode to the parent (I think)
            }
        }
        else {
            //recursively calls insertPart2 again since the parent is the left child
            insertPart2(parent->left, newNode);
        }
    }
    //right child conditions
    else {
        if (parent->right == nullptr) {
            parent->right = newNode;
            parent = nullptr;
            //todo later set the parent of the newNode to the parent (I think)
        }
        else {
            //recursively calls insertPart2 again since the parent is the right child
            insertPart2(parent->right, newNode);
        }
    }
    //todo update height and balance parent node
}
//code from zybooks
// if (node⇢key < currentNode⇢key) {
//     if (currentNode⇢left is null) {
//         currentNode⇢left = node
//         currentNode = null
//      }
//     else {
//         currentNode = currentNode⇢left
//      }
// }
// else {
//     if (currentNode⇢right is null) {
//         currentNode⇢right = node
//         currentNode = null
//      }
//     else {
//         currentNode = currentNode⇢right
//      }



//todo recursion
//if the key exists remove will delete the key-value pair from the tree. Memory allocated to the node that
//gets removed is released. After removing the key-value pair is rebalanced if necessary. If key gets removed
//then returns true, false otherwise.
//Time complexity must be 0(log2 n)
bool AVLTree::remove(const std::string& key) {

}

//todo recursion
//Returns true if the key is in the tree and false otherwise
//Time complexity must be 0(log2 n)
bool AVLTree::contains(const std::string& key) const {

}

//todo recursion
//if the key is found get will return the value associated with the key. If the key is not found it will
//return std::nullopt. If it is found it will return std::optional<size_t>
//time complexity must be O(log2 n)
std::optional<size_t> AVLTree::get(const std::string& key) const {

}

//todo recursion
//returns the value stored in the node with the current key
//can retrieve value by saying "int idNum = avlTree["James"];
//can also update value associated with key by "avlTree["James"] = 1234;
//does not need to handle missing or invalid keys
//time complexity must be O(log2 n)
std::string& AVLTree::operator[] (const size_t& key) {

}

//todo recursion
//will return a std::vector of size_t containing all the values associated with keys >= lowKey and keys
//<= highKey. For each key found in the given range, there will be one value in the vector. If no matching
//key-value pairs are found the function should return an empty vector.
vector<std::string> AVLTree::findRange(const std::string& lowKey, const std::string& highKey) const {

}

//todo recursion
//returns a vector with all the keys currently in the tree. The length of the vector should be the same
//as the size of the tree
std::vector<std::string> AVLTree::keys() const {

}

//returns how many key-value pairs are in the tree
//time complexity should be O(1)
size_t AVLTree::size() const {

}

//returns height of the AVL tree
//time complexity should be O(1)
size_t AVLTree::getHeight() const {

}

//todo recursion
//copy constructor
AVLTree::AVLTree(const AVLTree& other) {

}

//todo recursion
//assignment operator
//makes deep copy of the other tree
void AVLTree::operator=(const AVLTree& other) {

}

//todo recursion
//deconstructor
//goes through all nodes using a postorder traversal and uses delete to release memory taken in each node
AVLTree::~AVLTree() {

}

//default constructor, sets the root to null and the height to 0 since there is nothing yet
AVLTree::AVLTree() {
    root = nullptr;
    treeHeight = 0;
}

//todo don't forget the friend method again, dumb fuck