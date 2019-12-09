#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int N = 12, M = 1 << N;
bool st[M];
long long f[N][M];
int n, m;



int main(void)
{
    while (cin >> n >> m, n || m) {

        //预处理
        for(int i = 0; i < 1 << n; i ++){          //n列
            int cnt = 0;
            st[i] = true;

            for(int j = 0; j < n; j ++)
                if(i >> j & 1) {
                    if(cnt & 1) st[i] = false; 
                    cnt = 0;
                }else cnt++;
            if(cnt & 1) st[i] = false;
        }
        
        //状态压缩
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for(int i = 1; i<= m; i++)
            for(int j = 0; j < 1<< n; j ++)
                for(int k = 0; k < 1 << n; k ++) 
                  if((j & k) == 0 && st[j | k])    //st[j|k] ? 
                        f[i][j] += f[i-1][k];
        cout << f[m][0] << endl;
    } 
    return 0;
}
