#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <utility>

//#define USE_XILINX_AP_TYPES
//#include "ap_fixed.h"

#ifndef USE_XILINX_AP_TYPES
#pragma clang diagnostic warning "-Wall"
#pragma clang diagnostic warning "-Wextra"
#endif

#include "../src/BinaryTree.hpp"
#include "../src/HoeffdingTree.hpp"
#include "../src/JsonExporter.hpp"
#include "../src/Node.hpp"
#include "../src/TypeChooser.hpp"
#include "Tester.hpp"

float irisDataset[150][5] = {
    {5.1, 3.5, 1.4, 0.2, 0}, {4.9, 3.0, 1.4, 0.2, 0}, {7.0, 3.2, 4.7, 1.4, 1},
    {6.4, 3.2, 4.5, 1.5, 1}, {6.3, 3.3, 6.0, 2.5, 2}, {5.8, 2.7, 5.1, 1.9, 2},
    {5.3, 3.7, 1.5, 0.2, 0}, {5.0, 3.3, 1.4, 0.2, 0}, {6.9, 3.1, 4.9, 1.5, 1},
    {5.5, 2.3, 4.0, 1.3, 1}, {7.1, 3.0, 5.9, 2.1, 2}, {6.3, 2.9, 5.6, 1.8, 2},
    {4.7, 3.2, 1.3, 0.2, 0}, {4.6, 3.1, 1.5, 0.2, 0}, {6.5, 2.8, 4.6, 1.5, 1},
    {5.7, 2.8, 4.5, 1.3, 1}, {6.5, 3.0, 5.8, 2.2, 2}, {7.6, 3.0, 6.6, 2.1, 2},
    {5.0, 3.6, 1.4, 0.2, 0}, {5.4, 3.9, 1.7, 0.4, 0}, {6.3, 3.3, 4.7, 1.6, 1},
    {4.9, 2.4, 3.3, 1.0, 1}, {4.9, 2.5, 4.5, 1.7, 2}, {7.3, 2.9, 6.3, 1.8, 2},
    {4.6, 3.4, 1.4, 0.3, 0}, {5.0, 3.4, 1.5, 0.2, 0}, {6.6, 2.9, 4.6, 1.3, 1},
    {5.2, 2.7, 3.9, 1.4, 1}, {6.7, 2.5, 5.8, 1.8, 2}, {7.2, 3.6, 6.1, 2.5, 2},
    {4.4, 2.9, 1.4, 0.2, 0}, {4.9, 3.1, 1.5, 0.1, 0}, {5.0, 2.0, 3.5, 1.0, 1},
    {5.9, 3.0, 4.2, 1.5, 1}, {6.5, 3.2, 5.1, 2.0, 2}, {6.4, 2.7, 5.3, 1.9, 2},
    {5.4, 3.7, 1.5, 0.2, 0}, {4.8, 3.4, 1.6, 0.2, 0}, {6.0, 2.2, 4.0, 1.0, 1},
    {6.1, 2.9, 4.7, 1.4, 1}, {6.8, 3.0, 5.5, 2.1, 2}, {5.7, 2.5, 5.0, 2.0, 2},
    {4.8, 3.0, 1.4, 0.1, 0}, {4.3, 3.0, 1.1, 0.1, 0}, {5.6, 2.9, 3.6, 1.3, 1},
    {6.7, 3.1, 4.4, 1.4, 1}, {5.8, 2.8, 5.1, 2.4, 2}, {6.4, 3.2, 5.3, 2.3, 2},
    {5.8, 4.0, 1.2, 0.2, 0}, {5.7, 4.4, 1.5, 0.4, 0}, {5.6, 3.0, 4.5, 1.5, 1},
    {5.8, 2.7, 4.1, 1.0, 1}, {6.5, 3.0, 5.5, 1.8, 2}, {7.7, 3.8, 6.7, 2.2, 2},
    {5.4, 3.9, 1.3, 0.4, 0}, {5.1, 3.5, 1.4, 0.3, 0}, {6.2, 2.2, 4.5, 1.5, 1},
    {5.6, 2.5, 3.9, 1.1, 1}, {7.7, 2.6, 6.9, 2.3, 2}, {6.0, 2.2, 5.0, 1.5, 2},
    {5.7, 3.8, 1.7, 0.3, 0}, {5.1, 3.8, 1.5, 0.3, 0}, {5.9, 3.2, 4.8, 1.8, 1},
    {6.1, 2.8, 4.0, 1.3, 1}, {6.9, 3.2, 5.7, 2.3, 2}, {5.6, 2.8, 4.9, 2.0, 2},
    {5.4, 3.4, 1.7, 0.2, 0}, {5.1, 3.7, 1.5, 0.4, 0}, {6.3, 2.5, 4.9, 1.5, 1},
    {6.1, 2.8, 4.7, 1.2, 1}, {7.7, 2.8, 6.7, 2.0, 2}, {6.3, 2.7, 4.9, 1.8, 2},
    {4.6, 3.6, 1.0, 0.2, 0}, {5.1, 3.3, 1.7, 0.5, 0}, {6.4, 2.9, 4.3, 1.3, 1},
    {6.6, 3.0, 4.4, 1.4, 1}, {6.7, 3.3, 5.7, 2.1, 2}, {7.2, 3.2, 6.0, 1.8, 2},
    {4.8, 3.4, 1.9, 0.2, 0}, {5.0, 3.0, 1.6, 0.2, 0}, {6.8, 2.8, 4.8, 1.4, 1},
    {6.7, 3.0, 5.0, 1.7, 1}, {6.2, 2.8, 4.8, 1.8, 2}, {6.1, 3.0, 4.9, 1.8, 2},
    {5.0, 3.4, 1.6, 0.4, 0}, {5.2, 3.5, 1.5, 0.2, 0}, {6.0, 2.9, 4.5, 1.5, 1},
    {5.7, 2.6, 3.5, 1.0, 1}, {6.4, 2.8, 5.6, 2.1, 2}, {7.2, 3.0, 5.8, 1.6, 2},
    {5.2, 3.4, 1.4, 0.2, 0}, {4.7, 3.2, 1.6, 0.2, 0}, {5.5, 2.4, 3.8, 1.1, 1},
    {5.5, 2.4, 3.7, 1.0, 1}, {7.4, 2.8, 6.1, 1.9, 2}, {7.9, 3.8, 6.4, 2.0, 2},
    {4.8, 3.1, 1.6, 0.2, 0}, {5.4, 3.4, 1.5, 0.4, 0}, {5.8, 2.7, 3.9, 1.2, 1},
    {6.0, 2.7, 5.1, 1.6, 1}, {6.4, 2.8, 5.6, 2.2, 2}, {6.3, 2.8, 5.1, 1.5, 2},
    {5.2, 4.1, 1.5, 0.1, 0}, {5.5, 4.2, 1.4, 0.2, 0}, {5.4, 3.0, 4.5, 1.5, 1},
    {6.0, 3.4, 4.5, 1.6, 1}, {6.1, 2.6, 5.6, 1.4, 2}, {7.7, 3.0, 6.1, 2.3, 2},
    {4.9, 3.1, 1.5, 0.2, 0}, {5.0, 3.2, 1.2, 0.2, 0}, {6.7, 3.1, 4.7, 1.5, 1},
    {6.3, 2.3, 4.4, 1.3, 1}, {6.3, 3.4, 5.6, 2.4, 2}, {6.4, 3.1, 5.5, 1.8, 2},
    {5.5, 3.5, 1.3, 0.2, 0}, {4.9, 3.6, 1.4, 0.1, 0}, {5.6, 3.0, 4.1, 1.3, 1},
    {5.5, 2.5, 4.0, 1.3, 1}, {6.0, 3.0, 4.8, 1.8, 2}, {6.9, 3.1, 5.4, 2.1, 2},
    {4.4, 3.0, 1.3, 0.2, 0}, {5.1, 3.4, 1.5, 0.2, 0}, {5.5, 2.6, 4.4, 1.2, 1},
    {6.1, 3.0, 4.6, 1.4, 1}, {6.7, 3.1, 5.6, 2.4, 2}, {6.9, 3.1, 5.1, 2.3, 2},
    {5.0, 3.5, 1.3, 0.3, 0}, {4.5, 2.3, 1.3, 0.3, 0}, {5.8, 2.6, 4.0, 1.2, 1},
    {5.0, 2.3, 3.3, 1.0, 1}, {5.8, 2.7, 5.1, 1.9, 2}, {6.8, 3.2, 5.9, 2.3, 2},
    {4.4, 3.2, 1.3, 0.2, 0}, {5.0, 3.5, 1.6, 0.6, 0}, {5.6, 2.7, 4.2, 1.3, 1},
    {5.7, 3.0, 4.2, 1.2, 1}, {6.7, 3.3, 5.7, 2.5, 2}, {6.7, 3.0, 5.2, 2.3, 2},
    {5.1, 3.8, 1.9, 0.4, 0}, {4.8, 3.0, 1.4, 0.3, 0}, {5.7, 2.9, 4.2, 1.3, 1},
    {6.2, 2.9, 4.3, 1.3, 1}, {6.3, 2.5, 5.0, 1.9, 2}, {6.5, 3.0, 5.2, 2.0, 2},
    {5.1, 3.8, 1.6, 0.2, 0}, {4.6, 3.2, 1.4, 0.2, 0}, {5.1, 2.5, 3.0, 1.1, 1},
    {5.7, 2.8, 4.1, 1.3, 1}, {6.2, 3.4, 5.4, 2.3, 2}, {5.9, 3.0, 5.1, 1.8, 2}};

// ap_fixed<32, 8>

typedef HoeffdingTree<Node<NodeData<float, 4, 3>>> FixedTree;

FixedTree::data_t fixedDataset[150][5];

FixedTree::data_t scale(FixedTree::data_t a) { return a * 8; }

int main() {

    // Normalize Iris dataset values
    for (uint i = 0; i < 150; i++) {
        for (int j = 0; j < 4; j++)
            irisDataset[i][j] /= 8;
    }

    for (uint i = 0; i < 150; i++) {
        for (uint j = 0; j <= 4; j++) {
            fixedDataset[i][j] = irisDataset[i][j];
        }
    }

    // Run tests
    Tester ts;

#ifdef __BINARY_TREE_HPP__

    ts.addTest("Binary Tree - New tree has size 1", []() {
        typedef BinaryTree<Node<>> Tree;
        Tree tree;

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 1, executionLog);
    });

    ts.addTest("Binary Tree - Add node", []() {
        typedef BinaryTree<Node<>> Tree;
        typedef Tree::_NodeClass _NodeClass;
        Tree tree;

        _NodeClass &root = tree.getRootNode();
        tree.addLeftChild(root);

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 2, executionLog);
    });

    ts.addTest("Binary Tree - Add Left Child", []() {
        typedef BinaryTree<Node<>> Tree;
        typedef Tree::_NodeClass _NodeClass;
        Tree tree;

        _NodeClass &root = tree.getRootNode();
        bool r = tree.addLeftChild(root);

        std::string executionLog = (root.hasLeftChild() && r)
                                       ? "Left child has been created."
                                       : "Left child has not been created";

        return std::make_pair((root.hasLeftChild() && r), executionLog);
    });

    ts.addTest("Binary Tree - Add Left Child - Full tree", []() {
        typedef BinaryTree<Node<NodeData<>, 1>> Tree;
        typedef Tree::_NodeClass _NodeClass;
        Tree tree;

        _NodeClass &root = tree.getRootNode();
        bool r = tree.addLeftChild(root);

        std::string executionLog = (root.hasLeftChild() || r)
                                       ? "Left child has been created."
                                       : "Left child has not been created";

        return std::make_pair(!(root.hasLeftChild() || r), executionLog);
    });

    ts.addTest("Binary Tree - Add Right Child", []() {
        typedef BinaryTree<Node<>> Tree;
        typedef Tree::_NodeClass _NodeClass;
        Tree tree;

        _NodeClass &root = tree.getRootNode();
        bool r = tree.addRightChild(root);

        std::string executionLog = (root.hasRightChild() && r)
                                       ? "Right child has been created."
                                       : "Right child has not been created";

        return std::make_pair((root.hasRightChild() && r), executionLog);
    });

    ts.addTest("Binary Tree - Add Right Child - Full tree", []() {
        typedef BinaryTree<Node<NodeData<>, 1>> Tree;
        typedef Tree::_NodeClass _NodeClass;
        Tree tree;

        _NodeClass &root = tree.getRootNode();
        bool r = tree.addRightChild(root);

        std::string executionLog = (root.hasRightChild() || r)
                                       ? "Right child has been created."
                                       : "Right child has not been created";

        return std::make_pair(!(root.hasRightChild() || r), executionLog);
    });

    ts.addTest("Binary Tree - Root with left child has size 2", []() {
        typedef BinaryTree<Node<>> Tree;
        typedef Tree::_NodeClass _NodeClass;
        Tree tree;

        _NodeClass &root = tree.getRootNode();
        tree.addLeftChild(root);

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 2, executionLog);
    });

    ts.addTest("Binary Tree - Root with right child has size 2", []() {
        typedef BinaryTree<Node<>> Tree;
        typedef Tree::_NodeClass _NodeClass;
        Tree tree;

        _NodeClass &root = tree.getRootNode();
        tree.addRightChild(root);

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 2, executionLog);
    });

    ts.addTest("Binary Tree - Add 2 childs, check counter", []() {
        typedef BinaryTree<Node<>> Tree;
        typedef Tree::_NodeClass _NodeClass;
        Tree tree;

        _NodeClass &root = tree.getRootNode();
        tree.addLeftChild(tree.getNode(tree.addLeftChild(root)));

        std::string executionLog =
            "Tree has size " + std::to_string(tree.getSize());
        return std::make_pair(tree.getSize() == 3, executionLog);
    });

    ts.addTest("Binary Tree - Add 2 childs, check existance", []() {
        typedef BinaryTree<Node<>> Tree;
        typedef Tree::_NodeClass _NodeClass;
        Tree tree;

        _NodeClass &root = tree.getRootNode();
        tree.addLeftChild(tree.getNode(tree.addLeftChild(root)));

        bool ret = false;
        std::string executionLog;

        if (root.hasLeftChild()) {
            executionLog = "Tree root has a left child.\n";
            ret = tree.getNode(root.getLeftChild()).hasLeftChild();
            executionLog += ret ? "\tRoot's left child has left child"
                                : "\tRoot's left child has no left child";
        }

        return std::make_pair(ret, executionLog);
    });
#endif
#ifdef __HOEFFDING_TREE_HPP__

    ts.addTest("Hoeffding Tree - SampleCountTotal when training", []() {
        typedef HoeffdingTree<> Tree;
        typedef typename Tree::sample_count_t sample_count_t;

        Tree tree(1, 0.001, 0.05);
        bool doSplitTrial = true;
        const sample_count_t N_Samples = 1;

        float x[N_Samples][16] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        };

        sample_count_t y[N_Samples] = {1};

        for (sample_count_t i = 0; i < N_Samples; i++)
            tree.train(x[i], y[i], doSplitTrial);

        return std::make_pair(
            tree.getRootNode().getData().getSampleCountTotal() == 1,
            "Node sample count: " +
                std::to_string(
                    tree.getRootNode().getData().getSampleCountTotal()));
    });

    ts.addTest("Hoeffding Tree - sample count distribuitions", []() {
        typedef HoeffdingTree<> Tree;
        typedef typename Tree::sample_count_t sample_count_t;

        Tree tree(1, 0.001, 0.05);
        bool doSplitTrial = true;
        const sample_count_t N_Samples = 100;

        float x[N_Samples][16] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0.185, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        sample_count_t y[N_Samples] = {1, 0};

        for (sample_count_t i = 0; i < N_Samples; i++) {
            // std::cout << i << " : " << i % 2 << std::endl;
            tree.train(x[i % 2], y[i % 2], doSplitTrial);
        }

        // tree.getRootNode()->getData().evaluateSplit();

        return std::make_pair(true, "Will always return true");
    });

    ts.addTest("Hoeffding Tree - Iris sklearn dataset", []() {
        typedef HoeffdingTree<Node<NodeData<float, 4, 3>>> Tree;
        typedef typename Tree::sample_count_t sample_count_t;

        Tree tree(1, 0.01, 0.05);
        bool doSplitTrial = true;
        const sample_count_t N_Samples = 150;

        for (sample_count_t i = 0; i < N_Samples; i++) {
            tree.train(irisDataset[i], irisDataset[i][4], doSplitTrial);
        }

        // tree.getRootNode()->getData().evaluateSplit();

        return std::make_pair(true, "Will always return true");
    });

#endif
#ifdef __JSON_EXPORTER_HPP__

    ts.addTest("JsonExporter - arrayToJson()", []() {
        const uint size = 5;
        const int array[size] = {1, 2, 3, 4, 5};

        std::string str = JsonExporter::arrayToJson(array, size);
        bool ret = str == "[1,2,3,4,5]";

        return std::make_pair(ret,
                              str + (ret ? " == " : " != ") + "[1,2,3,4,5]");
    });

    ts.addTest("JsonExporter - vectorToJson()", []() {
        const std::vector<int> array = {1, 2, 3, 4, 5};

        std::string str = JsonExporter::vectorToJson(array);
        bool ret = str == "[1,2,3,4,5]";

        return std::make_pair(ret,
                              str + (ret ? " == " : " != ") + "[1,2,3,4,5]");
    });

    ts.addTest("JsonExporter - mapToJson()", []() {
        std::map<std::string, int> map;

        map.insert(std::pair<std::string, int>("hello", 1));
        map.insert(std::pair<std::string, int>("world", 200));

        std::string str = JsonExporter::mapToJson(map);

        bool ret = str == "{\"hello\":1,\"world\":200}";

        return std::make_pair(ret, str + (ret ? " == " : " != ") +
                                       "{\"hello\":1,\"world\":200}");
    });

    ts.addTest("JsonExporter - nodeClassCountsToJson()", []() {
        typedef HoeffdingTree<Node<NodeData<float, 4, 3>>> Tree;
        typedef typename Tree::sample_count_t sample_count_t;

        Tree tree(1, 0.01, 0.05);
        bool doSplitTrial = false;
        const sample_count_t N_Samples = 150;

        for (sample_count_t i = 0; i < N_Samples; i++) {
            tree.train(irisDataset[i], irisDataset[i][4], doSplitTrial);
        }

        std::string str =
            JsonExporter::nodeClassCountsToJson(tree.getRootNode(), 3);

        bool ret = str == "[[50.0,50.0,50.0]]";

        return std::make_pair(ret, str + (ret ? " == " : " != ") +
                                       "[[50.0,50.0,50.0]]");
    });

    ts.addTest(
        "JsonExporter - nodeDataToJson() without scalers - split node", []() {
            typedef HoeffdingTree<Node<NodeData<float, 4, 3>>> Tree;
            typedef typename Tree::sample_count_t sample_count_t;

            Tree tree(1, 0.01, 0.05);
            bool doSplitTrial = true;
            const sample_count_t N_Samples = 150;

            for (sample_count_t i = 0; i < N_Samples; i++) {
                tree.train(irisDataset[i], irisDataset[i][4], doSplitTrial);
            }

            std::string str =
                JsonExporter::nodeDataToJson(tree.getRootNode(), 1, 2);

            bool ret = str == "[-1,-1,-2,-2.0,0.666667,150,150.0]";

            return std::make_pair(ret,
                                  str + (ret ? " == " : " != ") +
                                      "[-1,-1,-2,-2.0,0.666667,150,150.0]");
        });

    ts.addTest(
        "JsonExporter - nodeDataToJson() with scalers - split node", []() {
            typedef HoeffdingTree<Node<NodeData<float, 4, 3>>> Tree;
            typedef typename Tree::sample_count_t sample_count_t;

            Tree tree(1, 0.01, 0.05);
            bool doSplitTrial = true;
            const sample_count_t N_Samples = 150;

            for (sample_count_t i = 0; i < N_Samples; i++) {
                tree.train(irisDataset[i], irisDataset[i][4], doSplitTrial);
            }

            typedef Tree::data_t data_t;

            static const Tree::_DataClass::sampleScaler
                scalers[Tree::_DataClass::N_Attributes] = {
                    [](data_t a) { return a * 8; },
                    [](data_t a) { return a * 8; },
                    [](data_t a) { return a * 8; },
                    [](data_t a) { return a * 8; }};

            std::string str =
                JsonExporter::nodeDataToJson(tree.getRootNode(), 1, 2, scalers);

            bool ret = str == "[-1,-1,-2,-2.0,0.666667,150,150.0]";

            return std::make_pair(ret,
                                  str + (ret ? " == " : " != ") +
                                      "[-1,-1,-2,-2.0,0.666667,150,150.0]");
        });

    ts.addTest(
        "JsonExporter - nodeDataToJson() without scalers - non-split node",
        []() {
            typedef HoeffdingTree<Node<NodeData<float, 4, 3>>> Tree;
            typedef typename Tree::sample_count_t sample_count_t;

            Tree tree(1, 0.01, 0.05);
            bool doSplitTrial = false;
            const sample_count_t N_Samples = 150;

            for (sample_count_t i = 0; i < N_Samples; i++) {
                tree.train(irisDataset[i], irisDataset[i][4], doSplitTrial);
            }

            std::string str =
                JsonExporter::nodeDataToJson(tree.getRootNode(), 1, 2);

            bool ret = str == "[-1,-1,-2,-2.0,0.666667,150,150.0]";

            return std::make_pair(ret,
                                  str + (ret ? " == " : " != ") +
                                      "[-1,-1,-2,-2.0,0.666667,150,150.0]");
        });

    ts.addTest(
        "JsonExporter - nodeDataToJson() with scalers - non-split node", []() {
            typedef HoeffdingTree<Node<NodeData<float, 4, 3>>> Tree;
            typedef typename Tree::sample_count_t sample_count_t;

            Tree tree(1, 0.01, 0.05);
            bool doSplitTrial = false;
            const sample_count_t N_Samples = 150;

            for (sample_count_t i = 0; i < N_Samples; i++) {
                tree.train(irisDataset[i], irisDataset[i][4], doSplitTrial);
            }

            typedef Tree::data_t data_t;

            static const Tree::_DataClass::sampleScaler
                scalers[Tree::_DataClass::N_Attributes] = {
                    [](data_t a) { return a * 8; },
                    [](data_t a) { return a * 8; },
                    [](data_t a) { return a * 8; },
                    [](data_t a) { return a * 8; }};

            std::string str =
                JsonExporter::nodeDataToJson(tree.getRootNode(), 1, 2, scalers);

            bool ret = str == "[-1,-1,-2,-2.0,0.666667,150,150.0]";

            return std::make_pair(ret,
                                  str + (ret ? " == " : " != ") +
                                      "[-1,-1,-2,-2.0,0.666667,150,150.0]");
        });

    ts.addTest("JsonExporter - copyNode() and treeToJson()", []() {
        /*
        typedef HoeffdingTree<Node<NodeData<float, TypeChooser_Unsigned(4), 4,
                                            TypeChooser_Unsigned(3), 3>>>
            Tree;
        */

        typedef FixedTree Tree;

        typedef typename Tree::sample_count_t sample_count_t;

        Tree tree(1, 0.001, 0.05);
        bool doSplitTrial = true;
        const sample_count_t N_Samples = 150;

        for (sample_count_t i = 0; i < N_Samples; i++) {
            tree.train(fixedDataset[i], fixedDataset[i][4], doSplitTrial);
        }

        static const Tree::_DataClass::sampleScaler
            scalers[Tree::_DataClass::N_Attributes] = {scale, scale, scale,
                                                       scale};

        Tree treeCopy(tree.getR(), tree.getSigma(), tree.getTau());

        JsonExporter::copyNode(tree, treeCopy, tree.getRootNode(),
                               treeCopy.getRootNode());

        JsonExporter::inferDataset(treeCopy, fixedDataset, N_Samples);

        std::string result = JsonExporter::treeToJson(treeCopy, scalers);

        bool ret = result ==
                   "{\"classes_\":[0,1,2],\"feature_importances_\":[0,0,0,0],"
                   "\"max_features_\":4,\"meta\":\"decision-tree\",\"n_classes_"
                   "\":3,\"n_features_\":4,\"n_outputs_\":1,\"params\":{\"ccp_"
                   "alpha\": 0.0,\"class_weight\": null,\"criterion\": "
                   "\"gini\",\"max_depth\": null,\"max_features\": "
                   "null,\"max_leaf_nodes\": null,\"min_impurity_decrease\": "
                   "0.0,\"min_impurity_split\": null,\"min_samples_leaf\": "
                   "1,\"min_samples_split\": 2,\"min_weight_fraction_leaf\": "
                   "0.0,\"random_state\": null,\"splitter\": "
                   "\"best\"},\"tree_\":{\"max_depth\":1,\"node_count\":1,"
                   "\"nodes\":[[-1,-1,-2,-2.0,0.666667,150,150.0]],\"nodes_"
                   "dtype\":[\"<i8\",\"<i8\",\"<i8\",\"<f8\",\"<f8\",\"<i8\","
                   "\"<f8\"],\"values\":[[[50.0,50.0,50.0]]]}}";

        std::ofstream file("out.json");
        file << result;
        file.close();

        return std::make_pair(ret, ret ? "Sucessfull json string export"
                                       : "Resulting json string did not match");
    });

#endif

    return ts.runTestSuite(true, false);
}
