#ifndef RING_NODE_H
#define RING_NODE_H

#include "iostream"
#include <utility>
using namespace std;

template<class Key, class Info>
struct Node{
    Key key;
    Info info;
    Node<Key, Info> *next;
    Node<Key, Info> *previous;

    Node(Key akey, Info ainfo) : key(akey), info(ainfo), next(nullptr), previous(nullptr) {}
    void print() const;
    bool operator==(const Node &rhs) const;
    bool operator!=(const Node &rhs) const;

};

template<class Key, class Info>
void Node<Key, Info>::print() const {
    cout<< "Key: " << key << ", Info: " << info << endl;
}

template<class Key, class Info>
bool Node<Key, Info>::operator==(const Node &rhs) const {
    return key == rhs.key &&
           info == rhs.info;
}

template<class Key, class Info>
bool Node<Key, Info>::operator!=(const Node &rhs) const {
    return key != rhs.key &&
           info != rhs.info;
}


#endif //RING_NODE_H
