#ifndef RING_SPLIT_H
#define RING_SPLIT_H

#include "Ring.h"

/*
 * IDEA: instead of rotating the flow manually by push_front, add first element to queue and then every ->previous
 * queue consist of proper ordered nodes which might create rotated Ring
 * */

template <typename Key, typename Info>
void split(const Ring<Key, Info>& source, int startIndex, int length, bool direction,
            Ring <Key, Info> & result1, int step1, bool direction1,
            Ring <Key, Info> & result2, int step2, bool direction2)
{
    Ring<Key, Info> src;
    if(!direction) // if direction is false, the stream need to rotate it flows
    {
        for(auto it = source.cbegin(); it != source.cend(); it++)
        {
            auto elem = *it;
            src.push_front(elem.key, elem.info);
        }
        auto end = *source.cend();
        src.push_front(end.key, end.info);
        src.move_backward(); // move backward is needed for proper order after rotating the flow
    }
    else src = source;
    int cnt = 0, c1 = 0, c2 = 0;
    auto it = src.cbegin();
    // finding the starting position
    while(cnt != startIndex)
    {
        cnt++;
        it++;
    }
    cnt = 0;
    while(cnt < length)
    {
        fill_ring(result1, it, cnt, c1, step1, length, direction1);
        if(cnt == length) break;
        fill_ring(result2, it, cnt, c2, step2, length, direction2);
        if(cnt == length) break;
    }
    if(!direction1) result1.move_backward();
    if(!direction2) result2.move_backward();

}

template<class Key, class Info>
void fill_ring(Ring <Key, Info>& result1, constRingIterator<Key, Info> &it, int &cnt, int&cx, int step, int length, bool dir)
{
    cx=0;
    while(cx != step && cnt != length)
    {
        auto elem = *it;
        if(dir) result1.push_back(elem.key, elem.info);
        else result1.push_front(elem.key, elem.info);
        cx++;
        cnt++;
        it++;
    }

}

#endif //RING_SPLIT_H