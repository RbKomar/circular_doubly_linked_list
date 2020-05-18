#ifndef RING_Ring_H
#define RING_Ring_H

#include "RingIterator.h"
#include <iostream>
#include <assert.h>


using namespace std;

// overloading operator<< for pairs needed for heuristical testing of front() and back() methods
template<class Key, class Info>
std::ostream& operator<<(std::ostream& stream, const pair<Key, Info>& pair)
{
    stream <<"Key: "<< pair.first << ", Info: " << pair.second;
    return stream;
}

/*
 * REMARK: since it is a ring class iterator doesn't have the classic end() pointer thus after every loop using iterator
 * last element should be called explicitly.
 * */

template<typename Key, typename Info>
class Ring{
private:
    typedef constRingIterator<Key, Info> const_iter;
    typedef RingIterator<Key, Info> iter;
    typedef Node<Key, Info> node;

    void set_length(int x) {size = x;} // setting the length to a specific value
    void update_length(int x) {size += x;} // updates the length of the ring

    iter begin(); // returns an iterator pointing to a last element of a ring
    iter end();  // returns an iterator pointing to a last element of a ring
    iter search_inside(const Key&, int ); // returns an iterator pointing to a searched element / nullptr if not found

public:

    Ring() : head(nullptr), tail(nullptr), size(0){};
    ~Ring();

    void copy_all_elements(const Ring&);

    Ring& operator=(const Ring &); // overloading operator=
    Ring operator+(const Ring &); // overloading operator+
    void operator+=(const Ring &); // overloading operator+=

    bool is_empty() const; // returns true if the ring is empty
    void clear(); // clears the list
    void print() const; // printing the elements of the ring
    int length() const; // returns number of elements in ring
    int occurrence(const Key&) const; // returns the number of how many specific key appeared in the ring


    pair<Key, Info> front() const; // returns the pair of values of first node
    pair<Key, Info> back() const; // returns the pair of values of last node

    void push_back(const Key&, const Info&); // adding the node as the last in the ring
    void push_front(const Key&, const Info&); // adding the node as the first in the ring
    void insert(const Key &, const Info &, const Key &, int ); // inserting the node after specific key
    void remove(const Key&, int ); // removing specific node
    Ring<Key, Info> reverse(); // returns reversed ring

    Ring<Key, Info> sub_ring(const Key&, int , const Key&, int );

    const_iter cbegin() const; // returns a constant iterator pointing to a first element of a ring
    const_iter cend() const; // returns a constant iterator pointing to a last element of a ring
    const_iter search(const Key&, int) const; // returns a constant iterator pointing to a searched element / nullptr if not found

    void move_backward();
    void move_frontward();

private:
    int size;
    node *head;
    node *tail;

};

template<typename Key, typename Info>
RingIterator<Key,Info> Ring<Key, Info>::begin() {
    return RingIterator(head);
}

template<typename Key, typename Info>
RingIterator<Key,Info> Ring<Key, Info>::end() {
    return RingIterator(tail);
}

template<typename Key, typename Info>
constRingIterator<Key,Info> Ring<Key, Info>::cbegin() const {
    return constRingIterator(head);
}

template<typename Key, typename Info>
constRingIterator<Key,Info> Ring<Key, Info>::cend() const {
    return constRingIterator(tail);
}

template<typename Key, typename Info>
pair<Key, Info> Ring<Key, Info>::front() const {
    assert(head != nullptr);
    return make_pair(head->key, head->info);
}

template<typename Key, typename Info>
pair<Key, Info> Ring<Key, Info>::back() const {
    assert(head->previous != nullptr);
    return make_pair(head->previous->key, head->previous->info);
}

template<typename Key, typename Info>
void Ring<Key, Info>::copy_all_elements(const Ring &x)  {
    for(auto it= x.cbegin(); it != x.cend(); ++it)
    {
        auto nta = *it; // node to add
        push_back(nta.key, nta.info);
    }
    auto end = *(x.cend());
    push_back(end.key, end.info);
}

template<typename Key, typename Info>
Ring<Key, Info> &Ring<Key, Info>::operator=(const Ring &x) {
    clear();
    copy_all_elements(x);
    size = x.length();
    return *this;
}

template<typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::operator+(const Ring &rhs) {
    Ring<Key, Info> n_ring;
    n_ring.clear();
    n_ring.copy_all_elements(*this);
    n_ring.copy_all_elements(rhs);
    n_ring.set_length(size + rhs.length());
    return n_ring;
}

template<typename Key, typename Info>
void Ring<Key, Info>::operator+=(const Ring &rhs) {
    copy_all_elements(rhs);
    update_length(rhs.length());
}

template<typename Key, typename Info>
void Ring<Key, Info>::push_back(const Key & akey, const Info &ainfo) {
    node *n = new node(akey, ainfo);
    if(head == tail && head == nullptr) {
        head = tail = n;
        head->next = tail->next = nullptr;
        head->previous = tail->previous = nullptr;
    }
    else{
        tail->next = n;
        n->previous = tail;
        tail = n;
        head->previous = tail;
        tail->next = head;
    }
    size++;
}

template<typename Key, typename Info>
void Ring<Key, Info>::push_front(const Key &akey, const Info &ainfo) {
    node *n = new node(akey, ainfo);
    if(head == tail && head == nullptr) {
        head = tail = n;
        head->next = tail->next = nullptr;
        head->previous = tail->previous = nullptr;
    }
    else{
        n->next = head;
        head->previous = n;
        head = n;
        head->previous = tail;
        tail->next = head;
    }
    size++;
}

template<typename Key, typename Info>
void Ring<Key, Info>::insert(const Key &akey, const Info &ainfo, const Key &where, int pos) {
    if(is_empty())
    {
        cout<<"Ring is empty";
        return;
    }
    auto found = search_inside(where, pos).get();

    if(found != nullptr){
        node *n = new node(akey, ainfo);
        n->next = found->next;
        n->previous = found;
        found->next = n;
        if(found == tail) {
            n->next = head;
            head->previous = n;
            tail = n;
        }
        size++;
    }else cout<<"Such item doesn't exist."<<endl;
}

template<typename Key, typename Info>
RingIterator<Key,Info> Ring<Key, Info>::search_inside(const Key &where, int pos) {
    int c = 0; // holing numbers of key repetitions
    if(head==tail && head == nullptr){
        cout<<"Empty list, nothing to search_inside"<<endl;
    }else
        {
            for (auto it = begin(); it != end(); ++it)
            {
                if( (*it).key == where){
                    c++;
                    if(c == pos)
                    {
                        return Ring::iter(it);
                    }
                }
            }
            if((*end()).key == where){
                c++;
                if(c == pos){
                    return end();
                }
            }
        }
    return Ring::iter();
}

template<typename Key, typename Info>
constRingIterator<Key,Info> Ring<Key, Info>::search(const Key &where, int pos) const {
    int c = 0; // holing numbers of key repetitions
    if(size == 0)
    {
        cout<<"Empty list, nothing to search_inside"<<endl;
    }else
    {
        for (auto it = cbegin(); it != cend(); ++it)
        {
            if( (*it).key == where){
                c++;
                if(c == pos)
                {
                    return Ring::const_iter(it);
                }
            }
        }
        if((*cend()).key == where){
            c++;
            if(c == pos){
                return cend();
            }
        }
    }
    return Ring::const_iter();
}

template<typename Key, typename Info>
void Ring<Key, Info>::remove(const Key &where, int pos) {
    auto found = search_inside(where, pos).get();
    if (found != nullptr)
    {
        if(size==1){
            clear();
            return;
        }
        found->previous->next = found->next;
        found->next->previous = found->previous;
        if(found == head) head = found->next;
        if(found == tail) tail = found->previous;
        delete found;
        size--;
    }else{
        cout<< "Such Item doesn't exists"<<endl;
    }
}

template<typename Key, typename Info>
Ring<Key, Info>::~Ring() {
    clear();
}

template<typename Key, typename Info>
bool Ring<Key, Info>::is_empty() const {
    return (size == 0);
}

template<typename Key, typename Info>
int Ring<Key, Info>::length() const {
    return size;
}

template<typename Key, typename Info>
void Ring<Key, Info>::print() const {
    if(is_empty()){
        cout<< "Empty Ring"<<endl;
        return;
    }
    for (auto it = cbegin(); it != cend(); it++) {
        (*it).print();
    }
    (*cend()).print();
}

template<typename Key, typename Info>
void Ring<Key, Info>::clear() {
    auto it = begin();
    while(it.hasNext()){
        auto tmp = it.get();
        it++;
        delete tmp;
    }
    head = tail = nullptr;
    size = 0;
}

template<typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::reverse() {
    Ring<Key, Info> n_ring;
    for(auto it=end(); it != begin(); it--)
    {
        n_ring.push_back((*it).key, (*it).info);
    }
    n_ring.push_back((*begin()).key, (*begin()).info);
    return n_ring;
}

template<typename Key, typename Info>
int Ring<Key, Info>::occurrence(const Key &akey) const {
    int oc = 0; // occurrence counter
    for (auto it = cbegin(); it != cend(); ++it)
    {
        if((*it).key == akey) oc++;
    }
    if((*cend()).key == akey) oc++;
    return oc;
}

template<typename Key, typename Info>
void Ring<Key, Info>::move_backward() {
    if(size == 0) return;
    else
    {
        head = tail;
        tail = tail->previous;
    }
}

template<typename Key, typename Info>
void Ring<Key, Info>::move_frontward() {
    if(size == 0) return;
    else
    {
        tail = head;
        head = head->next;
    }
}

template<typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::sub_ring(const Key &skey, int spos, const Key &ekey, int epos) {

    int scnt =0, ecnt =0;
    Ring<Key, Info> subRing;
    bool create = false;

    if(occurrence(skey) < spos)
        throw std::out_of_range("Not enough start key's to create subsequence");
    if(occurrence(ekey) < epos)
        throw std::out_of_range("Not enough end key's to create subsequence");

    for (auto it = begin(); it != end() ; ++it)
    {
        auto elem = (*it);

        if(elem.key == skey)
        {
            scnt++;
            if(scnt == spos) create = true;
        }

        if(create) subRing.push_back(elem.key, elem.info);

        if(elem.key == ekey)
        {
            ecnt++;
            if(ecnt == epos) return subRing;
        }
    }
    subRing.push_back((*end()).key, (*end()).info);
    return subRing;
}

#endif //RING_Ring_H