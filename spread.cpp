#include "spread.h"

int randomBetween(int lower, int upper) {
    return (rand() % (upper - lower + 1) + lower);
}

int randomIterate(int prev, int lower, int upper, int tolerance) {
    int next = randomBetween(lower, upper);
    while(abs(prev - next) > tolerance) {
        next = randomBetween(lower, upper);
    }
    return next;
}

int fixNumber(int num) {
    switch(num) {
    case(-78):
        num = 178;
        break;
    case(-79):
        num = 177;
        break;
    case(-80):
        num = 176;
        break;
    default:
        break;
    }
    return num;
}

spread::spread(unsigned int width, unsigned int height)
{
    vector<char> newLine;

    int nextTile = randomBetween(176, 178);

    for(unsigned int i = 0; i < width; i++) {
        newLine.push_back(static_cast<char>(nextTile));
        nextTile = fixNumber(randomIterate(nextTile, 176, 178, 1));
    }

    pixels[0] = newLine;
    newLine.clear();

    for(unsigned int y = 1; y < height; y++) {
        nextTile = fixNumber(randomIterate(fixNumber(pixels[y-1][0]), 176, 178, 1));
        newLine.push_back(static_cast<char>(nextTile));

        for(unsigned int x = 1; x < width; x++) {
            switch(abs(pixels[y-1][x] - newLine[x])) {
            case(2):
                nextTile = 177;
                break;
            case(1):
                nextTile = randomBetween(fixNumber(min(newLine[x-1], pixels[y-1][x])))
            }
        }
    }

    for(unsigned int i = 1; i < height; i++) {
        for(unsigned int i = 1; i < width; i++) {
            switch(abs(fixNumber(string1[i - 1] - string0[i]))) {
            case(2):
                nextTile = 177;
                break;
            case(1):
                nextTile = randomBetween(fixNumber(min(string1[i - 1], string0[i])), fixNumber(max(string1[i - 1], string0[i])));
                break;
            case(0):
                nextTile = fixNumber(randomIterate(fixNumber(string0[i]), 176, 178, 1));
                break;
            default:
                break;
            }
            string1.push_back(static_cast<char>(nextTile));
        }

        string1.append("\n");
        masterString.append(string1);
        string0 = string1;
        string1.clear();
    }
}

string randomPattern(unsigned int height, unsigned int width) {
    string masterString;
    string string0;
    string string1;

    string masterUnsmoothed = masterString;
    int I;

    for(unsigned int i = 1; i < masterString.size(); i++) {
        I = masterString[i];
        if(i % (width + 1) >= 2) {
            if(I == masterString[i + width] && I == masterString[i + width + 2] && I == masterString[i + 2 + (width * 2)] && masterString[i + width + 1] != I) {
                masterString[i + width + 1] = static_cast<char>(fixNumber(masterString[i]));
            }
            if(I == masterString[i + 1] && I == masterString[i + width] && I == masterString[i + width + 3] && I == masterString[i + 2 + (width * 2)] && I == masterString[i + 3 + (width * 2)]) {
                masterString[i + width + 1] = static_cast<char>(fixNumber(I));
                masterString[i + width + 2] = static_cast<char>(fixNumber(I));
            }
        }
    }

    masterString.append("Unsmoothed \n");
    masterString.append(masterUnsmoothed);
    masterUnsmoothed = "Smoothed \n"; //reusing variables, does not need to be masterUnsmoothed
    masterUnsmoothed.append(masterString);
    masterString = masterUnsmoothed;

    return masterString;
}

