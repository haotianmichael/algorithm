#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int  N = 110;
/*
   const int N = 25000, M = 2010;    优化版本的数据集
    之所以开成25000的数组是因为    s[i]最多是2000   因此每一个s[i]最多开成log2000 = 12左右而共有1000类物品
    因此2000*log2000 <= 25000
*/
int v[N], w[N], s[N];
int n, m;


/*
   多重背包朴素版本
   状态转移方程: f[i][j] =  max(f[i-1][j-v[i] * k] + w[i] * k);  (k <= s[i])
*/
void testIII() {

    int f[N][N] = {};
    cin >> n >> m;
    for(int i = 1; i <= n; i ++) cin >> v[i] >> w[i] >> s[i];

    for(int i = 1; i <= n; i ++)
        for(int j = 0; j <= m; j ++)
            for(int k = 0; k <= s[i] && k * v[i] <= j; k ++)
                f[i][j] = max(f[i][j], f[i-1][j-v[i] * k] + w[i] * k); 

    cout << f[n][m] << endl;
    return;
}

/*
    多重背包优化版本
    对s[i]拆分  然后采用01背包方式
*/
void testI() {

    int f[N] = {0};
    cin >> n >> m;
    int cnt =0;

    for(int i = 1; i<= n; i++) {
        int a, b, s;
        cin >> a>> b >> s;

        int k = 1;
        while(k <= s) {
            cnt ++;
            v[cnt] = a * k;
            w[cnt] = b * k;
            s -= k;
            k <<= 1; 
        }       

        if(s > 0) {
            cnt ++;
            v[cnt] = a * s;
            w[cnt] = b * s; 
        }
    }    
    

    n = cnt;
    for(int i = 1; i <= n; i ++)
        for(int j = m; j >= v[i]; j --)
            f[j] = max(f[j], f[j-v[i]] + w[i]);


    cout << f[m] << endl;
    return;
}

int 
main(void) {

//  testIII();
    testI();

    return 0;
}
