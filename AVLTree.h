/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <bits/stl_vector.h>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;
    };

public:

    private:
    AVLNode* root;
    size_t treeHeight;


    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);

    //---------------------------------------------------------------------------------------------------------

    bool insert(const std::string &key, size_t value);

    void insertPart2(AVLNode *parent, AVLNode *newNode);

    bool remove(const std::string &key);

    bool contains(const std::string &key) const;

    bool contains2(const AVLNode *current, const KeyType &key) const;

    std::optional<size_t> get(const std::string &key) const;

    std::optional<size_t> get2(AVLNode *current, KeyType key) const;

    size_t &operator[](const std::string &key);

    size_t &operator2(AVLNode *&current, KeyType key);

    vector<std::string> findRange(const std::string &lowKey, const std::string &highKey) const;

    void findRange2(AVLNode *current, const std::string &lowKey, const std::string &highKey, vector<string> &keysVector) const;

    std::vector<std::string> keys() const;

    void keys2(AVLNode *current, vector<string> &keysVector) const;

    size_t size() const;

    size_t getHeight() const;

    AVLTree(const AVLTree &other);

    AVLNode *copyConstucter(const AVLNode *current);

    void operator=(const AVLTree &other);

    ~AVLTree();

    void deconstructorMethod(AVLNode *current);

    AVLTree();

    //prints out the tree
    friend std::ostream &operator<<(std::ostream &os, const AVLTree &avlTree) {

    }
};

#endif //AVLTREE_H
