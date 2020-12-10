#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;


/*  1. 找出数组中重复的数字 */

const int N  = 100010;
int a[N];
int n;

int main(void)
{
    cin >> n;
    for(int i = 0;i < n; i ++) cin >> a[i];

    //===
    for(auto e : a) 
        if(e>=n || e<0)
            return -1;


    for(int i = 0; i < n; i ++) {
        while(i != a[i] && a[a[i]] != a[i]) swap(a[i], a[a[i]]);
        if(i != a[i] && a[a[i]] == a[i]) return a[i];
    } 

    return 0;
}
