/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>


using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

    AVLTree();
    ~AVLTree();
    bool remove(const std::string &key);
    bool insert(const std::string &key, size_t value);

    bool contains(const std::string &key) const;
    std::optional<size_t> get(const std::string &key) const;
    size_t &operator[](const std::string &key);
    vector<size_t> findRange(const std::string &lowKey, const std::string &highKey) const;
    std::vector<std::string> keys() const;
    size_t size() const;

    size_t getHeight() const;
    AVLTree(const AVLTree &other);
    void operator=(const AVLTree &other);

    //prints out the tree
    friend std::ostream &operator<<(std::ostream &os, const AVLTree &avlTree);



protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;
        AVLNode* parent;

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

    bool rotateRight(AVLNode *&node);

    bool roatateLeft(AVLNode *&node);

    bool AVLTreeSetChild(AVLNode *parent, const std::string &leftOrRight, AVLNode *child);

    bool AVLTreeReplaceChild(AVLNode *parent, AVLNode *currentChild, AVLNode *newChild);

    //---------------------------------------------------------------------------------------------------------

    AVLNode* insertPart2(AVLNode* parent, const std::string& key, size_t valueOfKey);

    bool contains2(const AVLNode *current, const KeyType &key) const;

    std::optional<size_t> get2(AVLNode *current, KeyType key) const;

    size_t &operator2(AVLNode *&current, KeyType key);

    void findRange2(AVLNode *current, const std::string &lowKey, const std::string &highKey, vector<size_t> &keysVector) const;

    void keys2(AVLNode *current, vector<string> &keysVector) const;

    AVLNode *copyConstucter(const AVLNode *current);

    void deconstructorMethod(AVLNode *current);

    void printMethod(std::ostream &os, AVLNode *current) const;

    void updateTreeHeight(AVLNode *&current);

    int treeBalance(AVLNode *node);

    size_t size2(AVLNode *node) const;
};

#endif //AVLTREE_H