/*
    Longest Increasing Subsequence 
*/
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 10010;
int a[N];
int f[N];
int n;


int 
main(void) {

    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> a[i];


    for(int i = 1; i <= n; i ++) {
        f[i] = 1;   //只有a[i]一个数
        for(int j = 1; j < i; j ++) 
            if(a[j] < a[i]) 
                f[i] = max(f[i], f[j] + 1); 
            
    }

    int res = 0;
    for(int  i = 1; i <= n; i ++)
        res = max(res, f[i]);

    cout << res;

    return 0;
}
