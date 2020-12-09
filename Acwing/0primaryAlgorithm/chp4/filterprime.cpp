#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 100010;
bool st[N];
int primes[N];


/*
    体会数组st的使用  
    在图论算法中和数论中常见的判断数组st
*/
//朴素版本
int filter_prime_normal(int n) {
    int cnt = 0;
    for(int i = 2; i <= n; i++){
        if(!st[i]) primes[cnt ++] = i;
        for(int j = i; j <= n; j +=i)  st[j] = true;
    }
    return cnt;
}

//对朴素版本的优化
//从j = i开始比较好容易理解
int filter_prime_ai(int n) {

    int cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(!st[i]) { 
            primes[cnt ++] = i; 
            for(int j = i; j <= n; j += i) st[j] = true;
        }
    }
    return cnt;
}


//n只会被最小质因子筛掉  和从小到大枚举的性质是一样的
int filter_prime_linear(int n) {

    int cnt  = 0;
    for(int i = 2; i <= n; i ++) {
        if(!st[i])  primes[cnt++] = i;
        for(int j = 0; primes[j] <= n/i; j ++) {  //prime[j] * i <= n的意思
            st[primes[j] * i] = true;  
            if(i % primes[j] == 0) break;   //prime[cnt++] = i; 该句子的意思是到头了
        }
    }
    return cnt;
}  


int 
main(void) {

    int n;
    cin >> n;
    cout << filter_prime_normal(n) << endl;
    cout << filter_prime_ai(n) << endl;

    return 0;
}
