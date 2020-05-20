#ifndef RING_TESTS_H
#define RING_TESTS_H

#include "Ring.h"
#include "Split.h"
#include<vector>

void inserting_test()
{
    vector<string> ans = {"push_front", "push_back", "insert"};
    bool passed = true;
    Ring<int, string> ring;
    ring.push_back(1, "push_back");
    ring.push_back(2, "push_back");
    ring.push_back(3, "push_back");
    ring.push_front(-1, "push_front");
    ring.push_front(-2, "push_front");
    ring.push_front(-3, "push_front");
    ring.insert(0, "insert", -1, 1);
    int c = 0;
    for (auto it = ring.cbegin(); it != ring.cend() ; ++it, ++c)
    {
        if(c<=2) passed &= (*it).info == ans[0];
        else if(c==3) passed &= ((*it).info == ans[2]);
        else if(c>3) passed &= ((*it).info == ans[1]);
    }
    passed &= ((*ring.cend()).info == ans[1]);
    if(passed) cout<< "INSERTING TEST PASSED"<<endl;
    else cout<< "INSERTING TEST NOT PASSED"<<endl;
}

void reversing_test()
{
    vector<string> ans = {"3", "2", "1"};
    bool passed = true;

    Ring<int, string> ring;
    ring.push_back(1, "1");
    ring.push_back(1, "2");
    ring.push_back(1, "3");

    ring = ring.reverse();

    int c =0;
    for (auto it = ring.cbegin(); it != ring.cend() ; ++it, c++)
    {
        auto elem = *it;
        passed &= (elem.info == ans[c]);
    }
    passed &= ((*ring.cend()).info == ans[2]);

    if(passed) cout<< "REVERSING TEST PASSED"<<endl;
    else cout<< "REVERSING TEST NOT PASSED"<<endl;


}

void operators_test()
{
    vector<string> ans = {"ring", "ring2", "ring3"};
    bool passed = true;
    Ring<int, string> ring;
    Ring<int, string> ring2;
    Ring<int, string> ring3;
    ring2.push_back(1, "ring2");
    ring2.push_back(2, "ring2");
    ring2.push_back(3, "ring2");
    ring.push_front(3, "ring");
    ring.push_front(2, "ring");
    ring.push_front(1, "ring");
    ring3.push_back(0, "ring3");

    ring += ring3;
    ring = ring + ring2;

    int c = 0;
    for (auto it = ring.cbegin(); it != ring.cend() ; ++it, ++c)
    {
        if(c<=2) passed &= (*it).info == ans[0];
        else if(c==3) passed &= ((*it).info == ans[2]);
        else if(c>3) passed &= ((*it).info == ans[1]);
    }
    passed &= ((*ring.cend()).info == ans[1]);
    if(passed) cout<< "OPERATORS TEST PASSED"<<endl;
    else cout<< "OPERATORS TEST NOT PASSED"<<endl;
}

void removing_test(){
    bool passed = true;
    Ring<int, int> ring;
    ring.push_back(1,1);
    ring.push_back(2,2);
    ring.push_back(3,3);
    ring.push_front(3,3);

    ring.remove(3, 2);
    passed &= ((*(ring.cend())).info == 2);
    passed &= (ring.length() == 3);
    ring.remove(3, 1);
    passed &= ((*(ring.cbegin())).info == 1);
    passed &= (ring.length() == 2);

    ring.clear();
    passed &= ring.is_empty();

    if(passed) cout<< "REMOVING TEST PASSED"<<endl;
    else cout<< "REMOVING TEST NOT PASSED"<<endl;
}

void subring_test()
{
    vector<int> ans = {3,4,5,6,7,8,9,10};
    bool passed = true;

    Ring<int, int> ring;
    for (int i = 1; i < 10; ++i) {
        ring.push_back(i, i);
    }
    ring.push_back(1, 10);

    Ring<int, int> sub_ring = ring.sub_ring(3, 1, 1, 1);
    auto it = sub_ring.cbegin();

    for(int i= 0; it != sub_ring.cend(); ++it, ++i) {
        auto elem = *it;
        passed &= (elem.info == ans[i]);
    }

    passed &= ((*sub_ring.cend()).info == ans[7]);

    if(passed) cout<< "SUB_RING TEST PASSED"<<endl;
    else cout<< "SUB_RING TEST NOT PASSED"<<endl;

}

void split_test()
{
    Ring<int, int> ring1, ring2;
    Ring<int, int> source;

    bool passed = true;
    vector<int> ans1 = {3,4,5,8,9,0,3,4,5,8};
    vector<int> ans2 = {6,7,6,2,1,7};

    for (int i = 1; i < 10; ++i) {
        source.push_back(i, i);
    }
    source.push_back(10, 0);

    split(source, 2, 16, true,
          ring1, 3, true,
          ring2, 2, false);
    auto it1 = ring1.cbegin();
    auto it2 = ring2.cbegin();

    for(int i= 0; it1 != ring1.cend(); ++it1, ++i) {
        auto elem = *it1;
        passed &= (elem.info == ans1[i]);
    }
    passed &= ((*ring1.cend()).info == ans1[9]);
    for(int j= 0; it2 != ring2.cend(); ++it2, ++j) {
        auto elem = *it2;
        passed &= (elem.info == ans2[j]);
    }
    passed &= ((*ring2.cend()).info == ans2[5]);

    if(passed) cout<< "SPLIT TEST PASSED"<<endl;
    else cout<< "SPLIT TEST NOT PASSED"<<endl;

}

#endif //RING_TESTS_H
