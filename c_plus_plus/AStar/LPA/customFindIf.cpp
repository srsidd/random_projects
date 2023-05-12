#include <iostream>
#include <stdint.h>
#include <fstream>
#include <list>
#include <algorithm>
#include <stdio.h>

struct S
{
    int S1;
    int S2;
};

using namespace std;

int main()
{
    std::vector<S> l;
    S s1;
    s1.S1 = 0;
    s1.S2 = 0;
    S s2;
    s2.S1 = 1;
    s2.S2 = 1;
    S s3;
    s3.S1 = 100;
    s3.S2 = 100;

    int value = 100;

    l.push_back(s1);
    l.push_back(s2);
    l.push_back(s3);

    vector<S>::iterator it = find_if(l.begin(), l.end(), [&value] (S s) { return s.S1 == value; } );
    S result,result2; 
    result = *it;

    cout<<result.S1;

   // result2 = l.at(it-l.begin());
    cout<<"\n"<<it-l.begin();

    getchar();

    
}