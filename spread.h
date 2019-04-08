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

    vector<vector<char>> pixels;
};

#endif // SPREAD_H
