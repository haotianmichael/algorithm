#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

/* 2. 不修改数组找出重复的数字*/

const int N = 100010;
int a[N], n;


int main(void)
{

    cin >> n;
    for(int i =0 ; i < n; i++)cin >> a[i];


    int l = 1,  r = n- 1;
    while(l < r) {
        int mid = (l  + r) >> 1;  //[l, mid] [mid + 1, r]
        int s = 0;
        for(auto x : a) s += x>=l && x<=mid;  
        if(s > mid - l + 1) r = mid;
        else l = mid + 1;
    }
    cout << r << endl;
    return 0;
}
