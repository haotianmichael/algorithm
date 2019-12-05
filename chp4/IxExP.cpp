/*
   容斥原理
   Inclusion-exclusion principle
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 20;
typedef long long LL;
int p[N];
int n, m;



int 
main(void) {
    cin >> n >> m;
    for(int i = 0; i < m; i ++) cin >> p[i];

    int res = 0;
    //位运算的开始方式 
    for(int i = 1; i < 1 << m; i++) {
          
        int cnt = 0, t = 1;
        for(int j = 0; j < m; j ++)  {
            if(i >> j & 1)  {
                cnt++;
                if(static_cast<LL>(t) * p[j] > n) { //类型强转置换的C++语法
                    t = -1;
                    break;
                }           
                t *= p[j];
            }
        }
            
        
        if(t != -1) {
            if(cnt % 2) res += n/t;
            else res -= n/t;            
        }
    }

    cout << res << endl; 

    return 0;
}

