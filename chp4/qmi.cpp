#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;

LL qmi(int a, int b, int p) {
    LL res = 1;
    while(b) {
        if(b >> 1)  res = res * a % p;
        a = a * (LL)a % p;
        b >>= 1; 
    }

    return res;
}

int 
main(void) {

    int n;
    cin >> n;
    while(n --) {
        int a, b, p;
        cin >> a >> b >> p;

        cout << qmi(a, b, p) << endl;  
    }
    return 0;
}
