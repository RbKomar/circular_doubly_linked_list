#ifndef RING_constRINGITERATOR_H
#define RING_constRINGITERATOR_H
#include "Node.h"


template<class Key, class Info>
class constRingIterator {
    typedef Node<Key, Info> node;

protected:
    node *current;

public:
    constRingIterator(); // default constructor
    explicit constRingIterator(Node<Key, Info> *ptr); // constructor with a parameter

    const node operator*() const {return *current;} // function to overload the dereferencing operator
    const node* get() const {return current;}

    constRingIterator<Key, Info>& operator++(); // overload preincrement operator
    constRingIterator<Key, Info>& operator--(); // overload predecrement operator
    constRingIterator<Key, Info> operator++(int); // overload postincrement operator
    constRingIterator<Key, Info> operator--(int); // overload postdecrement operator

    bool operator==(const constRingIterator &rhs) const; // overload the equality operator
    bool operator!=(const constRingIterator &rhs) const; // overload the 'not equal' operator
    void set(Node<Key, Info> *n) {current = n;}
    bool hasNext();
};

template<class Key, class Info>
constRingIterator<Key, Info>::constRingIterator(): current(nullptr) {}


template<class Key, class Info>
constRingIterator<Key, Info>::constRingIterator(Node<Key, Info> *ptr): current(ptr) {}

template<class Key, class Info>
bool constRingIterator<Key, Info>::operator==(const constRingIterator &rhs) const {
    return (current == rhs.current);
}

template<class Key, class Info>
bool constRingIterator<Key, Info>::operator!=(const constRingIterator &rhs) const {
    return (current != rhs.current);
}

template<class Key, class Info>
constRingIterator<Key, Info>& constRingIterator<Key, Info>::operator++() {
    current = current->next;
    return *this;
}

template<class Key, class Info>
constRingIterator<Key, Info>& constRingIterator<Key, Info>::operator--() {
    current = current->previous;
    return *this;
}

template<class Key, class Info>
 constRingIterator<Key, Info> constRingIterator<Key, Info>::operator++(int) {
    constRingIterator it(*this);
    current = current->next;
    return it;
}

template<class Key, class Info>
 constRingIterator<Key, Info> constRingIterator<Key, Info>::operator--(int) {
    constRingIterator it(*this);
    current = current->next;
    return it;
}

template<class Key, class Info>
bool constRingIterator<Key, Info>::hasNext() {
    if(current == nullptr) return false;
    return (current->next != nullptr);
}


template<class Key, class Info>
class RingIterator : protected constRingIterator<Key, Info>{
private:
    typedef Node<Key,Info> node;
    node *current;

public:
    RingIterator () : current(nullptr) {}
    explicit RingIterator (node *n ) : current(n) {};
    using constRingIterator<Key, Info>::set;
    using constRingIterator<Key, Info>::hasNext;
    bool operator==(const RingIterator &rhs) const; // overload the equality operator
    bool operator!=(const RingIterator &rhs) const; // overload the 'not equal' operator
    RingIterator<Key, Info>& operator++(); // overload preincrement operator
    RingIterator<Key, Info> operator++(int); // overload preincrement operator
    RingIterator<Key, Info>& operator--(); // overload predecrement operator
    RingIterator<Key, Info> operator--(int); // overload predecrement operator
    node operator*() {return *current;}
    node* get() {return current;}

};

template<class Key, class Info>
bool RingIterator<Key, Info>::operator==(const RingIterator &rhs) const {
    return (current == rhs.current);
}

template<class Key, class Info>
bool RingIterator<Key, Info>::operator!=(const RingIterator &rhs) const {
    return (current != rhs.current);
}

template<class Key, class Info>
RingIterator<Key, Info>& RingIterator<Key, Info>::operator++() {
    current = current->next;
    return *this;
}

template<class Key, class Info>
RingIterator<Key, Info>& RingIterator<Key, Info>::operator--() {
    current = current->previous;
    return *this;
}

template<class Key, class Info>
RingIterator<Key, Info> RingIterator<Key, Info>::operator++(int) {
    RingIterator it(*this);
    current = current->next;
    return it;
}

template<class Key, class Info>
RingIterator<Key, Info> RingIterator<Key, Info>::operator--(int) {
    RingIterator it(*this);
    current = current->previous;
    return it;
}

#endif //RING_constRINGITERATOR_H
