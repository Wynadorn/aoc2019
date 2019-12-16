#include <vector>
using namespace std;

int main(void)  
{
    vector<int> test;
    test.push_back(5);
    test[0] = 1;
    test[1] = 3;
    test[5] = 6;
    test[76499] = 4;
    test[76500] = 5;
    return 0;
}
