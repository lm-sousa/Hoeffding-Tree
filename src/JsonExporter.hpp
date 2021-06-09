#ifndef __JSON_EXPORTER_HPP__
#define __JSON_EXPORTER_HPP__

#include "Node.hpp"
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include <iostream>

class JsonExporter {
  public:
    JsonExporter() {}

    template <typename T> static std::string arrayToJson(T array[], uint size) {
        std::ostringstream ss;

        ss << arrayCharBegin << array[0];
        uint i = 1;

        while (i < size) {
            ss << arrayCharDelimiter << array[i++];
        }

        ss << arrayCharEnd;
        return ss.str();
    }

    template <typename T> static std::string vectorToJson(std::vector<T> v) {
        std::ostringstream ss;
        ss << arrayCharBegin;

        for (auto &elem : v) {
            ss << elem;
            if (v.back() != elem) {
                ss << arrayCharDelimiter;
            }
        }

        ss << arrayCharEnd;
        return ss.str();
    }

    template <typename T>
    static std::string mapToJson(std::map<std::string, T> map) {
        std::ostringstream ss;
        ss << objCharBegin;
        std::string lastKey = (--map.begin())->first;

        for (auto const &pair : map) {
            ss << "\"" << pair.first << "\":" << pair.second;
            if (lastKey.compare(pair.first)) {
                continue;
            }
            ss << objCharDelimiter;
        }

        ss << objCharEnd;
        return ss.str();
    }

    template <class T> static std::string treeToJson(T tree) {
        std::string str;
        return str;
    }

    template <class T> static std::string nodeToJson(T node) {
        std::string str;
        return str;
    }

    template <class T>
    static std::string nodeClassCountsToJson(T node, uint nClasses) {
        uint array[nClasses];

        for (uint i = 0; i < nClasses; i++) {
            array[i] = node->getData().getSampleCountPerClass(i);
        }

        const std::string intermediateArray[1] = {arrayToJson(array, nClasses)};
        return arrayToJson(intermediateArray, 1);
    }

    template <class T>
    static std::string nodeDataToJson(T *node, uint leftChildID,
                                      uint rightChildID) {

        typedef typename T::datatype datatype;

        const datatype array[7] = {
            node->hasLeftChild() ? datatype(leftChildID) : -1,
            node->hasRightChild() ? datatype(rightChildID) : -1,
            node->isSplit() ? datatype(node->getSplitAttributeIndex()) : -2,
            node->isSplit() ? node->getSplitValue() : -2,
            node->getData().getImpurity(),
            datatype(node->getData().getSampleCountTotal()),
            datatype(node->getData().getSampleCountTotal())};

        return arrayToJson(array, 7);
    }

    template <class T, class fn_T> static void DFS(T *node, fn_T function) {
        uint c = 0;
        _DFS_handle(node, function, c);
    }

  protected:
    static const char arrayCharBegin = '[';
    static const char arrayCharEnd = ']';
    static const char arrayCharDelimiter = ',';

    static const char objCharBegin = '{';
    static const char objCharEnd = '}';
    static const char objCharDelimiter = ',';

    template <class T, class fn_T>
    static void _DFS_handle(T *node, fn_T function, uint &nodeCounter) {

        std::cout << nodeCounter++ << std::endl;

        function(node);

        if (node->hasLeftChild()) {
            _DFS_handle(node->getLeftChild(), function, nodeCounter);
        }
        if (node->hasRightChild()) {
            _DFS_handle(node->getRightChild(), function, nodeCounter);
        }
    }
};

#endif
