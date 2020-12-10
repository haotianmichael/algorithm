#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/* 4. 替换空格*/


int main(void)
{
    string res, ans;
    cin >> res;
    for(auto x : res)
        if(x == ' ')
            ans += "%20";
        else 
            ans += x;

    cout << ans << endl;
    return 0;
}
