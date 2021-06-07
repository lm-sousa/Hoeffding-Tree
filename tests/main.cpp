#include <cstddef>
#include <functional>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <utility>

#include "../src/BinaryTree.hpp"
#include "../src/HoeffdingTree.hpp"
#include "../src/JsonExporter.hpp"
#include "../src/Node.hpp"
#include "Tester.hpp"

int main() {

    // Run tests
    Tester ts;

#ifdef __BINARY_TREE_HPP__
    ts.addTest("Root Node Exists", []() {
        BinaryTree<Node<>> tree;
        return std::make_pair(tree.getRootNode(), "");
    });

    ts.addTest("New tree has size 1", []() {
        BinaryTree<Node<>> tree;

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 1, executionLog);
    });

    ts.addTest("Add node", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addLeftChild(root);

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 2, executionLog);
    });

    ts.addTest("Add Left Child", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addLeftChild(root);

        std::string executionLog = root->getLeftChild()
                                       ? "Left child has been created."
                                       : "Left child has not been created";

        return std::make_pair(root->getLeftChild(), executionLog);
    });

    ts.addTest("Add Right Child", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addRightChild(root);

        std::string executionLog = root->getRightChild()
                                       ? "Right child has been created."
                                       : "Right child has not been created";

        return std::make_pair(root->getRightChild(), executionLog);
    });

    ts.addTest("Root with left child has size 2", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addLeftChild(root);

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 2, executionLog);
    });

    ts.addTest("Root with right child has size 2", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addRightChild(root);

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 2, executionLog);
    });

    ts.addTest("Add 2 childs, check counter", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();

        tree.addLeftChild(tree.addLeftChild(root));

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 3, executionLog);
    });

    ts.addTest("Add 2 childs, check existance", []() {
        BinaryTree<Node<>> tree;
        Node<> *root = tree.getRootNode();
        tree.addLeftChild(tree.addLeftChild(root));

        bool ret = false;
        std::string executionLog;

        if (root->hasLeftChild()) {
            executionLog = "Tree root has a left child.\n";
            ret = root->getLeftChild()->hasLeftChild();
            executionLog += ret ? "\tRoot's left child has left child"
                                : "\tRoot's left child has no left child";
        }

        return std::make_pair(ret, executionLog);
    });
#endif
#ifdef __HOEFFDING_TREE_HPP__

    ts.addTest("Hoeffding Tree - SampleCountTotal when training", []() {
        HoeffdingTree<NodeData<>> tree(1, 0.001, 0.05);
        bool doSplitTrial = true;
        const uint N_Samples = 1;

        float x[N_Samples][16] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        };

        uint y[N_Samples] = {1};

        for (uint i = 0; i < N_Samples; i++)
            tree.train(x[i], y[i], doSplitTrial);

        return std::make_pair(
            tree.getRootNode()->getData().getSampleCountTotal() == 1,
            "Node sample count: " +
                std::to_string(
                    tree.getRootNode()->getData().getSampleCountTotal()));
    });

    ts.addTest("Hoeffding Tree - sample count distribuitions", []() {
        HoeffdingTree<NodeData<>> tree(1, 0.001, 0.05);
        bool doSplitTrial = true;
        const uint N_Samples = 100;

        float x[N_Samples][16] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0.185, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        uint y[N_Samples] = {1, 0};

        for (uint i = 0; i < N_Samples; i++) {
            // std::cout << i << " : " << i % 2 << std::endl;
            tree.train(x[i % 2], y[i % 2], doSplitTrial);
        }

        // tree.getRootNode()->getData().evaluateSplit();

        return std::make_pair(true, "Will always return true");
    });

#endif

    ts.runTestSuite(false, true);

    return 0;
}
