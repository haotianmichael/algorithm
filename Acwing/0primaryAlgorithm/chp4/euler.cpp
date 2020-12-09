#include<iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;
const int N = 1000010;

int primes[N], cnt;
int euler[N];
int phi[N];
bool st[N];

//注意会爆int
void get_eulers(int n) {
    euler[1] = 1;


    for(int i = 2; i <= n; i ++) {
        if(!st[i]) {
            primes[cnt++]  = i;
            euler[i] = i - 1; 
        } 
        for(int j = 0; primes[j] <= n; j ++) {
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0) {
                euler[t] = euler[i] * primes[j]; 
                break; 
            } 
            euler[t] = euler[i] * (primes[j] - 1);
        } 
    }
}


LL acwing_geteuler(int n) {
        phi[1] = 1;

        int cnt = 0;
        LL res = 0;
        for(int i = 2; i <= n; i++) {
            if(!st[i])  {
                primes[cnt ++] = i;
                phi[i] = i - 1; 
            }
            //关键是理解线性筛法中的最小质因子
            for(int j = 0; primes[j] <= n/i;j ++) {
                st[primes[j] * i]  = true;
                if(i % primes[j] == 0) {
                    phi[primes[j] * i] = primes[j] * phi[i];
                    break;
                }else {
                    phi[primes[j] * i] = (primes[j] - 1) * phi[i]; 
                } 
            }
        }

        for(int i = 1; i<= n; i++) res += phi[i];
        return res;
 }

int 
main(void) {

    int n;
    cin >> n;

    get_eulers(n);

    LL res = 0;
    for(int i = 1; i <= n; i++) res += euler[i];
    cout << res << endl;
    return 0;
}

//欧拉函数
int 
test_euler_main(void) {
    int n;
    cin >> n;

    while(n--) {
        int a;
        cin >> a;
        
        int res = a;
        for(int i = 2; i <= a/i; i ++)   
            if(a%i == 0) {
                res = res / i * (i - 1); 
                while(a%i==0) a/=i;
            }
        if(a > 1) res = res / a * (a - 1);
        cout << res << endl;
    }
    return 0;
}
