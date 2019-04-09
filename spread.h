#ifndef SPREAD_H
#define SPREAD_H

#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

class spread
{
public:
    spread(unsigned int width, unsigned int height);
    string toString();
    char at(unsigned int x, unsigned int y);
    void set(unsigned int x, unsigned int y, char graph);
    void dilate();

    vector<vector<char>> pixels;
};

#endif // SPREAD_H
