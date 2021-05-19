#include <cstddef>
#include <functional>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>

#include "../src/BinaryTree.hpp"
#include "../src/HoeffdingTree.hpp"
#include "../src/Node.hpp"
#include "../src/NodeData.hpp"
#include "Tester.hpp"

int main() {

    // Run tests
    Tester ts;

#ifdef __BINARY_TREE_HPP__
    ts.addTest("Root Node Exists", []() {
        BinaryTree<Node<>> tree;
        return tree.getRootNode();
    });

    ts.addTest("New tree has size 1", []() {
        BinaryTree<Node<>> tree;
        return tree.getSize() == 1;
    });

    ts.addTest("Add node", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();

        tree.addLeftChild(root);
        return tree.getSize() == 2;
    });

    ts.addTest("Add Left Child", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addLeftChild(root);

        return root->getLeftChild();
    });

    ts.addTest("Add Right Child", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addRightChild(root);

        return root->getRightChild();
    });

    ts.addTest("Root with left child has size 2", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addLeftChild(root);

        return tree.getSize() == 2;
    });

    ts.addTest("Root with right child has size 2", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addRightChild(root);

        return tree.getSize() == 2;
    });

    ts.addTest("Add 2 childs", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();

        tree.addLeftChild(tree.addLeftChild(root));

        return tree.getSize() == 3;
    });

    ts.addTest("Add 2 childs, remove both", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addLeftChild(tree.addLeftChild(root));

        if (root->hasLeftChild())
            return root->getLeftChild()->hasLeftChild();

        return false;
    });
#endif
#ifdef __HOEFFDING_TREE_HPP__

    /*ts.addTest("Train Hoeffding Tree", []() {
        HoeffdingTree tree;
        return tree.train();
    });*/

#endif

    ts.runTestSuite(false);

    return 0;
}
