#include "spread.h"

char randomCharBetween(int lower, int upper) {
    return static_cast<char>((rand() % (upper - lower + 1) + lower));
}

char randomIterateChar(int prev, int lower, int upper, int tolerance) {
    char next = randomCharBetween(lower, upper);
    while(abs(prev - next) > tolerance) {
        next = randomCharBetween(lower, upper);
    }
    return next;
}

spread::spread(unsigned int width, unsigned int height)
{
    vector<char> newLine;
    char nextTile = randomCharBetween(-80, -78);

    for(unsigned int i = 0; i < width; i++) {
        newLine.push_back(nextTile);
        nextTile = randomIterateChar(nextTile, -80, -78, 1);
    }

    pixels.push_back(newLine);
    newLine.clear();

    for(unsigned int y = 1; y < height; y++) {
        nextTile = randomIterateChar(pixels[y-1][0], -80, -78, 1);
        newLine.push_back(nextTile);

        for(unsigned int x = 1; x < width; x++) {
            switch(abs(pixels[y-1][x] - newLine[x-1])) {
            case(2):
                nextTile = -79;
                break;
            case(1):
                nextTile = randomCharBetween(min(newLine[x-1], pixels[y-1][x]), max(newLine[x-1], pixels[y-1][x]));
                break;
            case(0):
                nextTile = randomIterateChar(pixels[y-1][x], -78, -80, 1);
                break;
            }
            newLine.push_back(nextTile);
        }

        pixels.push_back(newLine);
        newLine.clear();
    }
}

string spread::toString() {
    string output;
    for(unsigned int y = 0; y < pixels.size(); y++) {
        for(unsigned int x = 0; x < pixels[y].size(); x++) {
            output.push_back(pixels[y][x]);
        }
        output.append("\n");
    }
    return output;
}

char spread::at(unsigned int x, unsigned int y) {
    return pixels[y][x];
}

void spread::set(unsigned int x, unsigned int y, char graph) {
    pixels[y][x] = graph;
}

void spread::dilate() {
    for(unsigned int y = 1; y < pixels.size() - 1; y++) {
        for(unsigned int x = 1; x < pixels[y].size() - 1; x++) {
            if(at(x, y-1) == at(x-1,y) == at(x+1, y) == at(x, y+1) != at(x, y)) {
                set(x, y, at(x, y-1));
            }
        }
    }
}
