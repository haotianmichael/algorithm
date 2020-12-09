/*蛇形矩阵*/
#include <iostream>
#include <algorithm>
#include <cstring>


using namespace std;
const int N = 110;
int n, m;
int res[N][N];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};


int main(void)
{
    cin >> n >> m;  // n 行 m 列
    
    //填写
    for(int x = 0, y = 0, k = 1, d = 0; k <= n*m; k ++) {
            
       res[x][y] = k;
       int a = x + dx[d], b = y + dy[d]; 
       if(a < 0  || a >= n || b < 0 || b >= m || res[a][b]) {  //核心： 边界判断 
            d = (d + 1) % 4;
            a = x + dx[d], b = y + dy[d];
       } 
       x = a, y = b;
    }


    //输出
    for(int x = 0; x < n; x ++) {
        for(int y = 0; y < m; y ++) {
            cout << res[x][y] << ' '; 
        } 
        cout << endl; 
    }
    
    
    return 0;
}
