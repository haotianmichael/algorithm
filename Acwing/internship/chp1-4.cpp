#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 110, M = 11;
int n, m;
int f[N][M];

/*动态规划
  f[i][j]存的是次数
  O(n^2m)
 */
int DP1(void)
{
    while(cin >> n >> m){

        for(int i = 1; i <= n; i ++) f[i][1] = i;
        for(int i = 1; i <= m; i ++) f[1][i] = 1;

        for(int i = 2; i <= n; i++)
            for(int j = 2; j <= m; j ++) {
                f[i][j] = f[i][j-1];
                for(int k = 1; k <= i; k ++) 
                    f[i][j] = min(f[i][j], max(f[k-1][j-1], f[i-k][j]) + 1);
            }

        cout << f[n][m] << endl; 
    } 
    return 0;
}



/*
   动态规划
   f[i][j]存的是长度
   O(nm) 
 */
int DP2(void) {

    while(cin >> n >> m){
        for(int i = 1; i <= n; i ++)  {
            for(int j = 1; j <= m; j ++) f[i][j] = f[i-1][j] + f[i-1][j-1] + 1;
            if(f[i][m] >= n) {
                printf("%d\n", i);          
                break;
            }
        }
    }
    return 0;
}


int main(void)
{
    DP1();

    return 0;
}
