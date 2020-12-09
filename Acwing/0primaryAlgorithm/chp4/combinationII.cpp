#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100010, mod = 1e9 + 7;
int fact[N], infact[N];
typedef long long LL;

LL qmi(int a, int b, int p) {

    LL res= 1;
    while(b) {
        if(b & 1) res = res * a % p;
        a = (LL) a * a % p; 
        b >>= 1;
    } 

    return res;
}



void init() {
    fact[0] = infact[0] = 1;

    for(int i = 1; i < N; i ++) {
        fact[i]  = (LL)fact[i-1] * i % mod;  
        infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2, mod) % mod;
    }

}




int 
main(void) {

    int n;
    cin >> n;
    init();
    while(n --) {
        int a, b;
        cin >> a >> b;
        cout << (LL)fact[a] * infact[a - b] %mod * infact[b] % mod;
    }

    return 0;
}

