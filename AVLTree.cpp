//AVLTree.cpp
//Project 5
//CS 3100
//Lucas Sperati
//This file implements all the methods that are used for the avlTree



#include "AVLTree.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

//function to check the number of children in the node. If the left and right are not null then children increases
//by one
size_t AVLTree::AVLNode::numChildren() const {
    size_t children = 0;
    if (left != nullptr) {
        children = children + 1;
    }
    else if (right != nullptr) {
        children = children + 1;
    }
    return children;
}
//for the node to be a leaf the left and right need to be null
//checks if lef and right are null. True if the are false otherwise
bool AVLTree::AVLNode::isLeaf() const {
    if (left == nullptr && right == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

//made this return height instead of 0
size_t AVLTree::AVLNode::getHeight() const {
    return height;
}

//function given to us to delete the node
bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren(); //idk what this does
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
//helper remove method
bool AVLTree::remove(AVLNode *&current, KeyType key) {
    //if the current node is nullptr then it returns false since the key doesn't exist
    if (current == nullptr) {
        return false;
    }
    //if the key to be removed is less than the current key
    if (key < current->key) {
        //makes the current key the left child and calls recursively
        return remove(current->left, key);
    }
    //if the key to be removed is greater than the current key
    if (key > current->key) {
        //makes the current key the right child and calls recursively
        return remove(current->right, key);
    }
    else {
        //since the key would be found then it calls the removeNode method that was made for us
        return removeNode(current);
    }

}
//method to balance the node
//pretty much copied the chapter 11 zybooks example
void AVLTree::balanceNode(AVLNode *&node) {
    //first updates the height of the tree
    updateTreeHeight(node);
    if (treeBalance(node) == -2) {
        if (treeBalance(node) == 1) {
            //this is apparently the double rotation case according to the zybooks
            rotateRight(node->right);
        }
        roatateLeft(node); //single rotation case
    }

         if (treeBalance(node) == 2) {
            if (treeBalance(node->left) == -1) {
                //double rotation case.
                roatateLeft(node->left);
            }
             rotateRight(node); //single rotation case
        }
    }

//this function rotates the node on the tree to the right. Used zybooks example
bool AVLTree::rotateRight(AVLNode *&messedUpEvilNode) {
    //if the node does not exist it returns false
    if (messedUpEvilNode == nullptr) {
        return false;
    }
    //if the node does not have a left child then it also returns false since you need a left node to rotate right
    if (messedUpEvilNode->left == nullptr) {
        return false;
    }
    //node to get the left-right of the node
    AVLNode* leftRightChild = messedUpEvilNode->left->right;

    //ff node has a parent then replaces that node with its left child
    if (messedUpEvilNode->parent != nullptr) {
        AVLTreeReplaceChild(messedUpEvilNode->parent, messedUpEvilNode, messedUpEvilNode->left);
    }
    else {  //node is not root
        root = messedUpEvilNode->left;
        root-> parent = nullptr;
    }
    //set left child right child to node for rotation
    AVLTreeSetChild(messedUpEvilNode->left, "right", messedUpEvilNode);
    //set node left child to leftRightChild
    AVLTreeSetChild(messedUpEvilNode, "left", leftRightChild);
    //updates the height
    updateTreeHeight(messedUpEvilNode);
    //updates height again since the parent of the messedUpEvilNode is the root
    updateTreeHeight(messedUpEvilNode->parent);
    //returns true when successful
    return true;
}
//this function rotates the node on the tree to the left
bool AVLTree::roatateLeft(AVLNode *&messedUpEvilNode) {
    //if the node does not exist it returns false
    if (messedUpEvilNode == nullptr) {
        return false;
    }
    //if the node does not have a right child then it also returns false since you need a right node to rotate left
    if (messedUpEvilNode->right == nullptr) {
        return false;
    }

    AVLNode* rightChild = messedUpEvilNode->right;
    AVLNode* rightLeft = rightChild->left;

    //if node has a parent replaces node with its right child
    if (messedUpEvilNode->parent != nullptr) {
        AVLTreeReplaceChild(messedUpEvilNode->parent, messedUpEvilNode, rightChild);
    }
    else {
        //node is root
        root = rightChild;
        root-> parent = nullptr;
    }
    //set right child left child to messedUpEvilNode
    AVLTreeSetChild(rightChild, "left", messedUpEvilNode);
    //set right child to rightLeftChild
    AVLTreeSetChild(messedUpEvilNode, "right", rightLeft);
    //update heights
    updateTreeHeight(messedUpEvilNode);
    updateTreeHeight(rightChild);  // new subtree root after rotation
    //reutrn true once done
    return true;
}
//this function sets the left and right child based on the parameter used with rotation. Taken from zybooks
bool AVLTree::AVLTreeSetChild(AVLNode *parent, const std::string &leftOrRight ,AVLNode *child) {
    if (leftOrRight != "left" && leftOrRight != "right") {
        return false;
    }
    if (leftOrRight == "right") {
        parent->right = child;
    }
    else {
        parent->left = child;
    }

    if (child != nullptr) {
        //made a parent pointer in the .h file for AVLNode
        child->parent = parent;
    }
    return true;
}
//this function replaces the child node in rotation. Taken from zybooks
bool AVLTree::AVLTreeReplaceChild(AVLNode *parent, AVLNode *currentChild, AVLNode *newChild) {
    if (parent->left == currentChild) {
        return AVLTreeSetChild(parent, "left", newChild);
    }
    else if (parent->right == currentChild) {
        return AVLTreeSetChild(parent, "right", newChild);
    }
    return false;
}


//https://learn.zybooks.com/zybook/WRIGHTCS3100_5100AndersonFall2025/chapter/11/section/2
//extra method to update the height for balance node
//literally stole this entire method from the zybooks line by line
void AVLTree::updateTreeHeight(AVLNode *&node) {
    int leftHeight = -1;
    int rightHeight = -1;
    if (node->left != nullptr) {
        leftHeight = node->left->height;
    }
    if (node->right != nullptr) {
        rightHeight = node->right->height;
    }
    node->height = max(leftHeight, rightHeight) + 1;

}

//another method to get the balance of the tree for balanceNode. similar to update tree height
size_t AVLTree::treeBalance(AVLNode *node) {
    //sets the left and right height variable to -1 because the zybooks says so and I have no idea why
    int leftHeight = -1;
    int rightHeight = -1;
    //if the node has a left child you get that height
    if (node->left != nullptr) {
        leftHeight = node->left->height;
    }
    //if the node has a right child you get that height
    if (node->right != nullptr) {
        rightHeight = node->right->height;
    }
    //returns the balanceHeight which is the left height - the right height
    size_t balanceHeight = leftHeight - rightHeight;
    return balanceHeight;
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
        insertPart2(root, key, value);
    }
    return true;//returns true if gotten to this point since the insert would have been successful.
}
//helper for insert. Takes in the parent node, the key, and the value
AVLTree::AVLNode* AVLTree::insertPart2(AVLNode* parent, const string& key, size_t valueOfKey) {
    //https://learn.zybooks.com/zybook/WRIGHTCS3100_5100AndersonFall2025/chapter/10/section/5

    //if the node is null then it returns what was inserted as that node
    if (parent == nullptr) {
        return new AVLNode(key, valueOfKey);
        //todo update height
    }
    //if the parent is the same as the key then they are the same and duplicates are not allowed
    if (key == parent->key) {
        return parent;
    }
    //checks down left path
    if (key < parent->key) {//autogenerated by clion
        parent->left = insertPart2(parent->left, key, valueOfKey);
    }
    //checks down right path, which would be the last case
    else {
        parent->right = insertPart2(parent->right, key, valueOfKey);
    }

    //todo update height and balance parent node
    //calls the balanceNode method for the parent node
    balanceNode(parent);
    return parent;
}


//if the key exists remove will delete the key-value pair from the tree. Memory allocated to the node that
//gets removed is released. After removing the key-value pair is rebalanced if necessary. If key gets removed
//then returns true, false otherwise.
//Time complexity must be 0(log2 n)
//pretty much this calls this remove, then another remove with pointers and that pointer remove calls the method
//to finally remove the node
bool AVLTree::remove(const std::string& key) {
    //calls the recursive remove method that was given at the beginning of the assignment
    return remove(root, key);
}


//Returns true if the key is in the tree and false otherwise
//Time complexity must be 0(log2 n)
bool AVLTree::contains(const std::string& key) const {
    return contains2(root, key);
}
//recursive methods for contains
bool AVLTree::contains2(const AVLNode* current, const KeyType& key) const {
    //returns false if the key does not exist
    if (current == nullptr) {
        return false;
    }
    //if the keys match then it returns true
    if (key == current->key) {
        return true;
    }
    //if the key is less than the current then it runs contains2 again for the left child node
    if (key < current->key) {
        return contains2(current->left, key);
    }
    //if the key is greater than the current then it runs contains2 again for the right child node
    else if (key > current->key) {
        return contains2(current->right, key);
    }
}


//if the key is found get will return the value associated with the key. If the key is not found it will
//return std::nullopt. If it is found it will return std::optional<size_t>
//time complexity must be O(log2 n)
std::optional<size_t> AVLTree::get(const std::string& key) const {
    return get2(root, key);
}
//recursive method for get
std::optional<size_t> AVLTree::get2(AVLNode *current, KeyType key) const {
    //if the current is not found then it returns nullopt
    if (current == nullptr) {
        return std::nullopt;
    }
    //if it is found then it returns that value
    if (key == current->key) {
        return current -> value;
    }
    //goes to left node
    if (key < current->key) {
        return get2(current->left, key);
    }
    //goes to right node
    else if (key > current->key) {
        return get2(current->right, key);
    }
}


//returns the value stored in the node with the current key
//can retrieve value by saying "int idNum = avlTree["James"];
//can also update value associated with key by "avlTree["James"] = 1234;
//does not need to handle missing or invalid keys
//time complexity must be O(log2 n)
size_t& AVLTree::operator[](const std::string& key) {
    return operator2(root, key);
}
//recursive method for the operator
//does not check for missing or invalid keys
size_t &AVLTree::operator2(AVLNode *&current, KeyType key) {
    //if the key is found it returns the value of that node
    if (key == current->key) {
        return current -> value;
    }
    //recursive call for left child
    if (key < current->key) {
        return operator2(current->left, key);
    }
    //recursive call for right child
    else if (key > current->key) {
        return operator2(current->right, key);
    }
}


//will return a  of size_t containing all the values associated with keys >= lowKey and keys
//<= highKey. For each key found in the given range, there will be one value in the vector. If no matching
//key-value pairs are found the function should return an empty vector.

//I changed the type that findRange is to a size_t instead of a string. I also changed the call in debug to a size_t.
//The program wants findRange to return values, which should be ints, but the instructions also say it should return
//the vector of size_t. I don't know how to move ints, strings, and size_ts between each other so i made everything a size_t
std::vector<size_t> AVLTree::findRange(const std::string& lowKey, const std::string& highKey) const {
    //makes the vector for the keys
    //should technically be called valueVector or something like that
    vector<size_t> keysVector;
    //calls the other find range method for with the root, keys, and new vector
    findRange2(root, lowKey, highKey, keysVector);
    return keysVector;
}
//recursive method for findRange, returns the keysVector
void AVLTree::findRange2(AVLNode *current, const std::string &lowKey, const std::string &highKey,
    vector<size_t> &keysVector) const{
    //if the current is null then it returns back to findRange without adding anything to the vector
    if (current == nullptr) {
        //im pretty sure putting return here just makes the program back out
        return;
    }

    //looks through left child. must be before the push_back if statement
    if (current->key > lowKey) {
        findRange2(current->left, lowKey, highKey, keysVector);
    }
    //if the node's key is greater than the low and less than or high, or is the high or low then
    //it pops the values into the vector
    if (current->key >= lowKey && current->key <= highKey) {
        keysVector.push_back(current->value);
    }
    //looks through right child
    if (current->key < highKey) {
        findRange2(current->right, lowKey, highKey, keysVector);
    }
}



//returns a vector with all the keys currently in the tree. The length of the vector should be the same
//as the size of the tree
//set up pretty much the same as findRange
std::vector<std::string> AVLTree::keys() const {
    vector<string> actualKeyVector;
    keys2(root, actualKeyVector);
    return actualKeyVector;
}
//recursive method for keys
//MAKE SURE THE HELPERS ARE CONST
//also assuming this can be empty if there is nothing in the tree(?)
void AVLTree::keys2(AVLNode *current, vector<std::string> &keysVector) const {
    //if the current is nullptr then it returns the vector, again im assuming this can be empty like findRange
    if (current == nullptr) {
        return;
    }

    //goes left, gets that node, if not current, goes right, goes until one passes and pops key to that vector
    //https://learn.zybooks.com/zybook/WRIGHTCS3100_5100AndersonFall2025/chapter/10/section/7?content_resource_id=91821327
    //supposed to use a postorder traversal, not an inorder. I think???????
    //goes left
    keys2(current->left, keysVector);
    //pushed back so it gets listen before the right subtrees
    keysVector.push_back(current->key);
    //then right gets thrown on
    keys2(current->right, keysVector);
}


//returns how many key-value pairs are in the tree
//time complexity should be O(1)
//pretty sure this is just supposed to return the treeHeight
//random side tangent because my head hurts, this class is hard and I should really pay attention more lol
size_t AVLTree::size() const {
    //returns treeHeight which should be the same as the number of key-value pairs
    return treeHeight;
}



//returns height of the AVL tree
//time complexity should be O(1)
size_t AVLTree::getHeight() const {
    //because of a crash I made a check that if root does not exist then height must be 0
    if (root == nullptr) {
        return 0;
    }
    //calls the other node getHight and returns the height in the node class
    return root->getHeight();
}


//copy constructor
AVLTree::AVLTree(const AVLTree& other) {
    root = copyConstucter(other.root);
    treeHeight = other.treeHeight;
}
//recursive method to make a deep copy of the tree. It returns when the copy is finished.
AVLTree::AVLNode* AVLTree::copyConstucter(const AVLNode* current) {
    if (current == nullptr) {
        return nullptr;
    }
    //makes a new node with the key and value
    AVLNode* deepCopy = new AVLNode(current->key, current->value);
    //sets the deep copy left child to the current left child
    deepCopy->left = copyConstucter(current->left);

     //sets the deep copy right child to the current right child
    deepCopy->right = copyConstucter(current->right);
    //sets the deep copy height to the current's height
    deepCopy->height = current->getHeight();
    //returns the deep copy
    return deepCopy;
}


//assignment operator
//makes deep copy of the other tree
void AVLTree::operator=(const AVLTree& other) {
    //this is the assigment operator
    //makes sure there is no self assigment
    if (this == &other) {
        return;
    }
    //cleans up everything before it makes the copy in the event there is some random stuff left behind
    treeHeight = 0;
    root = nullptr;
    //reused the deconstructorMethod
    deconstructorMethod(root);
    //reused the copyConstucter
    //also clion generated most of these lines. going to pretend like it knows what it's doing because I sure don't
    //sets new root and tree
    root = copyConstucter(other.root);
    //copies the treeHeight
    treeHeight = other.treeHeight;
}


//deconstructor
//goes through all nodes using a postorder traversal and uses delete to release memory taken in each node
AVLTree::~AVLTree() {
    //gotta delete the tree first and then reset root and treeHeight
    deconstructorMethod(root);
    root = nullptr;
    treeHeight = 0;

}
//helper method for the deconstructor. Clion autofilled all of it
void AVLTree::deconstructorMethod(AVLNode *current) {
    //returns if the current node us null
    if (current == nullptr) {
        return;
    }
    //deletes left child
    deconstructorMethod(current->left);
    //deletes right child
    deconstructorMethod(current->right);
    delete current;
}

//default constructor, sets the root to null and the height to 0 since there is nothing yet
AVLTree::AVLTree() {
    root = nullptr;
    treeHeight = 0;
}
//method to print out the tree
std::ostream &operator<<(std::ostream &os, const AVLTree &AVLTree) {
    //calls printMethod for recursion
    AVLTree.printMethod(os, AVLTree.root);
    return os;
}
//helper method for operator<<
void AVLTree::printMethod( std::ostream &os, AVLNode *current) const {
    if (current == nullptr) {
        return;
    }
    //prints out the right subtree because of the right-child-first in-order traversal
    printMethod(os, current->right);
    //prints the key and value, clion generated this line
    std::cout << "{ " << current->key << ", " << current->value << " }" << std::endl;
    //prints left tree
    printMethod(os, current->left);
}