#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 210, INF = 1e9;
int d[N][N];
int n, m, Q;

/*
   使用邻接矩阵存储
 
   注意邻接矩阵在初始化的时候
 
*/
void floyd() {

    int i, j, k;
    for(k = 1; k <= n; k ++)
        for(i = 1; i <=n; i ++) 
            for(j = 1; j <= n; j++) 
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
}

int
main(void) {
    cin >> n >> m >> Q;
    //初始化
    for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= n; j ++) {
            if(i == j)  d[i][j] = 0;
            else d[i][j] = INF;
        } 
    }


    while(m --) {
        int a, b, w;
        cin >> a >> b >> w;
        d[a][b] = min(d[a][b], w);        
    }

    floyd();

    while(Q --) {
        int a, b;
        cin >> a>> b;
        //这里还是会遇到和spfa算法相同的判断方式
        if(d[a][b] > INF / 2)  cout << "impossible" << endl;
        else cout << d[a][b] <<endl; 
    }

    return 0;
}
