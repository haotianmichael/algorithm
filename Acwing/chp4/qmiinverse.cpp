#include <iostream>

using namespace std;
typedef long long LL;


int qmi(int a, int b, int p) {

    LL res = 1;
    while(b) {
        if(b & 1)  res = res * a % p;
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
        int a, p;
        cin >> a >> p;
        if(a % p == 0)  cout << "impossible" << endl;
        else cout << qmi(a, p - 2, p) << endl; 
    }

    return 0;
}

