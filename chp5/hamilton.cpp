#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 21;
int f[1 << 20][N];
int w[N][N];
int n;

int main(void)
{
    
    cin >> n;
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n;  j ++) 
            cin >> w[i][j];

    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;   //起点不需要代价
    for(int i = 1; i< (1 << n); i ++)    //  方案集合  二进制状态表示路径
        for(int j = 0; j < n; j ++)  //表示第几点
            if(i >> j & 1) 
              for(int k = 0; k < n;  k++)   
                f[i][j] = min(f[i][j], f[i^(1 << j)][k] + w[k][j]); 
    cout << f[(1 << n) - 1][n-1] << endl;
    return 0;
}
