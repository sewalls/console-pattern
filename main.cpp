#include "spread.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    string masterString = randomPattern(200, 200);
    cout << masterString << endl;
    return 0;
}
