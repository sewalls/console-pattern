#include "spread.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    spread newSpread(5, 5);
    //newSpread.dilate();
    cout << newSpread.toString() << endl;
    return 0;
}
