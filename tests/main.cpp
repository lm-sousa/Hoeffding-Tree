#include <functional>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>

#include "../src/BinaryTree.hpp"
#include "Tester.hpp"

int main(int argc, char const *argv[]) {

    // Run tests
    Tester ts;

    ts.addTest("Root Node Exists", []() {
        BinaryTree tree;
        tree.prime();
        return tree.getRootNode();
    });

    ts.addTest("Add node", []() {
        BinaryTree tree;
        tree.prime();
        BinaryTree::Node *root = tree.getRootNode();

        root->addLeftChild();
        return tree.getSize() == 2;
    });

    /*TestSuite.addTest("Add Left Child", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        root->setLeftChild(tree.createNode());

        return root->getLeftChild();
    });

    TestSuite.addTest("Add Right Child", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        root->setRightChild(tree.createNode());

        return root->getRightChild();
    });

    TestSuite.addTest("Remove Left Child", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        BinaryTree::Node *child = tree.createNode();
        root->setLeftChild(child);
        child->deleteNode();
        return !root->hasLeftChild();
    });

    TestSuite.addTest("Remove Right Child", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        BinaryTree::Node *child = tree.createNode();
        root->setRightChild(child);
        child->deleteNode();
        return !root->hasRightChild();
    });

    TestSuite.addTest("New tree has size 1", []() {
        BinaryTree tree;
        return tree.currentSize() == 1;
    });

    TestSuite.addTest("Root with child has size 2", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        root->setLeftChild(tree.createNode());

        return tree.currentSize() == 2;
    });

    TestSuite.addTest("Root with removed child has size 1", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        BinaryTree::Node *child = tree.createNode();
        root->setLeftChild(child);
        child->deleteNode();

        return tree.currentSize() == 1;
    });

    TestSuite.addTest("Add 2 childs", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        BinaryTree::Node *child = tree.createNode();
        BinaryTree::Node *child1 = tree.createNode();
        root->setLeftChild(child);
        child->setLeftChild(child1);

        return tree.currentSize() == 3;
    });

    TestSuite.addTest("Add 2 childs, remove both", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        BinaryTree::Node *child = tree.createNode();
        BinaryTree::Node *child1 = tree.createNode();
        root->setLeftChild(child);
        child->setLeftChild(child1);
        child->deleteNode();

        return tree.currentSize() == 1;
    });

    TestSuite.addTest("Add 2 childs remove 1", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        BinaryTree::Node *child = tree.createNode();
        BinaryTree::Node *child1 = tree.createNode();
        root->setLeftChild(child);
        child->setLeftChild(child1);
        child1->deleteNode();

        return tree.currentSize() == 2;
    });

    TestSuite.addTest("Add 2 childs, use deleteLeftChild", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        root->setLeftChild(tree.createNode());
        root->setRightChild(tree.createNode());
        root->deleteLeftChild();

        return tree.currentSize() == 2;
    });

    TestSuite.addTest("Add 2 childs, use deleteRightChild", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        root->setLeftChild(tree.createNode());
        root->setRightChild(tree.createNode());
        root->deleteRightChild();

        return tree.currentSize() == 2;
    });

    TestSuite.addTest("readded child must stay in same position", []() {
        BinaryTree tree;
        BinaryTree::Node *root = tree.getRootNode();
        BinaryTree::Node *child = tree.createNode();
        root->setLeftChild(child);
        root->setRightChild(tree.createNode());
        root->deleteLeftChild();
        BinaryTree::Node *child1 = tree.createNode();
        root->setLeftChild(child1);

        return child == child1;
    });*/

    ts.runTestSuite(false);

    return 0;
}
