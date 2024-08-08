#include "../inc/DynamicProgramming.h"
#include <iostream>
using namespace std;

int main()
{
    Solution *s = new Solution();
    vector<int> cost = {10, 15, 20};
    int result = s->integerBreak(10);
    cout << result;
}