#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;



const int N = 310;
int n;
int s[N];
int f[N][N];


int 
main(void) {

    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> s[i];

    //处理前缀和
    for(int i = 1; i <= n; i ++) s[i] += s[i-1];

    //枚举所有状态
    for(int len = 2; len <= n; len ++)   //长度
        for(int i = 1; i +len -1 <= n; i ++) {  //起点
            int l = i, r = i + len - 1;
            f[l][r] = 1e8;
            for(int k = l; k < r; k ++)    //区间
                f[l][r] = min(f[l][r], f[l][k] + f[k+1][r] + s[r] - s[l-1]);
        }

    cout << f[1][n] << endl;

    return 0;
}
