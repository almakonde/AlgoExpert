#include <bits/stdc++.h>
using namespace std;
 
float power(float x, int y)
{
    float temp;
    float res;
    if (y == 0)
        return 1;
    temp = power(x, y / 2);
    if (y % 2 == 0)
        
        return temp * temp;
    else {
        if (y > 0)
            return x * temp * temp;
        else
            res = (temp * temp) / x;
            return res;
    }
}
 
// Driver Code
int main()
{
    float x = 2;
    int y = -3;
    auto res = power(x, y);
 
    // Function call
    cout << res;
    return 0;
}