#ifndef __BINARY_TREE_HPP__
#define __BINARY_TREE_HPP__

#include <cstddef>
#include <functional>
#include <stdlib.h>

#define MAX_TREE_SIZE 100

class BinaryTree {

  public:
    class Node {

      public:
        void setTree(BinaryTree *tree);

        void *getData();
        void setData(void *data);
        void clearData();

        bool hasParent();
        Node *getParent();

        bool hasLeftChild();
        Node *getLeftChild();
        Node *addLeftChild();

        bool hasRightChild();
        Node *getRightChild();
        Node *addRightChild();

      private:
        BinaryTree *_tree = NULL;
        void *_data = NULL;
        Node *_parent = NULL;
        Node *_leftChild = NULL;
        Node *_rightChild = NULL;

        void _setParent(Node *parent);
        void _setLeftChild(Node *child);
        void _setRightChild(Node *child);
    };

    // BinaryTree();
    void prime();
    uint getCapacity();
    uint getSize();
    void increaseSize();
    bool canAddNode();
    Node *getRootNode();

    // static void DFS(Node *origin, void (BinaryTree::Node::*function)());

  private:
    const uint _capacity = MAX_TREE_SIZE;
    uint _size = 1;
    Node _nodes[MAX_TREE_SIZE];
    Node *_getNextFreeNode();
};

#endif