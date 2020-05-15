#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int N = 10010;
bool st[N];
int primes[N];




//线性筛法
int get_primes(int x) {

    int cnt = 0;
    for(int i = 2; i <= x; i ++){
        if(!st[i])  primes[cnt ++] = i;
        for(int j = 0; primes[j] <= x/i; j ++){
            st[primes[j] * i] = true;       
            if(i % primes[j] == 0) break;  
        } 
    }


    return cnt;
}



int get(vector<int> num, int l, int r) {
    int res = 0;
    for(int i = l; i >= r; i --) res = res * 10 + num[i];
    return res;
}

int power10(int x) {
    int res = 1;
    while (x --) res *= 10;
    return res;
}

int countbits(int x, int n) {
    std::vector<int> v;

    while (n) {
        v.push_back(n % 10); 
        n /= 10;
    }

    n = v.size();
    int res = 0;
    for(int i = n - 1; i >= 0; i --){

        if (i <  n - 1) {
            res += get(v, n - 1, i + 1) * power10(i); 
            if(!x) res -= power10(i); 
        }

        if (v[i] == x) {
            res += get(v, i + 1, 0) + 1;
        } else if(v[i] > x){
            res += power10(i); 
        }
    }
    return res;
}


int test_main(void)
{

    int a, b;
    while (cin >> a >> b, a || b) {

        if(a > b) swap(a, b); 
        for(int i = 0; i <= 9; i ++) cout << countbits(b, i)  - countbits(a - 1, i) << ' ';
        puts("");
    }
    return 0;
}



long long f[N][N];
int n, m;
int main(void) 
{
    while (cin >> n >> m, n || m) {
        for(int i = 0; i < 1 << n; i++){
            int cnt = 0;
            st[i] = true;
            for(int j = 0; j < n; j ++)
                if(i >> j & 1)  {
                    if(cnt & 1) st[i] = false; 
                    cnt = 0;
                }else cnt ++;
        }        

        memset(f, 0, sizeof f);
        
    } 

    return 0;
}    


