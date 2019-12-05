#include <iostream>
#include <algorithm>


using namespace std;
typedef long long LL;

int qmi(int a,int b, int p) {
    int res = 1;
    while(b) {
        if(b & 1) res = (LL)res * a %p;
        a = (LL)a * a % p; 
        b >>= 1;
    }
    return res;
}


int C(int a, int b, int p) {
    if(b > a) return 0;
    
    int res = 1;
    for(int i = 1, j = a; i <= b; i ++, j --) {
        res = (LL)res *j %p;
        res = (LL)res * qmi(i, p-2, p)%p; 
    }
        
    return res; 
}





int lucas(LL a, LL b, int p) {

    if(a <  p && b < p) return C(a, b, p);
    return (LL)C(a%p, b%p, p) * lucas(a/p, b/p, p)%p;

}

int 
main(void) {

    int n;
    cin >> n;
    while(n --) {
         
        LL a, b;
        int p;
        cin >> a >> b >> p;
        cout << lucas(a, b, p) << endl;
    }

    return 0;
}
