#ifndef __JSON_EXPORTER_HPP__
#define __JSON_EXPORTER_HPP__

#include "Node.hpp"
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class JsonExporter {
  public:
    JsonExporter() {}

    template <class T = Node<>> static void DFS(T *origin, void (*function)()) {
        T *_node = origin;
        T *_parent = origin;
        do {
            while (_node->hasLeftChild()) {
                _parent = _node;
                _node = _node->getLeftChild();
            }
            while (_node->hasRightChild()) {
                _parent = _node;
                _node = _node->getRightChild();
            }
            (*function)(_node);
            _node = _parent;
            _parent = _node->getParent();
        } while (_node != origin || _node->hasRightChild());
    }
};

#endif
