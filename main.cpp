#include <iostream>
#include <time.h>

using namespace std;

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

string randomPattern(unsigned int rows, unsigned int columns) {
    string masterString;
    string string0;
    string string1;

    int nextTile = randomBetween(176, 178);

    for(unsigned int i = 0; i < columns; i++) {
        string0.push_back(static_cast<char>(nextTile));
        nextTile = fixNumber(randomIterate(nextTile, 176, 178, 1));
    }

    string0.append("\n");
    masterString.append(string0);

    for(unsigned int i = 1; i < rows; i++) {
        nextTile = fixNumber(randomIterate(fixNumber(string0[0]), 176, 178, 1));
        string1.push_back(static_cast<char>(nextTile));
        for(unsigned int i = 1; i < columns; i++) {
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

    for(unsigned int i = 1; i < masterString.size(); i++) {
        if(i % (columns + 1) >= 2) {
            if(masterString[i] == masterString[i + columns] && masterString[i] == masterString[i + columns + 2] && masterString[i] == masterString[i + 2 + (columns * 2)] && masterString[i + columns + 1] != masterString[i]) {
                masterString[i + columns + 1] = static_cast<char>(fixNumber(masterString[i]));
            }
        }
    }

    return masterString;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    string masterString = randomPattern(100, 20);
    cout << masterString << endl;
    return 0;
}
