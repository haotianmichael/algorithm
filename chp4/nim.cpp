#include <iostream>


using namespace std;
/*
    ^是位运算！！！
    理解上有偏差 
*/

int 
main(void) {

    int n, res = 0;
    cin >> n;
    while(n --) {
        int t;
        cin >> t;
        res ^= t;
    }

    if(res) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}
