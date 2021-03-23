#ifndef __BINARY_TREE_HPP__
#define __BINARY_TREE_HPP__

#include <cstddef>
#include <functional>
#include <stdlib.h>

#define MAX_TREE_SIZE 100

class BinaryTree {

  public:
    class Node {
      private:
        BinaryTree *tree;
        bool isUsed = false;
        void *data;
        Node *_parent;
        Node *_leftChild;
        Node *_rightChild;

        void _setUsedStatus(bool isInUse);

      public:
        bool isInUse();
        void setUsed();
        void setUnused();

        void *getData();
        void setData(void *data);
        void clearData();

        bool hasParent();
        Node *getParent();

        bool hasLeftChild();
        Node *getLeftChild();
        Node &addLeftChild();
        void deleteLeftChild();

        bool hasRightChild();
        Node *getRightChild();
        Node &addRightChild();
        void deleteRightChild();

        void deleteNode();

        void _setTree(BinaryTree *tree);
        void _setParent(Node *parent);
        void _setLeftChild(Node *child);
        void _setRightChild(Node *child);
        void _clearParent();
        void _clearLeftChild();
        void _clearRightChild();
        Node &_addNode();
        void _clearNode();
    };

    BinaryTree();
    static void DFS(Node *origin, void (BinaryTree::Node::*function)());
    uint getCurrentSize();
    uint getCapacity();
    Node *getRootNode();

  private:
    const uint _capacity = MAX_TREE_SIZE;
    Node _nodes[MAX_TREE_SIZE];
    Node *_getNextFreeNode();
};

#endif