#include <iostream>

using namespace std;

/*
    从小到大的枚举使得每一个都是质因子
    n中最多包含一个大于sart(x)的质因子  
 */
void get_prime(int x) { 
    for(int i = 2; i <= x / i; i ++) {
        if(x % i == 0) {
            int s = 0;
            while(x%i==0) {
                s ++;
                x/=i; 
            } 
            cout << i << ' ' << s << endl;;
        } 
    }

    //最后一个质因子
    if(x > 1) cout << x << ' ' << 1 << endl; 
    puts("");
}

int 
main(void) {

    int n;
    cin >> n;
    while(n --) {
        int m;
        cin >> m;
        get_prime(m);
    }
    return 0;
}
