#include <iostream>
#include <algorithm>
#include <cstring>

/*
   排序不等式
   可能爆int
*/
using namespace std;
const int N =100010;
int a[N];


int main(void)
{
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) { 
        int x;
        cin >> x;
        a[i]  = x; 
    }

    sort(a, a + n); 

    int res = 0;
    for(int i = 0; i < n; i ++){
        res += a[i] * (n - i - 1); 
    }

    cout << res << endl;
    return 0;
}
