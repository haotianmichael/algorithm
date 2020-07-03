#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/*
    单调栈
    理解贪心的本质  及其与DP的区别 
 
 */

int main(void)
{
    
    string num;
    int k;
    cin >> num >> k;
    string res = "0";
    for(unsigned i = 0; i < num.size(); i ++) {
        while(k && num[i] < res.back()) {
            res.pop_back();
            k --; 
        } 
        res += num[i];
    }

    while(k --) res.pop_back();
    unsigned i = 0;
    while(i < res.size() && res[i] == '0') i++;

    if(i == res.size()) puts("00");
    else cout << res.substr(i) << endl;

    return 0;
}
