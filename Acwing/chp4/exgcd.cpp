#include <iostream>

using namespace std;
typedef  long long LL;

int gcd(int a, int b) {
    return (b ? gcd(b, a % b) : a); 
}

int exgcd(int a, int b, int &x, int &y) {
    if(!b) {
        x = 1, y = 0;
        return a; 
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;        
}

//求线性同余方程
int exgcdII(int a, int b, int &x, int &y) {
    if(!b)
    {
        x = 1, y = 0;
        return a; 
    }

    int d = exgcdII(b, a % b, y, x);
    y -= a / b * x;
    return d;
}


int test_exgcdII(void) {

    int n;
    cin >> n;
    while(n --){
        int a, b, m, x, y;
        cin >> a >> b >> m;

        int d = exgcdII(a, m, x, y);
        if(b%d) cout << "impossible" << endl;
        else cout << (LL)x*(b/d)%m << endl;

    }
    return 0;
}

int 
main(void) {

    int n;
    cin >> n;
    while(n --) {
        int a, b, x, y;
        cin >> a >> b;
        exgcd(a, b, x, y); 
        cout << x << ' ' << y << endl;
    }

    return 0;
}
