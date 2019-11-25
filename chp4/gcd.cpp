#include <iostream>

using namespace std;


//理解公式的由来   其中a 这b 的出现顺序
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int 
main(void) {

    int n;
    cin >> n;
    while(n --) {
        int a, b;
        cin >> a >> b;
        cout << gcd(a, b) << endl; 
    }
    return 0;
}
